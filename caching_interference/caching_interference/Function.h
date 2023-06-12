#ifndef FUNCTION_H_
#define FUNCTION_H_
#include "Node.h"

//第一种生成方式,产生节点坐标
void NodesGenerator(int num,Node *p);
bool Judge_Node(double x1,double y1,Node *q);
/*
//第二种生成方式
void NodesGenerator1(int linenumber,int columnnumber,Node *p)
{
	double x,y;		
	for(int l=0;l<linenumber; l++)			//行
	{
		for(int m=0;m<columnnumber; m++)		//列
		{
			x=(double)l*10;
			y=(double)m*10;
			*p=Node(x,y);
			p++;
		}
	}
		
}*/

//描绘出产生的节点
void print_node(int num,Node *p);

//产生与描绘基站缓存状态
void Cache_Generator(int (& Cache_data)[MaxRelayNum][MaxFileNum],int *Cache_remain);
void Print_Cache(int (& Cache_data)[MaxRelayNum][MaxFileNum],int *Cache_remain);

//用户请求
//void Request_Generator(int (& User_Request)[MaxUserNum][MaxFileNum]);
//void Print_Request(int *User_Request);

//比较两个节点之间的距离
double DistanceCalculation(Node src,Node dest);
//判断两个节点之间是否邻近
bool NodeDistanceJudgement(Node src,Node dest);
//将dBm转换为W
double Dbm_To_W(double dBm);
//获得邻居矩阵
void GetNodeNeighborTable(int * NodeNeighborTable,Node *Nodesarray);
void Print_NodeNeighborTable(int *NodeNeighborTable);

//记录每个用户可连接的基站的数目
void Get_UserRelayArray(int (& NodeNeighborTable)[MaxRelayNum][MaxUserNum],int *UserRelayArray);
void Print_UserRelayArray(int *UserRelayNum);

//计算传输模式，得到传输模式的矩阵

bool Judge_Temp(int *Temp,int num1,int (& NodeNeighborTable)[MaxRelayNum][MaxUserNum]);
int Get_Mode_Table(int (& NodeNeighborTable)[MaxRelayNum][MaxUserNum],Node *Nodesarray,int *UserRelayArray,int (& Mode_Table)[Mode_Num][MaxRelayNum],int *User_Mode_Num);
int Get_variable_number(int *User_Mode_Num);
void Print_Mode_Table(int (& Mode_Table)[Mode_Num][MaxRelayNum],int Mode_Num_Real);
void Out_Mode_Table(int (& Mode_Table)[Mode_Num][MaxRelayNum],int Mode_Num_Real);

//计算每一种传输模式下用户端可达的数据速率,速率输出，缓存输出
double Calculate_Power(Node dest,Node src,int (& Power_Relay)[MaxRelayNum][MaxUserNum]);
double DistanceCalculation(Node dest,Node src);
void Get_Rate(double *Rate,int Mode_Num_Real,int (& Mode_Table)[Mode_Num][MaxRelayNum],int *User_Mode_Num,Node *Nodesarray,int(& NodeNeighborTable)[MaxRelayNum][MaxUserNum]);
void Out_Rate(double *Rate,int Mode_Num_Real);
//void Out_Cache(int variable_number,int Mode_Num_Real);

//目标函数：
void Get_Objective_function(int (& Objective_function)[variable_num],int (& NodeNeighborTable)[MaxRelayNum][MaxUserNum],int (& User_Request)[MaxUserNum][MaxFileNum],int (& Cache_data)[MaxRelayNum][MaxFileNum],int (& Mode_Table)[Mode_Num][MaxRelayNum],int Mode_Num_Real,int *User_Mode_Num);
void Print_Objective_function(int (& Objective_function)[variable_num],int variable_number);

//等式约束：
void Get_Matrix_equation(int (& Matrix_equation_value)[equation_num], int ( & Matrix_equation)[equation_num][variable_num],int ( & Mode_Table)[Mode_Num][MaxRelayNum],int Mode_Num_Real,int equation_number, int *User_Mode_Num);
void Print_Matrix_equation(int (& Matrix_equation_value)[equation_num], int ( & Matrix_equation)[equation_num][variable_num],int equation_number,int variable_number);


//不等式约束：
int Get_Matrix_inequality(int (& Mode_Table)[Mode_Num][MaxRelayNum],int (& Matrix_inequality_value)[inequality_num],int Mode_Num_Real,int *User_Mode_Num,int(& NodeNeighborTable)[MaxRelayNum][MaxUserNum],double *Rate,int (& Cache_data)[MaxRelayNum][MaxFileNum], int(& Matrix_inequality)[inequality_num][variable_num]);
void Print_Matrix_inequality(int (&Matrix_inequality_value)[inequality_num],int inequality_number,int variable_number, int(& Matrix_inequality)[inequality_num][variable_num]);	


#endif 