#define GLUT_DISABLE_ATEXIT_HACK
#include <List>
#include <vector>
#include "GLUT.H"
#include <math.h>
#include <string.h>
#include <map>
#include<iostream>
#include <fstream>
#include <sstream>
using namespace std;
#define PI 3.1415
#define EPSILON 0.000001
#define nearplane_width 800 //视景体宽度
#define nearplane_height 800 //视景体高度

#define pointLightNum  1
#define modelNum  3

#define Weight 0.5

int nearplane_distance = 300; //视景体近平面与视点距离
int farplane_distance = nearplane_distance + 300; //视景体远平面与视点距离


float pitch = 0, yaw = -PI / 2;		//角度
int last_x = nearplane_width / 2, last_y = 0;

int speed = 10;		//视觉中心移动速度
float sensitivity = 0.002;		//鼠标输入灵敏度
int isperspective = 0;		//是否开启透视投影

class my_homogeneous_point
{
public:
	float x;
	float y;
	float z;
	float ratio;
	/*RGB rgb;*/
	float dx;	//法向量
	float dy;
	float dz;

	my_homogeneous_point(float a = 0, float b = 0, float c = 0, float d = 0, float e = 0, float f = 0) {
		x = a;
		y = b;
		z = c;
		dx = d;
		dy = e;
		dz = f;
		ratio = 1;
	}
};
//定义向量
class my_3Dvector
{
public:
	float dx = 0;
	float dy = 0;
	float dz = 0;
	float len = 1;
public:
	my_3Dvector() {}
	my_3Dvector(float x, float y, float z) {
		dx = x;
		dy = y;
		dz = z;
		len = sqrtf(powf(dx, 2) + powf(dy, 2) + powf(dz, 2));
		/*dx /= len;
		dy /= len;
		dz /= len;*/
	}
	//start点指向end点的向量
	my_3Dvector(my_homogeneous_point start, my_homogeneous_point end) {
		dx = end.x - start.x;
		dy = end.y - start.y;
		dz = end.z - start.z;
		len = sqrtf(powf(dx, 2) + powf(dy, 2) + powf(dz, 2));
	}
	//叉乘 this X input_vector
	my_3Dvector cross_multiply(my_3Dvector input_vector)
	{
		float new_dx = dy * input_vector.dz - dz * input_vector.dy;
		float new_dy = dz * input_vector.dx - dx * input_vector.dz;
		float new_dz = dx * input_vector.dy - dy * input_vector.dx;
		return my_3Dvector(new_dx, new_dy, new_dz);
	}
	//点乘 this * input_vector
	float dot_multiply(my_3Dvector input_vector) {
		return dx * input_vector.dx + dy * input_vector.dy + dz * input_vector.dz;
	}
};

class Color {
public:
	float r, g, b;
	Color(float x = 0, float y = 0, float z = 0) {
		r = x;
		g = y;
		b = z;
	}
};


//定义面的结构体，包含该面的各个顶点和法向量
class my_face_homogeneous
{
public:
	vector<my_homogeneous_point> mList;//各个顶点按照逆时针的顺序储存
	my_3Dvector n; //定义面法向量
};

class Model {
public:
	vector<my_face_homogeneous> face;
	float Kar, Kag, Kab;	//全局光反射率
	float Kdr, Kdg, Kdb;	//漫反射率
	float Ksr = 0.2, Ksg = 0.2, Ksb = 0.2;	//高光亮系数
	int n = 100;					//镜反射指数
	float Wr, Wt;		//折射与反射率
	float eta;		//折射率
	//float Ksr = 0.2, Ksg = 0.2, Ksb = 0.2;	//高光亮系数
	//int n = 100;					//镜反射指数
	/*Model(float a=0.5,float b=0.5,float c = 0.5,float d = 0.5,float e = 0.5,float f = 0.5) {
		Kar = a;
		Kag = b;
		Kab=c;
		Kdr = d;
		Kdg = e;
		Kdb = f;
	}*/
}model[modelNum], box[modelNum];
class GlobalLight {
public:
	float r = 1;
	float g = 1;
	float b = 1;
}globalLight;

class PointLight
{
public:
	float r = 1;
	float g = 1;
	float b = 1;
	my_homogeneous_point p;		//记录位置
	bool isOpen = 0;

	/*float distance = 10000;
	float pitch = 0, yaw = PI / 2;*/

	/*my_homogeneous_point P;*/
}pointLight[pointLightNum];

my_homogeneous_point eye(0, 0, 800);//视觉中心位置
my_3Dvector look(0, 0, -1);	//看向的方向	
Color color[nearplane_height][nearplane_width];

vector<string> split(string T, string P) {
	vector<string> arr;
	if (T == "")return arr;
	unsigned point1 = 0, point2 = 0;
	if (P == "" || T.find(P, point1) == string::npos) {//不分割或者原字符串找不到分割符
		arr.push_back(T);
		return arr;
	}
	while ((point1 = T.find(P, point1)) != string::npos) {
		if (point1 == point2)arr.push_back("");
		else arr.push_back(T.substr(point2, point1 - point2));
		point2 = point1 + P.length();//跳过匹配串P
		point1 += P.length();

	}
	if (point2 <= T.length() - 1)arr.push_back(T.substr(point2, T.length() - point2));
	return arr;
}
void read(vector<my_face_homogeneous>& model, string url)
{
	ifstream file;

	file.open(url, ios_base::in);

	if (!file.is_open())
	{
		cout << "打开文件失败";
		return;
	}

	string s;


	vector<my_homogeneous_point> point;
	my_homogeneous_point curPoint;
	int j = 0;
	while (getline(file, s))
	{
		my_3Dvector N1, N2, N3;

		if (s[0] == 'v' && s[1] == ' ') {

			vector<string>str = split(s, " ");
			/*float a;
			int b;*/
			curPoint.x = atof(str[1].c_str());
			curPoint.y = atof(str[2].c_str());
			curPoint.z = atof(str[3].c_str());
			/* b= rand() % 101;
			a = (float)b/ 100;
			curPoint.rgb.r = a;
			b = rand() % 101;
			a = (float)b / 100;
			curPoint.rgb.g = a;
			b = rand() % 101;
			a = (float)b / 100;
			curPoint.rgb.b = a;*/
			point.push_back(curPoint);
		}
		else if (s[0] == 'v' && s[1] == 'n') {
			vector<string>str = split(s, " ");
			point[j].dx = atof(str[1].c_str());
			point[j].dy = atof(str[2].c_str());
			point[j].dz = atof(str[3].c_str());
			j++;
		}
		else if (s[0] == 'f') {
			my_face_homogeneous curFace;
			vector<string>str = split(s, " ");
			for (int i = 0; i < 3; i++) {
				vector<string>str1 = split(str[i + 1], "/");
				curFace.mList.push_back(point[atoi(str1[0].c_str()) - 1]);
			}
			N1 = my_3Dvector(curFace.mList[1].x - curFace.mList[0].x, curFace.mList[1].y - curFace.mList[0].y, curFace.mList[1].z - curFace.mList[0].z);//N1用来存储当前平面上的一个向量
			N2 = my_3Dvector(curFace.mList[2].x - curFace.mList[0].x, curFace.mList[2].y - curFace.mList[0].y, curFace.mList[2].z - curFace.mList[0].z);//N2用来存储当前平面上的一个向量
			N3 = N1.cross_multiply(N2);//N3为当前平面的法向量
			float length = sqrtf(N3.dx * N3.dx + N3.dy * N3.dy + N3.dz * N3.dz);
			curFace.n.dx = N3.dx / length;
			curFace.n.dy = N3.dy / length;
			curFace.n.dz = N3.dz / length;

			model.push_back(curFace);
		}
	}

	file.close();

}

void creatBox(Model model, Model& box) {
	float maxX = model.face[0].mList[0].x, minX = model.face[0].mList[0].x, maxY = model.face[0].mList[0].y, minY = model.face[0].mList[0].y, maxZ = model.face[0].mList[0].z, minZ = model.face[0].mList[0].z;
	my_face_homogeneous face;
	my_homogeneous_point point;
	for (int i = 0; i < model.face.size(); i++) {
		for (int j = 0; j < model.face[i].mList.size(); j++) {
			if (model.face[i].mList[j].x > maxX)
				maxX = model.face[i].mList[j].x;
			else if (model.face[i].mList[j].x < minX) {
				minX = model.face[i].mList[j].x;
			}
			if (model.face[i].mList[j].y > maxY)
				maxY = model.face[i].mList[j].y;
			else if (model.face[i].mList[j].y < minY) {
				minY = model.face[i].mList[j].y;
			}
			if (model.face[i].mList[j].z > maxZ)
				maxZ = model.face[i].mList[j].z;
			else if (model.face[i].mList[j].z < minZ) {
				minZ = model.face[i].mList[j].z;
			}
		}
	}
	face.mList.clear();
	point.z = maxZ;
	point.x = minX;
	point.y = minY;
	face.mList.push_back(point);
	point.x = maxX;
	point.y = minY;
	face.mList.push_back(point);
	point.x = minX;
	point.y = maxY;
	face.mList.push_back(point);
	box.face.push_back(face);

	face.mList.clear();
	point.z = maxZ;
	point.x = maxX;
	point.y = maxY;
	face.mList.push_back(point);
	point.x = maxX;
	point.y = minY;
	face.mList.push_back(point);
	point.x = minX;
	point.y = maxY;
	face.mList.push_back(point);
	box.face.push_back(face);

	face.mList.clear();
	point.z = minZ;
	point.x = minX;
	point.y = minY;
	face.mList.push_back(point);
	point.x = maxX;
	point.y = minY;
	face.mList.push_back(point);
	point.x = minX;
	point.y = maxY;
	face.mList.push_back(point);
	box.face.push_back(face);

	face.mList.clear();
	point.z = minZ;
	point.x = maxX;
	point.y = maxY;
	face.mList.push_back(point);
	point.x = maxX;
	point.y = minY;
	face.mList.push_back(point);
	point.x = minX;
	point.y = maxY;
	face.mList.push_back(point);
	box.face.push_back(face);

	face.mList.clear();
	point.x = maxX;
	point.z = minZ;
	point.y = minY;
	face.mList.push_back(point);
	point.z = maxZ;
	point.y = minY;
	face.mList.push_back(point);
	point.z = minZ;
	point.y = maxY;
	face.mList.push_back(point);
	box.face.push_back(face);

	face.mList.clear();
	point.x = maxX;
	point.z = maxZ;
	point.y = maxY;
	face.mList.push_back(point);
	point.z = maxZ;
	point.y = minY;
	face.mList.push_back(point);
	point.z = minZ;
	point.y = maxY;
	face.mList.push_back(point);
	box.face.push_back(face);

	face.mList.clear();
	point.x = minX;
	point.z = minZ;
	point.y = minY;
	face.mList.push_back(point);
	point.z = maxZ;
	point.y = minY;
	face.mList.push_back(point);
	point.z = minZ;
	point.y = maxY;
	face.mList.push_back(point);
	box.face.push_back(face);

	face.mList.clear();
	point.x = minX;
	point.z = maxZ;
	point.y = maxY;
	face.mList.push_back(point);
	point.z = maxZ;
	point.y = minY;
	face.mList.push_back(point);
	point.z = minZ;
	point.y = maxY;
	face.mList.push_back(point);
	box.face.push_back(face);

	face.mList.clear();
	point.y = maxY;
	point.x = minX;
	point.z = minZ;
	face.mList.push_back(point);
	point.x = maxX;
	point.z = minZ;
	face.mList.push_back(point);
	point.x = minX;
	point.z = maxZ;
	face.mList.push_back(point);
	box.face.push_back(face);

	face.mList.clear();
	point.y = maxY;
	point.x = maxX;
	point.z = maxZ;
	face.mList.push_back(point);
	point.x = maxX;
	point.z = minZ;
	face.mList.push_back(point);
	point.x = minX;
	point.z = maxZ;
	face.mList.push_back(point);
	box.face.push_back(face);

	face.mList.clear();
	point.y = minY;
	point.x = minX;
	point.z = minZ;
	face.mList.push_back(point);
	point.x = maxX;
	point.z = minZ;
	face.mList.push_back(point);
	point.x = minX;
	point.z = maxZ;
	face.mList.push_back(point);
	box.face.push_back(face);

	face.mList.clear();
	point.y = minY;
	point.x = maxX;
	point.z = maxZ;
	face.mList.push_back(point);
	point.x = maxX;
	point.z = minZ;
	face.mList.push_back(point);
	point.x = minX;
	point.z = maxZ;
	face.mList.push_back(point);
	box.face.push_back(face);
}
struct my_homogeneous_point matrix_multiply_vector(float matrix[][4], struct my_homogeneous_point input_v)
{
	struct my_homogeneous_point translated_v;
	translated_v.x = matrix[0][0] * input_v.x + matrix[0][1] * input_v.y + matrix[0][2] * input_v.z + matrix[0][3] * input_v.ratio;
	translated_v.y = matrix[1][0] * input_v.x + matrix[1][1] * input_v.y + matrix[1][2] * input_v.z + matrix[1][3] * input_v.ratio;
	translated_v.z = matrix[2][0] * input_v.x + matrix[2][1] * input_v.y + matrix[2][2] * input_v.z + matrix[2][3] * input_v.ratio;
	translated_v.ratio = matrix[3][0] * input_v.x + matrix[3][1] * input_v.y + fabsf(matrix[3][2] * input_v.z) + matrix[3][3] * input_v.ratio;
	return translated_v;
}
void translate_model(vector<my_face_homogeneous>& model, int dx, int dy, int dz, float angleY, float angleX)
{
	for (int i = 0; i < model.size(); i++)
	{
		float pai = 3.14159;
		float translate_matrix[4][4];
		memset(translate_matrix, 0, sizeof(int) * 16);
		translate_matrix[1][1] = 1;

		float angle = angleY;	//先绕y轴
		/*angle = angle * pai / 180;*/
		translate_matrix[0][0] = cos(angle);
		translate_matrix[2][0] = -sin(angle);
		translate_matrix[0][2] = sin(angle);
		translate_matrix[2][2] = cos(angle);
		translate_matrix[3][3] = 1;
		for (int j = 0; j < model[i].mList.size(); j++)
		{
			struct my_homogeneous_point input_v;
			input_v.x = model[i].mList[j].x;
			input_v.y = model[i].mList[j].y;
			input_v.z = model[i].mList[j].z;
			input_v.ratio = 1;
			input_v = matrix_multiply_vector(translate_matrix, input_v);
			model[i].mList[j].x = input_v.x;
			model[i].mList[j].y = input_v.y;
			model[i].mList[j].z = input_v.z;
			model[i].mList[j].ratio = input_v.ratio;

			input_v.x = model[i].mList[j].dx;
			input_v.y = model[i].mList[j].dy;
			input_v.z = model[i].mList[j].dz;
			input_v.ratio = 1;
			input_v = matrix_multiply_vector(translate_matrix, input_v);
			model[i].mList[j].dx = input_v.x;
			model[i].mList[j].dy = input_v.y;
			model[i].mList[j].dz = input_v.z;
			model[i].mList[j].ratio = input_v.ratio;

		}
		memset(translate_matrix, 0, sizeof(int) * 16);
		translate_matrix[0][0] = 1;
		angle = angleX;			//再x轴
		translate_matrix[1][1] = cos(angle);
		translate_matrix[1][2] = -sin(angle);
		translate_matrix[2][1] = +sin(angle);
		translate_matrix[2][2] = cos(angle);
		translate_matrix[3][3] = 1;
		for (int j = 0; j < model[i].mList.size(); j++)
		{
			struct my_homogeneous_point input_v;
			input_v.x = model[i].mList[j].x;
			input_v.y = model[i].mList[j].y;
			input_v.z = model[i].mList[j].z;
			input_v.ratio = 1;
			input_v = matrix_multiply_vector(translate_matrix, input_v);
			model[i].mList[j].x = input_v.x;
			model[i].mList[j].y = input_v.y;
			model[i].mList[j].z = input_v.z;
			model[i].mList[j].ratio = input_v.ratio;

			input_v.x = model[i].mList[j].dx;
			input_v.y = model[i].mList[j].dy;
			input_v.z = model[i].mList[j].dz;
			input_v.ratio = 1;
			input_v = matrix_multiply_vector(translate_matrix, input_v);
			model[i].mList[j].dx = input_v.x;
			model[i].mList[j].dy = input_v.y;
			model[i].mList[j].dz = input_v.z;
			model[i].mList[j].ratio = input_v.ratio;

		}
		for (int j = 0; j < model[i].mList.size(); j++)
		{
			model[i].mList[j].x -= dx;
			model[i].mList[j].y -= dy;
			model[i].mList[j].z -= dz;
		}

	}
}

void rotate_normal(vector<my_face_homogeneous>& model)
{
	for (int i = 0; i < model.size(); i++)
	{
		my_3Dvector N1, N2, N3;
		N1 = my_3Dvector(model[i].mList[0], model[i].mList[1]);//N1用来存储当前平面上的一个向量
		N2 = my_3Dvector(model[i].mList[0], model[i].mList[2]);//N2用来存储当前平面上的一个向量
		N3 = N1.cross_multiply(N2);//N3为当前平面的法向量
		model[i].n.dx = N3.dx;
		model[i].n.dy = N3.dy;
		model[i].n.dz = N3.dz;
	}

}
void init() {
	read(model[0].face, "./Model/test_model/测试1.obj");
	translate_model(model[0].face, 0, 70, 0, 0, 0);
	rotate_normal(model[0].face);
	creatBox(model[0], box[0]);

	read(model[1].face, "./Model/test_model/测试2.obj");
	translate_model(model[1].face, 0, 50, 0, 0, 0);
	rotate_normal(model[1].face);
	creatBox(model[1], box[1]);

	read(model[2].face, "./Model/test_model/测试3.obj");
	creatBox(model[2], box[2]);

	/*read(model[3].face, "C:\\Users\\Hyotei\\OneDrive\\桌面\\模型\\test.obj");
	translate_model(model[3].face, 150, -75, -200, 2.5, 0);
	rotate_normal(model[3].face);
	creatBox(model[3], box[3]);*/



	model[0].Kar = 0;
	model[0].Kag = 0;
	model[0].Kab = 0.4;
	model[0].Kdr = 0;
	model[0].Kdg = 0;
	model[0].Kdb = 0.3;
	model[0].eta = 1.2;
	model[0].Wr = 0.2;
	model[0].Wt = 0;

	model[1].Kar = 0.4;
	model[1].Kag = 0;
	model[1].Kab = 0;
	model[1].Kdr = 0.3;
	model[1].Kdg = 0;
	model[1].Kdb = 0;
	model[1].eta = 1.2;
	model[1].Wr = 0.2;
	model[1].Wt = 0;

	model[2].Kar = 0.1;
	model[2].Kag = 0.1;
	model[2].Kab = 0.1;
	model[2].Kdr = 0.1;
	model[2].Kdg = 0.1;
	model[2].Kdb = 0.1;
	model[2].eta = 1.2;
	model[2].Wr = 0.9;
	model[2].Wt = 0;

	/*model[3].Kar = 0.1;
	model[3].Kag = 0.1;
	model[3].Kab = 0.1;
	model[3].Kdr = 0.1;
	model[3].Kdg = 0.1;
	model[3].Kdb = 0.1;
	model[3].eta = 1.2;
	model[3].Wr = 0.3;
	model[3].Wt = 0.9;*/


	pointLight[0].p.x = 0;
	pointLight[0].p.y = 1000;
	pointLight[0].p.z = 1000;
}
float ray_triangle_intersection(my_face_homogeneous face, my_homogeneous_point O, my_3Dvector D, my_homogeneous_point& I)
{
	my_3Dvector e1(face.mList[1].x - face.mList[0].x, face.mList[1].y - face.mList[0].y, face.mList[1].z - face.mList[0].z);
	my_3Dvector e2(face.mList[2].x - face.mList[0].x, face.mList[2].y - face.mList[0].y, face.mList[2].z - face.mList[0].z);
	my_3Dvector P = D.cross_multiply(e2);

	float det = e1.dot_multiply(P);
	if (det > -EPSILON && det < EPSILON) {

		return 0;
	}
	float inv_det = 1 / det;
	my_3Dvector T(O.x - face.mList[0].x, O.y - face.mList[0].y, O.z - face.mList[0].z);
	float u = T.dot_multiply(P) * inv_det;
	if (u < 0 || u > 1) {
		return 0;
	}
	my_3Dvector Q = T.cross_multiply(e1);
	float v = D.dot_multiply(Q) * inv_det;
	if (v < 0 || u + v  > 1) {

		return 0;
	}
	float t = e2.dot_multiply(Q) * inv_det;
	if (t > EPSILON)
	{
		I.x = O.x + D.dx * t;
		I.y = O.y + D.dy * t;
		I.z = O.z + D.dz * t;
		return t;
	}

	return 0;
}

my_3Dvector getDvector(my_face_homogeneous face, my_homogeneous_point p) {
	my_3Dvector d;
	/*float a = (-(p.x - face.mList[1].x) * (face.mList[2].y - face.mList[1].y) + (p.y - face.mList[1].y) * (face.mList[2].x - face.mList[1].x))
		/ (-(face.mList[0].x - face.mList[1].x) * (face.mList[2].y - face.mList[1].y) + (face.mList[0].y - face.mList[1].y) * (face.mList[2].x - face.mList[1].x));
	float b = (-(p.x - face.mList[2].x) * (face.mList[0].y - face.mList[2].y) + (p.y - face.mList[2].y) * (face.mList[0].x - face.mList[2].x))
		/ (-(face.mList[1].x - face.mList[2].x) * (face.mList[0].y - face.mList[2].y) + (face.mList[1].y - face.mList[2].y) * (face.mList[0].x - face.mList[2].x));
	float c = 1 - a - b;
	d.dx = a * face.mList[0].dx + b * face.mList[1].dx + c * face.mList[2].dx;
	d.dy = a * face.mList[0].dy + b * face.mList[1].dy + c * face.mList[2].dy;
	d.dz = a * face.mList[0].dz + b * face.mList[1].dz + c * face.mList[2].dz;*/
	my_3Dvector d1 = my_3Dvector(p, face.mList[0]);
	my_3Dvector d2 = my_3Dvector(p, face.mList[1]);
	my_3Dvector d3 = my_3Dvector(p, face.mList[2]);
	float S3 = d1.cross_multiply(d2).len;
	float S2 = d3.cross_multiply(d1).len;
	float S1 = d2.cross_multiply(d3).len;
	float sum = S1 + S2 + S3;
	d.dx = S1 / sum * face.mList[0].dx + S2 / sum * face.mList[1].dx + S3 / sum * face.mList[2].dx;
	d.dy = S1 / sum * face.mList[0].dy + S2 / sum * face.mList[1].dy + S3 / sum * face.mList[2].dy;
	d.dz = S1 / sum * face.mList[0].dz + S2 / sum * face.mList[1].dz + S3 / sum * face.mList[2].dz;
	return d;
}

Color RayTracing(my_homogeneous_point start, my_3Dvector direction, float weight, int lastModel = -1, int lastFace = -1) {


	Color color;
	my_homogeneous_point p, point;
	int model_num, face_num;
	float min = 999999999;
	if (weight < 0.15)
		return color;
	for (int i = 0; i < modelNum; i++) {
		bool flag = 0;
		for (int j = 0; j < box[i].face.size(); j++) {
			if (ray_triangle_intersection(box[i].face[j], start, direction, p)) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			for (int j = 0; j < model[i].face.size(); j++) {
				if (i == lastModel && j == lastFace)		//避免反射时直接传递自己！！！
					continue;
				float t = ray_triangle_intersection(model[i].face[j], start, direction, p);
				if (/*model[i].face[j].mList.size()!=0&&*/t != 0 && t < min) {
					min = t;
					point = p;
					model_num = i;
					face_num = j;
					/*color.r = 1;
					return color;*/
				}
			}
		}
	}
	if (min != 999999999) {
		my_3Dvector dvector = getDvector(model[model_num].face[face_num], point);
		my_3Dvector dvector_light(point, pointLight[0].p);
		color.r = globalLight.r * model[model_num].Kar;
		color.g = globalLight.g * model[model_num].Kag;
		color.b = globalLight.b * model[model_num].Kab;



		bool flag1 = 0, flag2 = 0;
		for (int i = 0; i < modelNum; i++) {		//遮挡产生阴影效果
			for (int j = 0; j < box[i].face.size(); j++) {
				float t = ray_triangle_intersection(box[i].face[j], point, dvector_light, p);
				if (t > 0 && t <= 1) {
					flag1 = 1;
					break;
				}
			}
			if (flag1 == 1) {
				for (int j = 0; j < model[i].face.size(); j++) {
					if (i == model_num && j == face_num)
						continue;
					float t = ray_triangle_intersection(model[i].face[j], point, dvector_light, p);
					if (t > 0 && t <= 1) {
						flag2 = 1;
						break;
					}
				}
				flag1 = 0;
			}
			if (flag2 == 1)
				break;
		}
		if (flag2 == 0) {
			my_3Dvector L(pointLight[0].p.x - point.x, pointLight[0].p.y - point.y, pointLight[0].p.z - point.z);
			L.dx /= L.len;
			L.dy /= L.len;
			L.dz /= L.len;

			my_3Dvector V(point, eye);
			V.dx /= V.len;
			V.dy /= V.len;
			V.dz /= V.len;
			float proportion = dvector.dot_multiply(L);
			my_3Dvector R(2 * proportion * dvector.dx - L.dx, 2 * proportion * dvector.dy - L.dy, 2 * proportion * dvector.dz - L.dz);
			R.dx /= R.len;
			R.dy /= R.len;
			R.dz /= R.len;

			float theta = dvector.dot_multiply(L);
			float alpha = R.dot_multiply(V);
			if (theta < 0) {
				theta = 0;
				alpha = 0;
			}
			if (alpha <= 0)
				alpha = 0;
			else
				alpha = powf(alpha, model[model_num].n);
			color.r += pointLight[0].r * model[model_num].Kdr * theta + pointLight[0].r * model[model_num].Ksr * alpha;
			color.g += pointLight[0].g * model[model_num].Kdg * theta + pointLight[0].g * model[model_num].Ksg * alpha;
			color.b += pointLight[0].b * model[model_num].Kdb * theta + pointLight[0].b * model[model_num].Ksb * alpha;
		}
		//计算反射光和折射光
		if (model[model_num].Wr || model[model_num].Wt) {


			Color reflexColor, refractionColor;
			float directionLength = sqrtf(powf(direction.dx, 2) + powf(direction.dy, 2) + powf(direction.dz, 2));//把光的方向变为单位向量，便于后面的处理
			direction.dx = direction.dx / directionLength;
			direction.dy = direction.dy / directionLength;
			direction.dz = direction.dz / directionLength;

			bool inside = false;				//分别处理内部和外部
			if (direction.dot_multiply(dvector) > 0) {
				dvector.dx *= -1;
				dvector.dy *= -1;
				dvector.dz *= -1;
				inside = true;
			}

			if (model[model_num].Wr) {
				float proportion = dvector.dot_multiply(direction);
				my_3Dvector R(direction.dx - 2 * proportion * dvector.dx, direction.dy - 2 * proportion * dvector.dy, direction.dz - 2 * proportion * dvector.dz);
				reflexColor = RayTracing(point, R, weight * model[model_num].Wr, model_num, face_num);
			}
			if (model[model_num].Wt) {
				float eta = (inside) ? model[model_num].eta : 1 / model[model_num].eta;
				float cosi = -dvector.dot_multiply(direction);
				float k = 1 - eta * eta * (1 - cosi * cosi);

				if (k > 0) {
					my_3Dvector T(eta * direction.dx + (eta * cosi - sqrtf(k)) * dvector.dx, eta * direction.dy + (eta * cosi - sqrtf(k)) * dvector.dy, eta * direction.dz + (eta * cosi - sqrtf(k)) * dvector.dz);
					refractionColor = RayTracing(point, T, weight * model[model_num].Wt, model_num, face_num);
				}
				/*if(inside)
					cout <<inside<<" " << refractionColor.r << " " << refractionColor.g << " " << refractionColor.b << endl;*/
			}

			color.r += reflexColor.r + refractionColor.r;
			color.g += reflexColor.g + refractionColor.g;
			color.b += reflexColor.b + refractionColor.b;
		}

		color.r *= weight;	//乘以权重
		color.g *= weight;
		color.b *= weight;
	}

	return color;
}

//绘制内容
void display(void) {
	/*for (int i = 0; i < modelNum; i++) {
		for (int j = 0; j < model[i].face.size(); j++) {
			if (model[i].face[j].n.dot_multiply(look) >= 0)
				model[i].face[j].mList.clear();
		}
	}*/


	my_3Dvector directionX(-look.dz, 0, look.dx);
	directionX.dx /= directionX.len;
	directionX.dz /= directionX.len;
	my_3Dvector directionY(0, -look.dz, look.dy);
	directionY.dy /= directionY.len;
	directionY.dz /= directionY.len;
	if (isperspective == 0) {		//平行投影
		my_homogeneous_point start(eye.x + look.dx * nearplane_distance - directionX.dx * nearplane_width / 2, eye.y + look.dy * nearplane_distance - directionY.dy * nearplane_height / 2
			, eye.z + look.dz * nearplane_distance - directionX.dz * nearplane_width / 2 - directionY.dz * nearplane_height / 2);
		for (int i = 0; i < nearplane_height; i++) {
			for (int j = 0; j < nearplane_width; j++) {
				color[i][j] = RayTracing(start, look, 1);
				start.x += directionX.dx;
				start.z += directionX.dz;
			}
			cout << i << endl;
			start.x -= directionX.dx * nearplane_width;
			start.y += directionY.dy;
			start.z = start.z - directionX.dz * nearplane_width + directionY.dz;
		}
	}
	else if (isperspective == 1) {		//透视投影
		my_homogeneous_point start(eye.x + look.dx * nearplane_distance - directionX.dx * nearplane_width / 2, eye.y + look.dy * nearplane_distance - directionY.dy * nearplane_height / 2
			, eye.z + look.dz * nearplane_distance - directionX.dz * nearplane_width / 2 - directionY.dz * nearplane_height / 2);
		for (int i = 0; i < nearplane_height; i++) {
			for (int j = 0; j < nearplane_width; j++) {
				my_3Dvector l(eye, start);
				color[i][j] = RayTracing(start, l, 1);
				start.x += directionX.dx;
				start.z += directionX.dz;
			}
			cout << i << endl;
			start.x -= directionX.dx * nearplane_width;
			start.y += directionY.dy;
			start.z = start.z - directionX.dz * nearplane_width + directionY.dz;
		}
	}

	glBegin(GL_POINTS);
	for (int i = 0; i < nearplane_height; i++) {
		for (int j = 0; j < nearplane_width; j++) {
			glColor3f(color[i][j].r, color[i][j].g, color[i][j].b);
			glVertex2i(j - nearplane_width / 2, i - nearplane_height / 2);
		}
	}
	glEnd();
	glutSwapBuffers();
}


//投影方式、modelview方式设置
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(-0.5 * nearplane_width, 0.5 * nearplane_width, -0.5 * nearplane_height * (GLfloat)nearplane_height / (GLfloat)nearplane_width, 0.5 * nearplane_height * (GLfloat)nearplane_height / (GLfloat)nearplane_width,
			-nearplane_distance, nearplane_distance + 1000); //相对于视点
	else
		glOrtho(-0.5 * nearplane_width, 0.5 * nearplane_width, -0.5 * nearplane_height * (GLfloat)nearplane_width / (GLfloat)nearplane_height, 0.5 * nearplane_height * (GLfloat)nearplane_width / (GLfloat)nearplane_height,
			-nearplane_distance, nearplane_distance + 1000);

	//if (w <= h)
	//	glFrustum(-0.5 * nearplane_width, 0.5 * nearplane_width, -0.5 * nearplane_height * (GLfloat)nearplane_height / (GLfloat)nearplane_width, 0.5 * nearplane_height * (GLfloat)nearplane_height / (GLfloat)nearplane_width,
	//		nearplane_distance, farplane_distance); //相对于视点
	//else
	//	glFrustum(-0.5 * nearplane_width, 0.5 * nearplane_width, -0.5 * nearplane_height * (GLfloat)nearplane_width / (GLfloat)nearplane_height, 0.5 * nearplane_height * (GLfloat)nearplane_width / (GLfloat)nearplane_height,
	//	nearplane_distance, farplane_distance);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*gluLookAt(eye_x, eye_y, eye_z, look_x * INT_MAX, look_y * INT_MAX, look_z * INT_MAX, 0, 1, 0);*/
}

//键盘交互事件
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	case 'W':
	{
		eye.x += cos(yaw) * speed;
		eye.z += sin(yaw) * speed;
		break;
	}
	case 's':
	case 'S':
	{
		eye.x -= cos(yaw) * speed;
		eye.z -= sin(yaw) * speed;
		break;
	}
	case 'a':
	case 'A':
	{
		eye.x += sin(yaw) * speed;
		eye.z -= cos(yaw) * speed;
		break;
	}
	case 'd':
	case 'D':
	{
		eye.x -= sin(yaw) * speed;
		eye.z += cos(yaw) * speed;
		break;
	}
	case 't':
	case 'T':
	{
		isperspective = 1 - isperspective;
		break;
	}
	case 'g':
	case 'G':
	{
		if (pitch < PI / 4)
			pitch += PI / 10;
		look.dy = sin(pitch);
		look.dx = cos(pitch) * cos(yaw);
		look.dz = cos(pitch) * sin(yaw);
		break;
	}
	case 'b':
	case 'B':
	{
		if (pitch > -PI / 4)
			pitch -= PI / 10;
		look.dy = sin(pitch);
		look.dx = cos(pitch) * cos(yaw);
		look.dz = cos(pitch) * sin(yaw);
		break;
	}
	case 'v':
	case 'V':
	{
		yaw -= PI / 10;
		look.dy = sin(pitch);
		look.dx = cos(pitch) * cos(yaw);
		look.dz = cos(pitch) * sin(yaw);
		break;
	}
	case 'n':
	case 'N':
	{
		yaw += PI / 10;
		look.dy = sin(pitch);
		look.dx = cos(pitch) * cos(yaw);
		look.dz = cos(pitch) * sin(yaw);
		break;
	}
	case 27:
		exit(0);
		break;
	}
	/*reshape(nearplane_width, nearplane_height);*/
	glutPostRedisplay();
}
//鼠标交互事件
//void mouse(int x, int y)
//{
//	float offset_x = x - last_x;
//	float offset_y = last_y - y;
//	last_x = x;
//	last_y = y;
//	yaw += offset_x * sensitivity * PI;
//	pitch += offset_y * sensitivity * PI;
//	if (pitch > PI / 4)
//		pitch = PI / 4;
//	else if (pitch < -PI / 4)
//		pitch = -PI / 4;
//	look.dy = sin(pitch);
//	look.dx = cos(pitch) * cos(yaw);
//	look.dz = cos(pitch) * sin(yaw);
//	/*reshape(nearplane_width, nearplane_height);*/
//	glutPostRedisplay();
//}

//主调函数
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(nearplane_width, nearplane_height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("RayTracing");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	/*glutPassiveMotionFunc(mouse);*/
	glutMainLoop();
	return 0;
}




