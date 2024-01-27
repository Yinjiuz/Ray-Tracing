//#define GLUT_DISABLE_ATEXIT_HACK
//#define STB_IMAGE_IMPLEMENTATION
//#include <List>
//#include <vector>
//#include "GLUT.H"
//#include <math.h>
//#include <string.h>
//#include <map>
//#include<iostream>
//#include <fstream>
//#include <sstream>
//#include"stb_image.h"
//#include<pthread.h>
//#pragma comment(lib, "pthreadVC2.lib")
//using namespace std;
//#define PI 3.1415
//#define EPSILON 0.000001
//#define nearplane_width 800 //视景体宽度
//#define nearplane_height 800 //视景体高度
//
//#define pointLightNum 3
//#define modelNum  300
//
//#define Weight 0.5
//#define Erow	160
//#define Enumber 0
//#define threads 25
//
//int ModelNum = 0;
//int imageNum = 0;
//
//int nearplane_distance = 1000; //视景体近平面与视点距离
//int farplane_distance = nearplane_distance + 300; //视景体远平面与视点距离
//
//
//float pitch = 0, yaw = PI / 2;		//角度
//int last_x = nearplane_width / 2, last_y = 0;
//
//int speed = 10;		//视觉中心移动速度
//float sensitivity = 0.002;		//鼠标输入灵敏度
//int isperspective = 1;		//是否开启透视投影
//vector<int>single_arr = { 1,2,3,8,15,18,19,20,22,23,24,25,26,27,28,29,30,34,35,37,38,40,41,42,43,44,45,47,48,50,52,55,56,61,69,70,71,72,73,74,79,80,81,82,83,84,85,87,88,89,90,91
//,93,94,95,96,97,99,100,103 };
//class my_homogeneous_point
//{
//public:
//	float x = 0;
//	float y = 0;
//	float z = 0;
//	float ratio;
//	/*RGB rgb;*/
//	float dx = 0;	//法向量
//	float dy = 0;
//	float dz = 0;
//	//纹理信息
//	float fx = 0;
//	float fy = 0;
//
//	my_homogeneous_point(float a = 0, float b = 0, float c = 0, float d = 0, float e = 0, float f = 0, float g = 0, float h = 0) {
//		x = a;
//		y = b;
//		z = c;
//		dx = d;
//		dy = e;
//		dz = f;
//		ratio = 1;
//		fx = g;
//		fy = h;
//	}
//};
////定义向量
//class my_3Dvector
//{
//public:
//	float dx = 0;
//	float dy = 0;
//	float dz = 0;
//	float len = 1;
//public:
//	my_3Dvector() {}
//	my_3Dvector(float x, float y, float z) {
//		dx = x;
//		dy = y;
//		dz = z;
//		len = sqrtf(powf(dx, 2) + powf(dy, 2) + powf(dz, 2));
//		/*dx /= len;
//		dy /= len;
//		dz /= len;*/
//	}
//	//start点指向end点的向量
//	my_3Dvector(my_homogeneous_point start, my_homogeneous_point end) {
//		dx = end.x - start.x;
//		dy = end.y - start.y;
//		dz = end.z - start.z;
//		len = sqrtf(powf(dx, 2) + powf(dy, 2) + powf(dz, 2));
//	}
//	//叉乘 this X input_vector
//	my_3Dvector cross_multiply(my_3Dvector input_vector)
//	{
//		float new_dx = dy * input_vector.dz - dz * input_vector.dy;
//		float new_dy = dz * input_vector.dx - dx * input_vector.dz;
//		float new_dz = dx * input_vector.dy - dy * input_vector.dx;
//		return my_3Dvector(new_dx, new_dy, new_dz);
//	}
//	//点乘 this * input_vector
//	float dot_multiply(my_3Dvector input_vector) {
//		return dx * input_vector.dx + dy * input_vector.dy + dz * input_vector.dz;
//	}
//};
//
//class Color {
//public:
//	float data[4];
//	Color(float x = 0, float y = 0, float z = 0, float a = 1) {
//		data[0] = x;
//		data[1] = y;
//		data[2] = z;
//		data[3] = a;
//	}
//};
//
//struct Image {
//	vector<vector<Color>> data;
//	string imageName;
//	int height;
//	int width;
//}imageData[modelNum], * image[modelNum] = { NULL };
////定义面的结构体，包含该面的各个顶点和法向量
//class my_face_homogeneous
//{
//public:
//	vector<my_homogeneous_point> mList;//各个顶点按照逆时针的顺序储存
//	my_3Dvector n; //定义面法向量
//};
//
//class Model {
//public:
//	vector<my_face_homogeneous> face;
//	float Kar, Kag, Kab;	//全局光反射率
//	float Kdr, Kdg, Kdb;	//漫反射率
//	float Ksr = 0.2, Ksg = 0.2, Ksb = 0.2;	//高光亮系数
//	int n = 100;					//镜反射指数
//	float Wr = 0, Wt = 0;		//反射率与折射
//	float eta = 1.5;		//折射率
//	//float Ksr = 0.2, Ksg = 0.2, Ksb = 0.2;	//高光亮系数
//	//int n = 100;					//镜反射指数
//	/*Model(float a=0.5,float b=0.5,float c = 0.5,float d = 0.5,float e = 0.5,float f = 0.5) {
//		Kar = a;
//		Kag = b;
//		Kab=c;
//		Kdr = d;
//		Kdg = e;
//		Kdb = f;
//	}*/
//}model[modelNum], box[modelNum];
//class GlobalLight {
//public:
//	float r = 0.4;
//	float g = 0.4;
//	float b = 0.4;
//}globalLight;
//
//class PointLight
//{
//public:
//	float r = 0.4;
//	float g = 0.4;
//	float b = 0.4;
//
//	bool isOpen = 1;
//
//	float distance = 10000;
//	float pitch = 0, yaw = PI / 2;
//	//聚光灯
//	int tag = 0;
//	//my_3Dvector direction;
//	my_3Dvector Direction;
//	float Cutoff;
//	my_homogeneous_point p;
//	my_homogeneous_point P;
//}pointLight[pointLightNum];
//
//my_homogeneous_point eye(0, 2500, 1000);//视觉中心位置
////my_homogeneous_point eye(0, 0, -1000);
//my_3Dvector look(-0.3, 0, 0.95);	//看向的方向	
//Color color[nearplane_height][nearplane_width];
//my_3Dvector directionX;
//my_3Dvector directionY;
//
//my_homogeneous_point start, start2, start3, start4, start5, start6, start7, start8, start9, start10, start11, start12, start13, start14, start15, start16, start17, start18, start19, start20, start21, start22, start23, start24, start25;
//vector<int>toumingIndex = { 72, 150,151,152 ,167 ,168,169,77 ,85 ,92 ,99,71, 176, 181,24,25,26,109,108,107,106,110,111,74 };
//
//vector<string> split(string T, string P) {
//	vector<string> arr;
//	if (T == "")return arr;
//	unsigned point1 = 0, point2 = 0;
//	if (P == "" || T.find(P, point1) == string::npos) {//不分割或者原字符串找不到分割符
//		arr.push_back(T);
//		return arr;
//	}
//	while ((point1 = T.find(P, point1)) != string::npos) {
//		if (point1 == point2)arr.push_back("");
//		else arr.push_back(T.substr(point2, point1 - point2));
//		point2 = point1 + P.length();//跳过匹配串P
//		point1 += P.length();
//
//	}
//	if (point2 <= T.length() - 1)arr.push_back(T.substr(point2, T.length() - point2));
//	return arr;
//}
//void readImage(Image& image, string a) {
//
//	int n;
//	// 加载图片获取宽、高、颜色通道信息
//	unsigned char* data = stbi_load(a.c_str(), &image.width, &image.height, &n, 0);
//	Color color;
//	vector<Color> heng;
//	int j = 0;
//	for (int i = 0; i < image.width * image.height * n; i++) {
//		color.data[i % n] = (float)data[i] / 255;
//		if (i % n == n - 1) {
//			heng.push_back(color);
//			j++;
//		}
//		if (j == image.width) {
//			j = 0;
//			image.data.push_back(heng);
//			heng.clear();
//		}
//	}
//	stbi_image_free(data);
//}
//void readMTL(Model* model, string url)
//{
//	ifstream file;
//
//	file.open(url, ios_base::in);
//
//	if (!file.is_open())
//	{
//		cout << "打开文件失败";
//		return;
//	}
//
//	string s;
//	int index = ModelNum;
//	bool first = true;
//	/*struct ModelReflectivity temp;*/
//	while (getline(file, s))
//	{
//		if (s[0] == 'n' && s[1] == 'e' && s[2] == 'w' && first)
//		{
//			first = false;
//		}
//		else if (s[0] == 'n' && s[1] == 'e' && s[2] == 'w')
//		{
//			/*mdelReflectivity[index] = temp;*/
//			index++;
//
//			/*cout << mdelReflectivity[index - 1].Kar << " " << mdelReflectivity[index - 1].Ksr << endl;*/
//		}
//		else if (s[0] == 'm' && s[1] == 'a' && s[2] == 'p') {
//			vector<string>str = split(s, " ");
//			int flag = -1;
//
//			for (int i = 0; i < imageNum; i++) {
//				if (imageData[i].imageName == str[1]) {
//					flag = i;
//					break;
//				}
//			}
//
//			if (flag != -1) {
//				image[index] = &imageData[flag];
//			}
//
//			else {
//				readImage(imageData[imageNum], "./Model/texture/" + str[1]);
//				/*cout << index << endl;*/
//				imageData[imageNum].imageName = str[1];
//				image[index] = &imageData[imageNum];
//				imageNum++;
//			}
//		}
//		else if (s[0] == 'K' && s[1] == 'a')
//		{
//			vector<string>str = split(s, " ");
//
//			model[index].Kar = atof(str[1].c_str());
//			model[index].Kag = atof(str[2].c_str());
//			model[index].Kab = atof(str[3].c_str());
//		}
//		else if (s[0] == 'K' && s[1] == 'd')
//		{
//			vector<string>str = split(s, " ");
//			model[index].Kdr = atof(str[1].c_str());
//			model[index].Kdg = atof(str[2].c_str());
//			model[index].Kdb = atof(str[3].c_str());
//		}
//		else if (s[0] == 'K' && s[1] == 's')
//		{
//			vector<string>str = split(s, " ");
//			model[index].Ksr = atof(str[1].c_str());
//			model[index].Ksg = atof(str[2].c_str());
//			model[index].Ksb = atof(str[3].c_str());
//		}
//		/*else if (s[0] == 'N' && s[1] == 's')
//		{
//			vector<string>str = split(s, " ");
//			model[index].Wt = atof(str[1].c_str());
//		}
//		else if (s[0] == 'N' && s[1] == 'i')
//		{
//			vector<string>str = split(s, " ");
//			model[index].eta = 1 / atof(str[1].c_str());
//		}*/
//		/*else if (s[0] == 'N' && s[1] == 'i')
//		{
//			vector<string>str = split(s, " ");
//			model[index].eta = 1 / atof(str[1].c_str());
//		}*/
//
//		for (int i = 0; i < toumingIndex.size(); i++)
//		{
//			if (index == toumingIndex[i])
//			{
//				//cout << "透明标号 ：" << index << " " << tar << endl;
//				if (index == 74)
//				{
//					model[index].Wt = 0.7;
//				}
//				else {
//					model[index].Wt = 0.9;
//					model[index].Wr = 0.3;
//				}
//
//				break;
//			}
//		}
//		if (index == 4)
//		{
//			model[index].Wr = 0.5;
//		}
//		if (index == 45)
//		{
//			model[index].Wr = 1;
//		}
//
//	}
//	/*mdelReflectivity[index] = temp;*/
//	ModelNum = index + 1;
//
//}
//void creatBox(Model model, Model& box) {
//	float maxX = model.face[0].mList[0].x, minX = model.face[0].mList[0].x, maxY = model.face[0].mList[0].y, minY = model.face[0].mList[0].y, maxZ = model.face[0].mList[0].z, minZ = model.face[0].mList[0].z;
//	my_face_homogeneous face;
//	my_homogeneous_point point;
//	for (int i = 0; i < model.face.size(); i++) {
//		for (int j = 0; j < model.face[i].mList.size(); j++) {
//			if (model.face[i].mList[j].x > maxX)
//				maxX = model.face[i].mList[j].x;
//			else if (model.face[i].mList[j].x < minX) {
//				minX = model.face[i].mList[j].x;
//			}
//			if (model.face[i].mList[j].y > maxY)
//				maxY = model.face[i].mList[j].y;
//			else if (model.face[i].mList[j].y < minY) {
//				minY = model.face[i].mList[j].y;
//			}
//			if (model.face[i].mList[j].z > maxZ)
//				maxZ = model.face[i].mList[j].z;
//			else if (model.face[i].mList[j].z < minZ) {
//				minZ = model.face[i].mList[j].z;
//			}
//		}
//	}
//	face.mList.clear();
//	point.z = maxZ;
//	point.x = minX;
//	point.y = minY;
//	face.mList.push_back(point);
//	point.x = maxX;
//	point.y = minY;
//	face.mList.push_back(point);
//	point.x = minX;
//	point.y = maxY;
//	face.mList.push_back(point);
//	box.face.push_back(face);
//
//	face.mList.clear();
//	point.z = maxZ;
//	point.x = maxX;
//	point.y = maxY;
//	face.mList.push_back(point);
//	point.x = maxX;
//	point.y = minY;
//	face.mList.push_back(point);
//	point.x = minX;
//	point.y = maxY;
//	face.mList.push_back(point);
//	box.face.push_back(face);
//
//	face.mList.clear();
//	point.z = minZ;
//	point.x = minX;
//	point.y = minY;
//	face.mList.push_back(point);
//	point.x = maxX;
//	point.y = minY;
//	face.mList.push_back(point);
//	point.x = minX;
//	point.y = maxY;
//	face.mList.push_back(point);
//	box.face.push_back(face);
//
//	face.mList.clear();
//	point.z = minZ;
//	point.x = maxX;
//	point.y = maxY;
//	face.mList.push_back(point);
//	point.x = maxX;
//	point.y = minY;
//	face.mList.push_back(point);
//	point.x = minX;
//	point.y = maxY;
//	face.mList.push_back(point);
//	box.face.push_back(face);
//
//	face.mList.clear();
//	point.x = maxX;
//	point.z = minZ;
//	point.y = minY;
//	face.mList.push_back(point);
//	point.z = maxZ;
//	point.y = minY;
//	face.mList.push_back(point);
//	point.z = minZ;
//	point.y = maxY;
//	face.mList.push_back(point);
//	box.face.push_back(face);
//
//	face.mList.clear();
//	point.x = maxX;
//	point.z = maxZ;
//	point.y = maxY;
//	face.mList.push_back(point);
//	point.z = maxZ;
//	point.y = minY;
//	face.mList.push_back(point);
//	point.z = minZ;
//	point.y = maxY;
//	face.mList.push_back(point);
//	box.face.push_back(face);
//
//	face.mList.clear();
//	point.x = minX;
//	point.z = minZ;
//	point.y = minY;
//	face.mList.push_back(point);
//	point.z = maxZ;
//	point.y = minY;
//	face.mList.push_back(point);
//	point.z = minZ;
//	point.y = maxY;
//	face.mList.push_back(point);
//	box.face.push_back(face);
//
//	face.mList.clear();
//	point.x = minX;
//	point.z = maxZ;
//	point.y = maxY;
//	face.mList.push_back(point);
//	point.z = maxZ;
//	point.y = minY;
//	face.mList.push_back(point);
//	point.z = minZ;
//	point.y = maxY;
//	face.mList.push_back(point);
//	box.face.push_back(face);
//
//	face.mList.clear();
//	point.y = maxY;
//	point.x = minX;
//	point.z = minZ;
//	face.mList.push_back(point);
//	point.x = maxX;
//	point.z = minZ;
//	face.mList.push_back(point);
//	point.x = minX;
//	point.z = maxZ;
//	face.mList.push_back(point);
//	box.face.push_back(face);
//
//	face.mList.clear();
//	point.y = maxY;
//	point.x = maxX;
//	point.z = maxZ;
//	face.mList.push_back(point);
//	point.x = maxX;
//	point.z = minZ;
//	face.mList.push_back(point);
//	point.x = minX;
//	point.z = maxZ;
//	face.mList.push_back(point);
//	box.face.push_back(face);
//
//	face.mList.clear();
//	point.y = minY;
//	point.x = minX;
//	point.z = minZ;
//	face.mList.push_back(point);
//	point.x = maxX;
//	point.z = minZ;
//	face.mList.push_back(point);
//	point.x = minX;
//	point.z = maxZ;
//	face.mList.push_back(point);
//	box.face.push_back(face);
//
//	face.mList.clear();
//	point.y = minY;
//	point.x = maxX;
//	point.z = maxZ;
//	face.mList.push_back(point);
//	point.x = maxX;
//	point.z = minZ;
//	face.mList.push_back(point);
//	point.x = minX;
//	point.z = maxZ;
//	face.mList.push_back(point);
//	box.face.push_back(face);
//}
//void read(Model* model, string url)
//{
//	ifstream file;
//
//	file.open(url, ios_base::in);
//
//	if (!file.is_open())
//	{
//		cout << "打开文件失败";
//		return;
//	}
//
//	string s;
//
//
//	vector<vector<float>>v;
//	vector<vector<float>>vn;
//	vector<vector<float>>vt;
//	float c;
//	my_homogeneous_point curPoint;
//
//	bool isfirst = 1;
//	vector<my_face_homogeneous> tempModel;
//	int index = ModelNum;
//	while (getline(file, s))
//	{
//
//		if (s[0] == 'v' && s[1] == ' ') {
//			vector<float> cur;
//
//			vector<string>str = split(s, " ");
//			/*float a;
//			int b;*/
//			c = atof(str[1].c_str()) * 20;
//			cur.push_back(c);
//			c = atof(str[2].c_str()) * 20;
//			cur.push_back(c);
//			c = atof(str[3].c_str()) * 20;
//			cur.push_back(c);
//			/* b= rand() % 101;
//			a = (float)b/ 100;
//			curPoint.rgb.r = a;
//			b = rand() % 101;
//			a = (float)b / 100;
//			curPoint.rgb.g = a;
//			b = rand() % 101;
//			a = (float)b / 100;
//			curPoint.rgb.b = a;*/
//			v.push_back(cur);
//		}
//		else if (s[0] == 'v' && s[1] == 'n') {
//			vector<float> cur;
//			vector<string>str = split(s, " ");
//			c = atof(str[1].c_str());
//			cur.push_back(c);
//			c = atof(str[2].c_str());
//			cur.push_back(c);
//			c = atof(str[3].c_str());
//			cur.push_back(c);
//			vn.push_back(cur);
//		}
//		else if (s[0] == 'v' && s[1] == 't') {
//			vector<float> cur;
//			vector<string>str = split(s, " ");
//			c = atof(str[1].c_str());
//			cur.push_back(c);
//			c = atof(str[2].c_str());
//			cur.push_back(c);
//			vt.push_back(cur);
//		}
//		else if (s[0] == 'u') {
//			if (isfirst == 1)
//				isfirst = 0;
//			else {
//				model[index].face = tempModel;
//				creatBox(model[index], box[index]);
//
//				index++;
//				tempModel.clear();
//			}
//
//		}
//
//		else if (s[0] == 'f') {
//			my_face_homogeneous curFace;
//			vector<string>str = split(s, " ");
//			for (int i = 0; i < 3; i++) {
//				vector<string>str1 = split(str[i + 1], "/");
//				my_homogeneous_point p;
//				p.x = v[atoi(str1[0].c_str()) - 1][0];
//				p.y = v[atoi(str1[0].c_str()) - 1][1];
//				p.z = v[atoi(str1[0].c_str()) - 1][2];
//				p.fx = vt[atoi(str1[1].c_str()) - 1][0];
//				p.fy = vt[atoi(str1[1].c_str()) - 1][1];
//				p.dx = vn[atoi(str1[2].c_str()) - 1][0];
//				p.dy = vn[atoi(str1[2].c_str()) - 1][1];
//				p.dz = vn[atoi(str1[2].c_str()) - 1][2];
//				curFace.mList.push_back(p);
//			}
//			tempModel.push_back(curFace);
//			if (str.size() == 5)
//			{
//				curFace.mList.clear();
//				for (int i = 2; i < 5; i++) {
//					if (i == 4)
//					{
//						i = 0;
//					}
//					vector<string>str1 = split(str[i + 1], "/");
//					my_homogeneous_point p;
//					p.x = v[atoi(str1[0].c_str()) - 1][0];
//					p.y = v[atoi(str1[0].c_str()) - 1][1];
//					p.z = v[atoi(str1[0].c_str()) - 1][2];
//					p.fx = vt[atoi(str1[1].c_str()) - 1][0];
//					p.fy = vt[atoi(str1[1].c_str()) - 1][1];
//					p.dx = vn[atoi(str1[2].c_str()) - 1][0];
//					p.dy = vn[atoi(str1[2].c_str()) - 1][1];
//					p.dz = vn[atoi(str1[2].c_str()) - 1][2];
//					curFace.mList.push_back(p);
//					if (i == 0)
//						break;
//				}
//				tempModel.push_back(curFace);
//			}
//
//		}
//	}
//	model[index].face = tempModel;
//	creatBox(model[index], box[index]);
//	index++;
//	file.close();
//
//}
//
//struct my_homogeneous_point matrix_multiply_vector(float matrix[][4], struct my_homogeneous_point input_v)
//{
//	struct my_homogeneous_point translated_v;
//	translated_v.x = matrix[0][0] * input_v.x + matrix[0][1] * input_v.y + matrix[0][2] * input_v.z + matrix[0][3] * input_v.ratio;
//	translated_v.y = matrix[1][0] * input_v.x + matrix[1][1] * input_v.y + matrix[1][2] * input_v.z + matrix[1][3] * input_v.ratio;
//	translated_v.z = matrix[2][0] * input_v.x + matrix[2][1] * input_v.y + matrix[2][2] * input_v.z + matrix[2][3] * input_v.ratio;
//	translated_v.ratio = matrix[3][0] * input_v.x + matrix[3][1] * input_v.y + fabsf(matrix[3][2] * input_v.z) + matrix[3][3] * input_v.ratio;
//	return translated_v;
//}
//void translate_model(vector<my_face_homogeneous>& model, int dx, int dy, int dz, float angleY, float angleX)
//{
//	for (int i = 0; i < model.size(); i++)
//	{
//		float pai = 3.14159;
//		float translate_matrix[4][4];
//		memset(translate_matrix, 0, sizeof(int) * 16);
//		translate_matrix[1][1] = 1;
//
//		float angle = angleY;	//先绕y轴
//		/*angle = angle * pai / 180;*/
//		translate_matrix[0][0] = cos(angle);
//		translate_matrix[2][0] = -sin(angle);
//		translate_matrix[0][2] = sin(angle);
//		translate_matrix[2][2] = cos(angle);
//		translate_matrix[3][3] = 1;
//		for (int j = 0; j < model[i].mList.size(); j++)
//		{
//			struct my_homogeneous_point input_v;
//			input_v.x = model[i].mList[j].x;
//			input_v.y = model[i].mList[j].y;
//			input_v.z = model[i].mList[j].z;
//			input_v.ratio = 1;
//			input_v = matrix_multiply_vector(translate_matrix, input_v);
//			model[i].mList[j].x = input_v.x;
//			model[i].mList[j].y = input_v.y;
//			model[i].mList[j].z = input_v.z;
//			model[i].mList[j].ratio = input_v.ratio;
//
//			input_v.x = model[i].mList[j].dx;
//			input_v.y = model[i].mList[j].dy;
//			input_v.z = model[i].mList[j].dz;
//			input_v.ratio = 1;
//			input_v = matrix_multiply_vector(translate_matrix, input_v);
//			model[i].mList[j].dx = input_v.x;
//			model[i].mList[j].dy = input_v.y;
//			model[i].mList[j].dz = input_v.z;
//			model[i].mList[j].ratio = input_v.ratio;
//
//		}
//		memset(translate_matrix, 0, sizeof(int) * 16);
//		translate_matrix[0][0] = 1;
//		angle = angleX;			//再x轴
//		translate_matrix[1][1] = cos(angle);
//		translate_matrix[1][2] = -sin(angle);
//		translate_matrix[2][1] = +sin(angle);
//		translate_matrix[2][2] = cos(angle);
//		translate_matrix[3][3] = 1;
//		for (int j = 0; j < model[i].mList.size(); j++)
//		{
//			struct my_homogeneous_point input_v;
//			input_v.x = model[i].mList[j].x;
//			input_v.y = model[i].mList[j].y;
//			input_v.z = model[i].mList[j].z;
//			input_v.ratio = 1;
//			input_v = matrix_multiply_vector(translate_matrix, input_v);
//			model[i].mList[j].x = input_v.x;
//			model[i].mList[j].y = input_v.y;
//			model[i].mList[j].z = input_v.z;
//			model[i].mList[j].ratio = input_v.ratio;
//
//			input_v.x = model[i].mList[j].dx;
//			input_v.y = model[i].mList[j].dy;
//			input_v.z = model[i].mList[j].dz;
//			input_v.ratio = 1;
//			input_v = matrix_multiply_vector(translate_matrix, input_v);
//			model[i].mList[j].dx = input_v.x;
//			model[i].mList[j].dy = input_v.y;
//			model[i].mList[j].dz = input_v.z;
//			model[i].mList[j].ratio = input_v.ratio;
//
//		}
//		for (int j = 0; j < model[i].mList.size(); j++)
//		{
//			model[i].mList[j].x -= dx;
//			model[i].mList[j].y -= dy;
//			model[i].mList[j].z -= dz;
//		}
//
//	}
//}
//
//
//void init() {
//	read(model, "./Model/天空盒00a.obj");
//	readMTL(model, "./Model/天空盒00a.mtl");
//
//	for (int i = 0; i < single_arr.size(); i++)
//	{
//
//		string url = "./Model/model/" + to_string(single_arr[i]);
//		read(model, url + ".obj");
//
//
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		//if (single_arr[i] == 55 || single_arr[i] == 56)
//		//{
//		//	//readMir
//		//}
//		//if (single_arr[i] == 9 || single_arr[i] == 20)
//		//{
//		//	//readNOR(url + ".mtl");
//		//}
//	}
//	for (int i = 1; i < 5; i++)
//	{
//		string url = "./Model/model/12_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		//readNOR(url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/13_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		//readNOR(url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/17_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/32_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		//readNOR(url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/33_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		//readNOR(url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//
//		url = "./Model/model/78_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/86_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		if (i == 2 || i == 3)
//		{
//			continue;
//		}
//		url = "./Model/model/58_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//	}
//	for (int i = 1; i < 6; i++)
//	{
//		string url = "./Model/model/4_" + to_string(i);
//		//cout << url << endl;
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		//readNOR(url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/10_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/46_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/105_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//	}
//	for (int i = 1; i < 7; i++)
//	{
//		string url = "./Model/model/65_" + to_string(i);
//		//cout << url << endl;
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/66_" + to_string(i);
//		//cout << url << endl;
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//	}
//	for (int i = 1; i < 3; i++)
//	{
//		string url = "./Model/model/14_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/21_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/31_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/39_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/53_" + to_string(i);	////
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		//	cout << ModelNum << " " << url << endl;
//		url = "./Model/model/59_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/62_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/63_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/64_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/67_" + to_string(i);
//		//cout << url << endl;
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/68_" + to_string(i);
//		//cout << url << endl;
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/75_" + to_string(i);
//		//cout << url << endl;
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		//readNOR(url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/92_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/98_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/101_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/102_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//	}
//	for (int i = 1; i < 4; i++)
//	{
//		string url = "./Model/model/16_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		//	
//		url = "./Model/model/57_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/60_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/76_" + to_string(i);
//		//cout << url << endl;
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//		url = "./Model/model/77_" + to_string(i);
//		//cout << url << endl;
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//	}
//	for (int i = 1; i < 10; i++)
//	{
//		string url = "./Model/model/49_" + to_string(i);
//		read(model, url + ".obj");
//		readMTL(model, url + ".mtl");
//		cout << ModelNum << " " << url << endl;
//	}
//
//	//string url = "./Model/model/2";
//	//	read(model, url + ".obj");
//
//	ifstream file;
//	file.open("./Model/light.txt", ios_base::in);
//
//	if (!file.is_open())
//	{
//		cout << "erroe in txt" << endl;
//	}
//	string s;
//	while (getline(file, s))
//	{
//		vector<string>str = split(s, " ");
//		int index = atof(str[0].c_str()) + 1;
//		if (index == 11)
//		{
//			pointLight[2].p.x = atof(str[1].c_str());
//			pointLight[2].p.y = atof(str[2].c_str());
//			pointLight[2].p.z = atof(str[3].c_str());
//			pointLight[2].r = 1 / 2.5;
//			pointLight[2].g = 0.901 / 2.5;
//			pointLight[2].b = 0.776 / 2.5;
//
//		}
//
//	}
//
//	pointLight[0].p.x = 0;
//	pointLight[0].p.y = 5500;
//	pointLight[0].p.z = 4000;
//	pointLight[1].pitch = PI / 10;
//	pointLight[1].yaw = PI / 2;
//	pointLight[1].p.y = sin(pointLight[1].pitch) * pointLight[1].distance;
//	pointLight[1].p.x = cos(pointLight[1].pitch) * cos(pointLight[1].yaw) * pointLight[1].distance;
//	pointLight[1].p.z = cos(pointLight[1].pitch) * sin(pointLight[1].yaw) * pointLight[1].distance;
//
//}
//float ray_triangle_intersection(my_face_homogeneous face, my_homogeneous_point O, my_3Dvector D, my_homogeneous_point& I)
//{
//	my_3Dvector e1(face.mList[1].x - face.mList[0].x, face.mList[1].y - face.mList[0].y, face.mList[1].z - face.mList[0].z);
//	my_3Dvector e2(face.mList[2].x - face.mList[0].x, face.mList[2].y - face.mList[0].y, face.mList[2].z - face.mList[0].z);
//	my_3Dvector P = D.cross_multiply(e2);
//
//	float det = e1.dot_multiply(P);
//	if (det > -EPSILON && det < EPSILON) {
//
//		return 0;
//	}
//	float inv_det = 1 / det;
//	my_3Dvector T(O.x - face.mList[0].x, O.y - face.mList[0].y, O.z - face.mList[0].z);
//	float u = T.dot_multiply(P) * inv_det;
//	if (u < 0 || u > 1) {
//		return 0;
//	}
//	my_3Dvector Q = T.cross_multiply(e1);
//	float v = D.dot_multiply(Q) * inv_det;
//	if (v < 0 || u + v  > 1) {
//
//		return 0;
//	}
//	float t = e2.dot_multiply(Q) * inv_det;
//	if (t > EPSILON)
//	{
//		I.x = O.x + D.dx * t;
//		I.y = O.y + D.dy * t;
//		I.z = O.z + D.dz * t;
//		return t;
//	}
//
//	return 0;
//}
//
//my_3Dvector getDvector(my_face_homogeneous face, my_homogeneous_point p) {
//	my_3Dvector d;
//	my_3Dvector d1 = my_3Dvector(p, face.mList[0]);
//	my_3Dvector d2 = my_3Dvector(p, face.mList[1]);
//	my_3Dvector d3 = my_3Dvector(p, face.mList[2]);
//	float S3 = d1.cross_multiply(d2).len;
//	float S2 = d3.cross_multiply(d1).len;
//	float S1 = d2.cross_multiply(d3).len;
//	float sum = S1 + S2 + S3;
//	d.dx = S1 / sum * face.mList[0].dx + S2 / sum * face.mList[1].dx + S3 / sum * face.mList[2].dx;
//	d.dy = S1 / sum * face.mList[0].dy + S2 / sum * face.mList[1].dy + S3 / sum * face.mList[2].dy;
//	d.dz = S1 / sum * face.mList[0].dz + S2 / sum * face.mList[1].dz + S3 / sum * face.mList[2].dz;
//	return d;
//}
//void getF(my_face_homogeneous face, my_homogeneous_point p, float& fx, float& fy) {
//	my_3Dvector d1 = my_3Dvector(p, face.mList[0]);
//	my_3Dvector d2 = my_3Dvector(p, face.mList[1]);
//	my_3Dvector d3 = my_3Dvector(p, face.mList[2]);
//	float S3 = d1.cross_multiply(d2).len;
//	float S2 = d3.cross_multiply(d1).len;
//	float S1 = d2.cross_multiply(d3).len;
//	float sum = S1 + S2 + S3;
//	fx = S1 / sum * face.mList[0].fx + S2 / sum * face.mList[1].fx + S3 / sum * face.mList[2].fx;
//	fy = S1 / sum * face.mList[0].fy + S2 / sum * face.mList[1].fy + S3 / sum * face.mList[2].fy;
//}
//Color rayTracing(my_homogeneous_point start, my_3Dvector direction, float weight, int lastModel = -1, int lastFace = -1, int num = 1) {
//
//	/*cout << start.x << " " << start.y << " " << start.z << endl;*/
//	/*cout << direction.dx << " " << direction.dy << " " << direction.dz << endl;*/
//	Color color;
//	my_homogeneous_point p, point;
//	int model_num, face_num;
//	float min = 999999999;
//	if (/*weight<0.1||*/num > 3)
//		return color;
//	for (int i = 0; i < ModelNum; i++) {
//		bool flag = 0;
//		for (int j = 0; j < box[i].face.size(); j++) {
//			if (ray_triangle_intersection(box[i].face[j], start, direction, p)) {
//				flag = 1;
//				break;
//			}
//		}
//		if (flag == 1) {
//			for (int j = 0; j < model[i].face.size(); j++) {
//				if (i == lastModel && j == lastFace)		//避免反射时直接传递自己！！！
//					continue;
//				float t = ray_triangle_intersection(model[i].face[j], start, direction, p);
//				if (/*model[i].face[j].mList.size()!=0&&*/t != 0 && t < min) {
//					min = t;
//					point = p;
//					model_num = i;
//					face_num = j;
//					/*color.r = 1;
//					return color;*/
//				}
//			}
//		}
//	}
//	
//	if (min != 999999999) {
//		my_3Dvector dvector = getDvector(model[model_num].face[face_num], point);
//		////全局光
//		color.data[0] = globalLight.r * model[model_num].Kar;
//		color.data[1] = globalLight.g * model[model_num].Kag;
//		color.data[2] = globalLight.b * model[model_num].Kab;
//		for (int k = 0; k < pointLightNum; k++) {
//			if (pointLight[k].isOpen == 1) {
//				my_3Dvector dvector_light(point, pointLight[k].p);
//				bool flag1 = 0, flag2 = 0;
//
//				for (int i = 0; i < ModelNum; i++) {		//遮挡产生阴影效果
//					if (model[i].Wt != 0)
//					{
//						continue;
//					}
//					for (int j = 0; j < box[i].face.size(); j++) {
//						float t = ray_triangle_intersection(box[i].face[j], point, dvector_light, p);
//						if (t > 0 && t <= 1) {
//							flag1 = 1;
//							break;
//						}
//					}
//					if (flag1 == 1) {
//						for (int j = 0; j < model[i].face.size(); j++) {
//							if (i == model_num && j == face_num)
//								continue;
//							float t = ray_triangle_intersection(model[i].face[j], point, dvector_light, p);
//							if (t > 0 && t <= 1) {
//								flag2 = 1;
//								break;
//							}
//						}
//						flag1 = 0;
//					}
//					if (flag2 == 1)
//						break;
//				}
//				if (flag2 == 0) {
//					my_3Dvector L(pointLight[k].p.x - point.x, pointLight[k].p.y - point.y, pointLight[k].p.z - point.z);
//					L.dx /= L.len;
//					L.dy /= L.len;
//					L.dz /= L.len;
//
//					my_3Dvector V(point, eye);
//					V.dx /= V.len;
//					V.dy /= V.len;
//					V.dz /= V.len;
//					float proportion = dvector.dot_multiply(L);
//					my_3Dvector R(2 * proportion * dvector.dx - L.dx, 2 * proportion * dvector.dy - L.dy, 2 * proportion * dvector.dz - L.dz);
//					R.dx /= R.len;
//					R.dy /= R.len;
//					R.dz /= R.len;
//
//					float theta = dvector.dot_multiply(L);
//					float alpha = R.dot_multiply(V);
//					if (theta < 0) {
//						theta = 0;
//						alpha = 0;
//					}
//					if (alpha <= 0)
//						alpha = 0;
//					else
//						alpha = powf(alpha, model[model_num].n);
//					color.data[0] += pointLight[k].r * model[model_num].Kdr * theta + pointLight[k].r * model[model_num].Ksr * alpha;
//					color.data[1] += pointLight[k].g * model[model_num].Kdg * theta + pointLight[k].g * model[model_num].Ksg * alpha;
//					color.data[2] += pointLight[k].b * model[model_num].Kdb * theta + pointLight[k].b * model[model_num].Ksb * alpha;
//				}
//			}
//
//		}
//		/*cout << "1:" << color.data[0] << " " << color.data[1] << " " << color.data[2] << endl;*/
//		//计算反射光和折射光
//		if (model[model_num].Wr || model[model_num].Wt) {
//			Color reflexColor, refractionColor;
//			float directionLength = sqrtf(powf(direction.dx, 2) + powf(direction.dy, 2) + powf(direction.dz, 2));//把光的方向变为单位向量，便于后面的处理
//			direction.dx = direction.dx / directionLength;
//			direction.dy = direction.dy / directionLength;
//			direction.dz = direction.dz / directionLength;
//
//			bool inside = false;				//分别处理内部和外部
//			if (direction.dot_multiply(dvector) > 0) {
//				dvector.dx *= -1;
//				dvector.dy *= -1;
//				dvector.dz *= -1;
//				inside = true;
//			}
//
//			if (model[model_num].Wr) {
//				float proportion = dvector.dot_multiply(direction);
//				my_3Dvector R(direction.dx - 2 * proportion * dvector.dx, direction.dy - 2 * proportion * dvector.dy, direction.dz - 2 * proportion * dvector.dz);
//				reflexColor = rayTracing(point, R, weight * model[model_num].Wr, model_num, face_num, num + 1);
//			}
//			if (model[model_num].Wt) {
//				float eta = (inside) ? model[model_num].eta : 1 / model[model_num].eta;
//				float cosi = -dvector.dot_multiply(direction);
//				float k = 1 - eta * eta * (1 - cosi * cosi);
//
//				if (k > 0) {
//					my_3Dvector T(eta * direction.dx + (eta * cosi - sqrtf(k)) * dvector.dx, eta * direction.dy + (eta * cosi - sqrtf(k)) * dvector.dy, eta * direction.dz + (eta * cosi - sqrtf(k)) * dvector.dz);
//					refractionColor = rayTracing(point, T, weight * model[model_num].Wt, model_num, face_num, num + 1);
//				}
//				/*if(inside)
//					cout <<inside<<" " << refractionColor.r << " " << refractionColor.g << " " << refractionColor.b << endl;*/
//			}
//			/*cout <<"3:"<< reflexColor.data[0] << " " << reflexColor.data[1] << " " << reflexColor.data[2] << endl;
//			cout << "4:" << refractionColor.data[0] << " " << refractionColor.data[1] << " " << refractionColor.data[2] << endl;*/
//			color.data[0] += reflexColor.data[0] + refractionColor.data[0];
//			color.data[1] += reflexColor.data[1] + refractionColor.data[1];
//			color.data[2] += reflexColor.data[2] + refractionColor.data[2];
//		}
//		/*cout << "2:" << color.data[0] << " " << color.data[1] << " " << color.data[2] << endl;*/
//		//加上纹理贴图
//		color.data[0] *= (1 - Weight);	//乘以权重
//		color.data[1] *= (1 - Weight);
//		color.data[2] *= (1 - Weight);
//		if (image[model_num] != NULL) {
//			float fx, fy;
//			getF(model[model_num].face[face_num], point, fx, fy);
//			int h = int(image[model_num]->height * (fy));
//			/*if (h < 0)
//				h = 0;
//			else if (h > image[num].height)
//				h = image[num].height - 1;*/
//			int w = int(image[model_num]->width * (fx));
//			/*if (w < 0)
//				w = 0;
//			else if (w > image[num].width)
//				w = image[num].width - 1;*/
//			if (h < image[model_num]->height && h>0 && w < image[model_num]->width && w>0) {
//
//				color.data[0] += Weight * image[model_num]->data[h][w].data[0];
//				color.data[1] += Weight * image[model_num]->data[h][w].data[1];
//				color.data[2] += Weight * image[model_num]->data[h][w].data[2];
//				/*cout << color[y][x][k].data[0] << " " << color[y][x][k].data[1] << " " << color[y][x][k].data[2] << endl;*/
//			}
//		}
//		color.data[0] *= weight;	//乘以权重
//		color.data[1] *= weight;
//		color.data[2] *= weight;
//	}
//
//	return color;
//}
//void saveResult(int i, int j)
//{
//	ofstream outfile("./Model/1.txt", ios::app);
//	outfile << i << " " << j << " " << color[i][j].data[0] << " " << color[i][j].data[1] << " " << color[i][j].data[2] << " ";
//	outfile << endl;
//	outfile.close();
//}
//void* rayTracing1(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = 0; j < nearplane_width / threads; j++) {
//			my_3Dvector l(eye, start);
//			color[i+Enumber*Erow][j] = rayTracing(start, l, 1);
//			saveResult(i + Enumber * Erow, j);
//			start.x += directionX.dx;
//			start.z += directionX.dz;
//		}
//		cout << i << endl;
//		start.x -= directionX.dx * nearplane_width / threads;
//		start.y += directionY.dy;
//		start.z = start.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//void* rayTracing2(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads; j < nearplane_width / threads * 2; j++) {
//
//			my_3Dvector l(eye, start2);
//			color[i + Enumber * Erow][j] = rayTracing(start2, l, 1); saveResult(i + Enumber * Erow, j);
//			start2.x += directionX.dx;
//			start2.z += directionX.dz;
//		}
//		cout << i << endl;
//		start2.x -= directionX.dx * nearplane_width / threads;
//		start2.y += directionY.dy;
//		start2.z = start2.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//void* rayTracing3(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 2; j < nearplane_width / threads * 3; j++) {
//			my_3Dvector l(eye, start3);
//			color[i + Enumber * Erow][j] = rayTracing(start3, l, 1); saveResult(i + Enumber * Erow, j);
//			start3.x += directionX.dx;
//			start3.z += directionX.dz;
//		}
//		cout << i << endl;
//		start3.x -= directionX.dx * nearplane_width / threads;
//		start3.y += directionY.dy;
//		start3.z = start3.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//void* rayTracing4(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 3; j < nearplane_width / threads * 4; j++) {
//			my_3Dvector l(eye, start4);
//			color[i + Enumber * Erow][j] = rayTracing(start4, l, 1); saveResult(i + Enumber * Erow, j);
//			start4.x += directionX.dx;
//			start4.z += directionX.dz;
//		}
//		cout << i << endl;
//		start4.x -= directionX.dx * nearplane_width / threads;
//		start4.y += directionY.dy;
//		start4.z = start4.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//void* rayTracing5(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 4; j < nearplane_width / threads * 5; j++) {
//			my_3Dvector l(eye, start5);
//			color[i + Enumber * Erow][j] = rayTracing(start5, l, 1); saveResult(i + Enumber * Erow, j);
//			start5.x += directionX.dx;
//			start5.z += directionX.dz;
//		}
//		cout << i << endl;
//		start5.x -= directionX.dx * nearplane_width / threads;
//		start5.y += directionY.dy;
//		start5.z = start5.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//void* rayTracing6(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 5; j < nearplane_width / threads * 6; j++) {
//			my_3Dvector l(eye, start6);
//			color[i + Enumber * Erow][j] = rayTracing(start6, l, 1);saveResult(i + Enumber * Erow, j);
//			start6.x += directionX.dx;
//			start6.z += directionX.dz;
//		}
//		cout << i << endl;
//		start6.x -= directionX.dx * nearplane_width / threads;
//		start6.y += directionY.dy;
//		start6.z = start6.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//void* rayTracing7(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 6; j < nearplane_width / threads * 7; j++) {
//			my_3Dvector l(eye, start7);
//			color[i + Enumber * Erow][j] = rayTracing(start7, l, 1); saveResult(i + Enumber * Erow, j);
//			start7.x += directionX.dx;
//			start7.z += directionX.dz;
//		}
//		cout << i << endl;
//		start7.x -= directionX.dx * nearplane_width / threads;
//		start7.y += directionY.dy;
//		start7.z = start7.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//void* rayTracing8(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 7; j < nearplane_width / threads * 8; j++) {
//			my_3Dvector l(eye, start8);
//			color[i + Enumber * Erow][j] = rayTracing(start8, l, 1); saveResult(i + Enumber * Erow, j);
//			start8.x += directionX.dx;
//			start8.z += directionX.dz;
//		}
//		cout << i << endl;
//		start8.x -= directionX.dx * nearplane_width / threads;
//		start8.y += directionY.dy;
//		start8.z = start8.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//
//void* rayTracing9(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 8; j < nearplane_width / threads * 9; j++) {
//			my_3Dvector l(eye, start9);
//			color[i + Enumber * Erow][j] = rayTracing(start9, l, 1); saveResult(i + Enumber * Erow, j);
//			start9.x += directionX.dx;
//			start9.z += directionX.dz;
//		}
//		cout << i << endl;
//		start9.x -= directionX.dx * nearplane_width / threads;
//		start9.y += directionY.dy;
//		start9.z = start9.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//
//void* rayTracing10(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 9; j < nearplane_width / threads * 10; j++) {
//			my_3Dvector l(eye, start10);
//			color[i + Enumber * Erow][j] = rayTracing(start10, l, 1); saveResult(i + Enumber * Erow, j);
//			start10.x += directionX.dx;
//			start10.z += directionX.dz;
//		}
//		cout << i << endl;
//		start10.x -= directionX.dx * nearplane_width / threads;
//		start10.y += directionY.dy;
//		start10.z = start10.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//
//void* rayTracing11(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 10; j < nearplane_width / threads * 11; j++) {
//			my_3Dvector l(eye, start11);
//			color[i + Enumber * Erow][j] = rayTracing(start11, l, 1); saveResult(i + Enumber * Erow, j);
//			start11.x += directionX.dx;
//			start11.z += directionX.dz;
//		}
//		cout << i << endl;
//		start11.x -= directionX.dx * nearplane_width / threads;
//		start11.y += directionY.dy;
//		start11.z = start11.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//
//void* rayTracing12(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 11; j < nearplane_width / threads * 12; j++) {
//			my_3Dvector l(eye, start12);
//			color[i + Enumber * Erow][j] = rayTracing(start12, l, 1); saveResult(i + Enumber * Erow, j);
//			start12.x += directionX.dx;
//			start12.z += directionX.dz;
//		}
//		cout << i << endl;
//		start12.x -= directionX.dx * nearplane_width / threads;
//		start12.y += directionY.dy;
//		start12.z = start12.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//void* rayTracing13(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 12; j < nearplane_width / threads * 13; j++) {
//			my_3Dvector l(eye, start13);
//			color[i + Enumber * Erow][j] = rayTracing(start13, l, 1); saveResult(i + Enumber * Erow, j);
//			start13.x += directionX.dx;
//			start13.z += directionX.dz;
//		}
//		cout << i << endl;
//		start13.x -= directionX.dx * nearplane_width / threads;
//		start13.y += directionY.dy;
//		start13.z = start13.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//
//void* rayTracing14(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 13; j < nearplane_width / threads * 14; j++) {
//			my_3Dvector l(eye, start14);
//			color[i + Enumber * Erow][j] = rayTracing(start14, l, 1); saveResult(i + Enumber * Erow, j);
//			start14.x += directionX.dx;
//			start14.z += directionX.dz;
//		}
//		cout << i << endl;
//		start14.x -= directionX.dx * nearplane_width / threads;
//		start14.y += directionY.dy;
//		start14.z = start14.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//
//void* rayTracing15(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 14; j < nearplane_width / threads * 15; j++) {
//			my_3Dvector l(eye, start15);
//			color[i + Enumber * Erow][j] = rayTracing(start15, l, 1); saveResult(i + Enumber * Erow, j);
//			start15.x += directionX.dx;
//			start15.z += directionX.dz;
//		}
//		cout << i << endl;
//		start15.x -= directionX.dx * nearplane_width / threads;
//		start15.y += directionY.dy;
//		start15.z = start15.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//
//void* rayTracing16(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 15; j < nearplane_width / threads * 16; j++) {
//			my_3Dvector l(eye, start16);
//			color[i + Enumber * Erow][j] = rayTracing(start16, l, 1); saveResult(i + Enumber * Erow, j);
//			start16.x += directionX.dx;
//			start16.z += directionX.dz;
//		}
//		cout << i << endl;
//		start16.x -= directionX.dx * nearplane_width / threads;
//		start16.y += directionY.dy;
//		start16.z = start16.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//
//void* rayTracing17(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 16; j < nearplane_width / threads * 17; j++) {
//			my_3Dvector l(eye, start17);
//			color[i + Enumber * Erow][j] = rayTracing(start17, l, 1); saveResult(i + Enumber * Erow, j);
//			start17.x += directionX.dx;
//			start17.z += directionX.dz;
//		}
//		cout << i << endl;
//		start17.x -= directionX.dx * nearplane_width / threads;
//		start17.y += directionY.dy;
//		start17.z = start17.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//
//void* rayTracing18(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 17; j < nearplane_width / threads * 18; j++) {
//			my_3Dvector l(eye, start18);
//			color[i + Enumber * Erow][j] = rayTracing(start18, l, 1); saveResult(i + Enumber * Erow, j);
//			start18.x += directionX.dx;
//			start18.z += directionX.dz;
//		}
//		cout << i << endl;
//		start18.x -= directionX.dx * nearplane_width / threads;
//		start18.y += directionY.dy;
//		start18.z = start18.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//
//void* rayTracing19(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 18; j < nearplane_width / threads * 19; j++) {
//			my_3Dvector l(eye, start19);
//			color[i + Enumber * Erow][j] = rayTracing(start19, l, 1); saveResult(i + Enumber * Erow, j);
//			start19.x += directionX.dx;
//			start19.z += directionX.dz;
//		}
//		cout << i << endl;
//		start19.x -= directionX.dx * nearplane_width / threads;
//		start19.y += directionY.dy;
//		start19.z = start19.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//
//void* rayTracing20(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 19; j < nearplane_width / threads * 20; j++) {
//			my_3Dvector l(eye, start20);
//			color[i + Enumber * Erow][j] = rayTracing(start20, l, 1); saveResult(i + Enumber * Erow, j);
//			start20.x += directionX.dx;
//			start20.z += directionX.dz;
//		}
//		cout << i << endl;
//		start20.x -= directionX.dx * nearplane_width / threads;
//		start20.y += directionY.dy;
//		start20.z = start20.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//
//void* rayTracing21(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 20; j < nearplane_width / threads * 21; j++) {
//			my_3Dvector l(eye, start21);
//			color[i + Enumber * Erow][j] = rayTracing(start21, l, 1); saveResult(i + Enumber * Erow, j);
//			start21.x += directionX.dx;
//			start21.z += directionX.dz;
//		}
//		cout << i << endl;
//		start21.x -= directionX.dx * nearplane_width / threads;
//		start21.y += directionY.dy;
//		start21.z = start21.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//
//void* rayTracing22(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 21; j < nearplane_width / threads * 22; j++) {
//			my_3Dvector l(eye, start22);
//			color[i + Enumber * Erow][j] = rayTracing(start22, l, 1); saveResult(i + Enumber * Erow, j);
//			start22.x += directionX.dx;
//			start22.z += directionX.dz;
//		}
//		cout << i << endl;
//		start22.x -= directionX.dx * nearplane_width / threads;
//		start22.y += directionY.dy;
//		start22.z = start22.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//
//void* rayTracing23(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 22; j < nearplane_width / threads * 23; j++) {
//			my_3Dvector l(eye, start23);
//			color[i + Enumber * Erow][j] = rayTracing(start23, l, 1); saveResult(i + Enumber * Erow, j);
//			start23.x += directionX.dx;
//			start23.z += directionX.dz;
//		}
//		cout << i << endl;
//		start23.x -= directionX.dx * nearplane_width / threads;
//		start23.y += directionY.dy;
//		start23.z = start23.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//
//void* rayTracing24(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 23; j < nearplane_width / threads * 24; j++) {
//			my_3Dvector l(eye, start24);
//			color[i + Enumber * Erow][j] = rayTracing(start24, l, 1); saveResult(i + Enumber * Erow, j);
//			start24.x += directionX.dx;
//			start24.z += directionX.dz;
//		}
//		cout << i << endl;
//		start24.x -= directionX.dx * nearplane_width / threads;
//		start24.y += directionY.dy;
//		start24.z = start24.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//
//void* rayTracing25(void* arg)
//{
//	for (int i = 0; i < Erow; i++) {
//		for (int j = nearplane_width / threads * 24; j < nearplane_width / threads * 25; j++) {
//			my_3Dvector l(eye, start25);
//			color[i + Enumber * Erow][j] = rayTracing(start25, l, 1); saveResult(i + Enumber * Erow, j);
//			start25.x += directionX.dx;
//			start25.z += directionX.dz;
//		}
//		cout << i << endl;
//		start25.x -= directionX.dx * nearplane_width / threads;
//		start25.y += directionY.dy;
//		start25.z = start25.z - directionX.dz * nearplane_width / threads + directionY.dz;
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//
//
//
//
////绘制内容
//void display(void) {
//	/*for (int i = 0; i < ModelNum; i++) {
//		for (int j = 0; j < model[i].face.size(); j++) {
//			if (model[i].face[j].n.dot_multiply(look) >= 0)
//				model[i].face[j].mList.clear();
//		}
//	}*/
//
//
//	//my_3Dvector directionX(-look.dz, 0, look.dx);
//	//directionX.dx /= directionX.len;
//	//directionX.dz /= directionX.len;
//	//my_3Dvector directionY(0, -look.dz, look.dy);
//	//directionY.dy /= directionY.len;
//	//directionY.dz /= directionY.len;
//	my_3Dvector DX(-look.dz, 0, look.dx);
//	directionX.dx = DX.dx / DX.len;
//	directionX.dz = DX.dz / DX.len;
//	my_3Dvector DY(0, look.dz, look.dy);
//	if (DY.dy >= 0) {
//		directionY.dy = DY.dy / DY.len;
//		directionY.dz = -DY.dz / DY.len;
//	}
//	else {
//		directionY.dy = -DY.dy / DY.len;
//		directionY.dz = DY.dz / DY.len;
//	}
//
//	my_homogeneous_point p(eye.x + look.dx * nearplane_distance - directionX.dx * nearplane_width / 2, eye.y + look.dy * nearplane_distance - directionY.dy * nearplane_height / 2
//		, eye.z + look.dz * nearplane_distance - directionX.dz * nearplane_width / 2 - directionY.dz * nearplane_height / 2);
//	start = p;
//	start.y += Erow * Enumber * directionY.dy;
//	start.z += Erow * Enumber * directionY.dz;
//	start2.x = p.x + nearplane_width / threads * directionX.dx;
//	start2.y = p.y + Erow * Enumber * directionY.dy;
//	start2.z = p.z + nearplane_width / threads * directionX.dz + Erow * Enumber * directionY.dz;
//
//	start3.x = p.x + nearplane_width / threads * directionX.dx * 2;
//	start3.y = p.y + Erow * Enumber * directionY.dy;
//	start3.z = p.z + nearplane_width / threads * directionX.dz * 2 + Erow * Enumber * directionY.dz;
//
//	start4.x = p.x + nearplane_width / threads * directionX.dx * 3;
//	start4.y = p.y + Erow * Enumber * directionY.dy;
//	start4.z = p.z + nearplane_width / threads * directionX.dz * 3 + Erow * Enumber * directionY.dz;
//
//	start5.x = p.x + nearplane_width / threads * directionX.dx * 4;
//	start5.y = p.y + Erow * Enumber * directionY.dy;
//	start5.z = p.z + nearplane_width / threads * directionX.dz * 4 + Erow * Enumber * directionY.dz;
//
//	start6.x = p.x + nearplane_width / threads * directionX.dx * 5;
//	start6.y = p.y + Erow * Enumber * directionY.dy;
//	start6.z = p.z + nearplane_width / threads * directionX.dz * 5 + Erow * Enumber * directionY.dz;
//
//	start7.x = p.x + nearplane_width / threads * directionX.dx * 6;
//	start7.y = p.y + Erow * Enumber * directionY.dy;
//	start7.z = p.z + nearplane_width / threads * directionX.dz * 6 + Erow * Enumber * directionY.dz;
//
//	start8.x = p.x + nearplane_width / threads * directionX.dx * 7;
//	start8.y = p.y + Erow * Enumber * directionY.dy;
//	start8.z = p.z + nearplane_width / threads * directionX.dz * 7 + Erow * Enumber * directionY.dz;
//
//
//	start9.x = p.x + nearplane_width / threads * directionX.dx * 8;
//	start9.y = p.y + Erow * Enumber * directionY.dy;
//	start9.z = p.z + nearplane_width / threads * directionX.dz * 8 + Erow * Enumber * directionY.dz;
//
//
//	start10.x = p.x + nearplane_width / threads * directionX.dx * 9;
//	start10.y = p.y + Erow * Enumber * directionY.dy;
//	start10.z = p.z + nearplane_width / threads * directionX.dz * 9 + Erow * Enumber * directionY.dz;
//
//	start11.x = p.x + nearplane_width / threads * directionX.dx * 10;
//	start11.y = p.y + Erow * Enumber * directionY.dy;
//	start11.z = p.z + nearplane_width / threads * directionX.dz * 10 + Erow * Enumber * directionY.dz;
//
//	start12.x = p.x + nearplane_width / threads * directionX.dx * 11;
//	start12.y = p.y + Erow * Enumber * directionY.dy;
//	start12.z = p.z + nearplane_width / threads * directionX.dz * 11 + Erow * Enumber * directionY.dz;
//
//	start13.x = p.x + nearplane_width / threads * directionX.dx * 12;
//	start13.y = p.y + Erow * Enumber * directionY.dy;
//	start13.z = p.z + nearplane_width / threads * directionX.dz * 12 + Erow * Enumber * directionY.dz;
//
//	start14.x = p.x + nearplane_width / threads * directionX.dx * 13;
//	start14.y = p.y + Erow * Enumber * directionY.dy;
//	start14.z = p.z + nearplane_width / threads * directionX.dz * 13 + Erow * Enumber * directionY.dz;
//
//	start15.x = p.x + nearplane_width / threads * directionX.dx * 14;
//	start15.y = p.y + Erow * Enumber * directionY.dy;
//	start15.z = p.z + nearplane_width / threads * directionX.dz * 14 + Erow * Enumber * directionY.dz;
//
//	start16.x = p.x + nearplane_width / threads * directionX.dx * 15;
//	start16.y = p.y + Erow * Enumber * directionY.dy;
//	start16.z = p.z + nearplane_width / threads * directionX.dz * 15 + Erow * Enumber * directionY.dz;
//
//	start17.x = p.x + nearplane_width / threads * directionX.dx * 16;
//	start17.y = p.y + Erow * Enumber * directionY.dy;
//	start17.z = p.z + nearplane_width / threads * directionX.dz * 16 + Erow * Enumber * directionY.dz;
//
//	start18.x = p.x + nearplane_width / threads * directionX.dx * 17;
//	start18.y = p.y + Erow * Enumber * directionY.dy;
//	start18.z = p.z + nearplane_width / threads * directionX.dz * 17 + Erow * Enumber * directionY.dz;
//
//	start19.x = p.x + nearplane_width / threads * directionX.dx * 18;
//	start19.y = p.y + Erow * Enumber * directionY.dy;
//	start19.z = p.z + nearplane_width / threads * directionX.dz * 18 + Erow * Enumber * directionY.dz;
//
//	start20.x = p.x + nearplane_width / threads * directionX.dx * 19;
//	start20.y = p.y + Erow * Enumber * directionY.dy;
//	start20.z = p.z + nearplane_width / threads * directionX.dz * 19 + Erow * Enumber * directionY.dz;
//
//	start21.x = p.x + nearplane_width / threads * directionX.dx * 20;
//	start21.y = p.y + Erow * Enumber * directionY.dy;
//	start21.z = p.z + nearplane_width / threads * directionX.dz * 20 + Erow * Enumber * directionY.dz;
//
//	start22.x = p.x + nearplane_width / threads * directionX.dx * 21;
//	start22.y = p.y + Erow * Enumber * directionY.dy;
//	start22.z = p.z + nearplane_width / threads * directionX.dz * 21 + Erow * Enumber * directionY.dz;
//
//	start23.x = p.x + nearplane_width / threads * directionX.dx * 22;
//	start23.y = p.y + Erow * Enumber * directionY.dy;
//	start23.z = p.z + nearplane_width / threads * directionX.dz * 22 + Erow * Enumber * directionY.dz;
//
//	start24.x = p.x + nearplane_width / threads * directionX.dx * 23;
//	start24.y = p.y + Erow * Enumber * directionY.dy;
//	start24.z = p.z + nearplane_width / threads * directionX.dz * 23 + Erow * Enumber * directionY.dz;
//
//	start25.x = p.x + nearplane_width / threads * directionX.dx * 24;
//	start25.y = p.y + Erow * Enumber * directionY.dy;
//	start25.z = p.z + nearplane_width / threads * directionX.dz * 24 + Erow * Enumber * directionY.dz;
//
//
//	if (isperspective == 0) {		//平行投影
//		///*my_homogeneous_point start(eye.x + look.dx * nearplane_distance - directionX.dx * nearplane_width / 2, eye.y + look.dy * nearplane_distance - directionY.dy * nearplane_height / 2
//		//	, eye.z + look.dz * nearplane_distance - directionX.dz * nearplane_width / 2 - directionY.dz * nearplane_height / 2);*/
//		//pthread_t t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25;
//		//pthread_create(&t1, NULL, rayTracing1, NULL);
//		//pthread_create(&t2, NULL, rayTracing2, NULL);
//		//pthread_create(&t3, NULL, rayTracing3, NULL);
//		//pthread_create(&t4, NULL, rayTracing4, NULL);
//		//pthread_create(&t5, NULL, rayTracing5, NULL);
//		//pthread_create(&t6, NULL, rayTracing6, NULL);
//		//pthread_create(&t7, NULL, rayTracing7, NULL);
//		//pthread_create(&t8, NULL, rayTracing8, NULL);
//		//pthread_create(&t9, NULL, rayTracing9, NULL);
//		//pthread_create(&t10, NULL, rayTracing10, NULL);
//		//pthread_create(&t11, NULL, rayTracing11, NULL);
//		//pthread_create(&t12, NULL, rayTracing12, NULL);
//		//pthread_create(&t13, NULL, rayTracing13, NULL);
//		//pthread_create(&t14, NULL, rayTracing14, NULL);
//		//pthread_create(&t15, NULL, rayTracing15, NULL);
//		//pthread_create(&t16, NULL, rayTracing16, NULL);
//		//pthread_create(&t17, NULL, rayTracing17, NULL);
//		//pthread_create(&t18, NULL, rayTracing18, NULL);
//		//pthread_create(&t19, NULL, rayTracing19, NULL);
//		//pthread_create(&t20, NULL, rayTracing20, NULL);
//		//pthread_create(&t21, NULL, rayTracing21, NULL);
//		//pthread_create(&t22, NULL, rayTracing22, NULL);
//		//pthread_create(&t23, NULL, rayTracing23, NULL);
//		//pthread_create(&t24, NULL, rayTracing24, NULL);
//		//pthread_create(&t25, NULL, rayTracing25, NULL);
//		//pthread_join(t1, NULL);
//		//pthread_join(t2, NULL);
//		//pthread_join(t3, NULL);
//		//pthread_join(t4, NULL);
//		//pthread_join(t5, NULL);
//		//pthread_join(t6, NULL);
//		//pthread_join(t7, NULL);
//		//pthread_join(t8, NULL);
//		//pthread_join(t9, NULL);
//		//pthread_join(t10, NULL);
//		//pthread_join(t11, NULL);
//		//pthread_join(t12, NULL);
//		//pthread_join(t13, NULL);
//		//pthread_join(t14, NULL);
//		//pthread_join(t15, NULL);
//		//pthread_join(t16, NULL);
//		//pthread_join(t17, NULL);
//		//pthread_join(t18, NULL);
//		//pthread_join(t19, NULL);
//		//pthread_join(t20, NULL);
//		//pthread_join(t21, NULL);
//		//pthread_join(t22, NULL);
//		//pthread_join(t23, NULL);
//		//pthread_join(t24, NULL);
//		//pthread_join(t25, NULL);
//	}
//	else if (isperspective == 1) {		//透视投影
//		/*my_homogeneous_point start(eye.x + look.dx * nearplane_distance - directionX.dx * nearplane_width / 2, eye.y + look.dy * nearplane_distance - directionY.dy * nearplane_height / 2
//			, eye.z + look.dz * nearplane_distance - directionX.dz * nearplane_width / 2 - directionY.dz * nearplane_height / 2);*/
//		pthread_t t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25;
//		pthread_create(&t1, NULL, rayTracing1, NULL);
//		pthread_create(&t2, NULL, rayTracing2, NULL);
//		pthread_create(&t3, NULL, rayTracing3, NULL);
//		pthread_create(&t4, NULL, rayTracing4, NULL);
//		pthread_create(&t5, NULL, rayTracing5, NULL);
//		pthread_create(&t6, NULL, rayTracing6, NULL);
//		pthread_create(&t7, NULL, rayTracing7, NULL);
//		pthread_create(&t8, NULL, rayTracing8, NULL);
//		pthread_create(&t9, NULL, rayTracing9, NULL);
//		pthread_create(&t10, NULL, rayTracing10, NULL);
//		pthread_create(&t11, NULL, rayTracing11, NULL);
//		pthread_create(&t12, NULL, rayTracing12, NULL);
//		pthread_create(&t13, NULL, rayTracing13, NULL);
//		pthread_create(&t14, NULL, rayTracing14, NULL);
//		pthread_create(&t15, NULL, rayTracing15, NULL);
//		pthread_create(&t16, NULL, rayTracing16, NULL);
//		pthread_create(&t17, NULL, rayTracing17, NULL);
//		pthread_create(&t18, NULL, rayTracing18, NULL);
//		pthread_create(&t19, NULL, rayTracing19, NULL);
//		pthread_create(&t20, NULL, rayTracing20, NULL);
//		pthread_create(&t21, NULL, rayTracing21, NULL);
//		pthread_create(&t22, NULL, rayTracing22, NULL);
//		pthread_create(&t23, NULL, rayTracing23, NULL);
//		pthread_create(&t24, NULL, rayTracing24, NULL);
//		pthread_create(&t25, NULL, rayTracing25, NULL);
//		pthread_join(t1, NULL);
//		pthread_join(t2, NULL);
//		pthread_join(t3, NULL);
//		pthread_join(t4, NULL);
//		pthread_join(t5, NULL);
//		pthread_join(t6, NULL);
//		pthread_join(t7, NULL);
//		pthread_join(t8, NULL);
//		pthread_join(t9, NULL);
//		pthread_join(t10, NULL);
//		pthread_join(t11, NULL);
//		pthread_join(t12, NULL);
//		pthread_join(t13, NULL);
//		pthread_join(t14, NULL);
//		pthread_join(t15, NULL);
//		pthread_join(t16, NULL);
//		pthread_join(t17, NULL);
//		pthread_join(t18, NULL);
//		pthread_join(t19, NULL);
//		pthread_join(t20, NULL);
//		pthread_join(t21, NULL);
//		pthread_join(t22, NULL);
//		pthread_join(t23, NULL);
//		pthread_join(t24, NULL);
//		pthread_join(t25, NULL);
//	}
//
//	glBegin(GL_POINTS);
//	for (int i = 0; i < nearplane_height; i++) {
//		for (int j = 0; j < nearplane_width; j++) {
//			glColor3f(color[i][j].data[0], color[i][j].data[1], color[i][j].data[2]);
//			glVertex2i(j - nearplane_width / 2, i - nearplane_height / 2);
//		}
//	}
//	glEnd();
//	glutSwapBuffers();
//}
//
//
////投影方式、modelview方式设置
//void reshape(int w, int h)
//{
//	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	if (w <= h)
//		glOrtho(-0.5 * nearplane_width, 0.5 * nearplane_width, -0.5 * nearplane_height * (GLfloat)nearplane_height / (GLfloat)nearplane_width, 0.5 * nearplane_height * (GLfloat)nearplane_height / (GLfloat)nearplane_width,
//			-nearplane_distance, nearplane_distance + 1000); //相对于视点
//	else
//		glOrtho(-0.5 * nearplane_width, 0.5 * nearplane_width, -0.5 * nearplane_height * (GLfloat)nearplane_width / (GLfloat)nearplane_height, 0.5 * nearplane_height * (GLfloat)nearplane_width / (GLfloat)nearplane_height,
//			-nearplane_distance, nearplane_distance + 1000);
//
//	//if (w <= h)
//	//	glFrustum(-0.5 * nearplane_width, 0.5 * nearplane_width, -0.5 * nearplane_height * (GLfloat)nearplane_height / (GLfloat)nearplane_width, 0.5 * nearplane_height * (GLfloat)nearplane_height / (GLfloat)nearplane_width,
//	//		nearplane_distance, farplane_distance); //相对于视点
//	//else
//	//	glFrustum(-0.5 * nearplane_width, 0.5 * nearplane_width, -0.5 * nearplane_height * (GLfloat)nearplane_width / (GLfloat)nearplane_height, 0.5 * nearplane_height * (GLfloat)nearplane_width / (GLfloat)nearplane_height,
//	//	nearplane_distance, farplane_distance);
//
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	/*gluLookAt(eye_x, eye_y, eye_z, look_x * INT_MAX, look_y * INT_MAX, look_z * INT_MAX, 0, 1, 0);*/
//}
//
////键盘交互事件
//void keyboard(unsigned char key, int x, int y)
//{
//	switch (key)
//	{
//	case 'w':
//	case 'W':
//	{
//		eye.x += cos(yaw) * speed;
//		eye.z += sin(yaw) * speed;
//		break;
//	}
//	case 's':
//	case 'S':
//	{
//		eye.x -= cos(yaw) * speed;
//		eye.z -= sin(yaw) * speed;
//		break;
//	}
//	case 'a':
//	case 'A':
//	{
//		eye.x += sin(yaw) * speed;
//		eye.z -= cos(yaw) * speed;
//		break;
//	}
//	case 'd':
//	case 'D':
//	{
//		eye.x -= sin(yaw) * speed;
//		eye.z += cos(yaw) * speed;
//		break;
//	}
//	case 't':
//	case 'T':
//	{
//		isperspective = 1 - isperspective;
//		break;
//	}
//	case 'g':
//	case 'G':
//	{
//		if (pitch < PI / 4)
//			pitch += PI / 10;
//		look.dy = sin(pitch);
//		look.dx = cos(pitch) * cos(yaw);
//		look.dz = cos(pitch) * sin(yaw);
//		break;
//	}
//	case 'b':
//	case 'B':
//	{
//		if (pitch > -PI / 4)
//			pitch -= PI / 10;
//		look.dy = sin(pitch);
//		look.dx = cos(pitch) * cos(yaw);
//		look.dz = cos(pitch) * sin(yaw);
//		break;
//	}
//	case 'v':
//	case 'V':
//	{
//		yaw -= PI / 10;
//		look.dy = sin(pitch);
//		look.dx = cos(pitch) * cos(yaw);
//		look.dz = cos(pitch) * sin(yaw);
//		break;
//	}
//	case 'n':
//	case 'N':
//	{
//		yaw += PI / 10;
//		look.dy = sin(pitch);
//		look.dx = cos(pitch) * cos(yaw);
//		look.dz = cos(pitch) * sin(yaw);
//		break;
//	}
//	case 27:
//		exit(0);
//		break;
//	}
//	/*reshape(nearplane_width, nearplane_height);*/
//	glutPostRedisplay();
//}
//
//
////主调函数
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowSize(nearplane_width, nearplane_height);
//	glutInitWindowPosition(100, 100);
//	glutCreateWindow("RayTracing");
//	init();
//	glutReshapeFunc(reshape);
//	glutDisplayFunc(display);
//	glutKeyboardFunc(keyboard);
//	/*glutPassiveMotionFunc(mouse);*/
//	glutMainLoop();
//	return 0;
//}
//
//
//
//
