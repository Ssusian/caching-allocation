#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include<ctime>
#include <math.h>
#include <fstream>
#include <conio.h>
#include <cassert>
#include <math.h>
using namespace std;
#define MaxRelayNum 5      //基站数
#define MaxUserNum  100  //用户数
#define MaxFileNum 200       //文件个
const int SubcarrierNum=25;    //RB数目
const int Cache_Max=20;        //缓存空间Cn,5%
const double γ= 0.7;          //文件受欢迎度的分布参数
const int RAN_MAX =100000; 
//const int SEED=200;
//记得精度的问题~~~

const int TRANSMISSION_DISTANCE = 50;         //基站的传输范围
const int INTERFERENCE_DISTANCE = 50;

const double Rate_Request =8.0;           //用户速率需求bit/s/Hz
const double Band = 0.18;               //单个信道的带宽180kHz
const int RANGE=50;                     //基站的传输半径
//const int H=225;
#define POWER 13.0103                         //发射功率dBm
#define T 1                           //门限

const int Mode_Num = 5000;               //预设的传输模式的个数
const int variable_num = 5000;           //预设的变量数
const int equation_num=MaxRelayNum;             //预设的等式矩阵的行数
const int inequality_num=5000;           //预设的不等式矩阵行数

const int MAX_NODENUM=MaxRelayNum+MaxUserNum;
const double Environmentalnoise=8.417*1e-16;    //环境噪声，单位是W

class Node
{
private:
	double x_axis; //节点横坐标
	double y_axis; //节点纵坐标
	int nodenum;//节点标号

public:
	Node();
	Node(double, double);
	~Node();
	double NodeGetXAxis() const;//获得节点的横坐标
	double NodeGetYAxis() const;//获得节点的纵坐标
	int NodeGetnodenum() const;//获得节点标号

	void NodeSetXAxis(double);
	void NodeSetYAxis(double);
	void NodeSetnodenum(int);
	void ShowNode() const;	
};


#endif 