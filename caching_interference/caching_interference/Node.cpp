 
#include "Node.h"
// 实现构造函数
Node::Node()		
{
	x_axis=0;
	y_axis=0;
	nodenum=0;
}

Node::Node(double x, double y)	
{
	x_axis=x;
	y_axis=y;
	nodenum=0;
}

Node::~Node()
{
	
}

//获得节点的横坐标
double Node::NodeGetXAxis() const
{
	return x_axis;
}

//获得节点的纵坐标
double Node::NodeGetYAxis() const
{
	return y_axis;
}

//获得节点标号
int Node::NodeGetnodenum() const
{
	return nodenum;
}

//设置节点横坐标
void Node::NodeSetXAxis(double x)
{
	x_axis = x;
}

//设置节点纵坐标
void Node::NodeSetYAxis(double y)
{
	y_axis = y;
}

//设置节点标号
void Node::NodeSetnodenum(int nodenumber)
{
	nodenum =nodenumber;
}

//显示构造的节点
void Node::ShowNode() const
{
	cout<< "节点" << this->NodeGetnodenum() << "的坐标为：（" << this->NodeGetXAxis() << "," << this->NodeGetYAxis()<<")" << endl;
}