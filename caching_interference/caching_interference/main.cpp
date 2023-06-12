//#include "Node.h"

#include "Request.h"
//#include "st.h"

//全局变量
	//基站缓存情况
	int Cache_data[MaxRelayNum][MaxFileNum];
 	//节点邻居矩阵，用于表示节点是否为邻居
	int NodeNeighborTable[MaxRelayNum][MaxUserNum];	
	//记录所有用户的传输模式
	int Mode_Table[Mode_Num][MaxRelayNum]; 
	//等式系数矩阵
	//int Matrix_equation[equation_num][variable_num];
	//不等式系数矩阵
	int Matrix_inequality[inequality_num][variable_num];
	//ln,i
	
 void main()
{
	
	int NodeNum=MAX_NODENUM;

	//节点数组：用户存储节点   P.S.:前MaxRelayNum个表示基站的数目；后MaxUserNum个表示用户的数目
	Node Nodesarray[MAX_NODENUM];
	//产生节点
	NodesGenerator(NodeNum,Nodesarray);        
	//描绘出产生的节点
	//print_node(NodeNum,Nodesarray);   

	//基站初始缓存状态
	//int Cache_data[MaxRelayNum][MaxFileNum];
	//int Cache_remain[MaxRelayNum];
	//Cache_Generator(Cache_data,Cache_remain);
	//Print_Cache(Cache_data,Cache_remain);

	//文件受欢迎度
	double File_Pro[MaxFileNum] = {0.0};
	Pro_Generator(File_Pro);
	//Print_Pro(File_Pro);
	//用户请求
	int User_Request[MaxUserNum][MaxFileNum]={0};
	//按文件受欢迎度产生
	Request_Generator(User_Request, File_Pro);
	//随机产生
	//Request_Generator(User_Request);
	//Print_Request(User_Request[0]);
	//将用户的文件请求输出到本地
	Out_Request(User_Request);

 	//节点邻居矩阵，用于表示节点是否为邻居
	//int NodeNeighborTable[MaxRelayNum][MaxUserNum];	
	//获得relay节点邻居表:行代表不同的relay节点；列代表不同的用户节点
	GetNodeNeighborTable(NodeNeighborTable[0],Nodesarray);
	//表示节点邻居表
	//Print_NodeNeighborTable(NodeNeighborTable[0]);

	//UserRelayTable 记录了每个用户可以连接的基站的数目
	int UserRelayArray[MaxUserNum] = {0};
	Get_UserRelayArray(NodeNeighborTable,UserRelayArray);
    //Print_UserRelayArray(UserRelayArray);

	//得到传输模式的矩阵
	//int Mode_Table[Mode_Num][MaxRelayNum]; 
	int User_Mode_Num[MaxUserNum];     //记录每个用户存在的传输模式的个数
	int Mode_Num_Real=Get_Mode_Table(NodeNeighborTable,Nodesarray,UserRelayArray,Mode_Table,User_Mode_Num);
	//Print_Mode_Table(Mode_Table,Mode_Num_Real);
	Out_Mode_Table(Mode_Table,Mode_Num_Real);   //将传输模式矩阵写入到本地文档中

		
	//计算在每一种传输模式下用户端可达的速率,将速率输出，缓存输出
	double Rate[Mode_Num]={0.0};
	Get_Rate(Rate,Mode_Num_Real,Mode_Table,User_Mode_Num,Nodesarray,NodeNeighborTable);
	Out_Rate(Rate,Mode_Num_Real);
	//Out_Cache(variable_number,Mode_Num_Real);

	//计算单接入下的吞吐量
	//double ST_rate[MaxUserNum] = {0.0};
	//ST_throughput(Rate, User_Mode_Num,ST_rate);
	//Print_ST(ST_rate);

    const int variable_number=Get_variable_number(User_Mode_Num);  //数学模型中实际的变量个数
	int Objective_function[variable_num]={0};                      //目标函数

	//输出目标函数：Objective_function		
	Get_Objective_function(Objective_function,NodeNeighborTable,User_Request,Cache_data,Mode_Table,Mode_Num_Real,User_Mode_Num);
	Print_Objective_function(Objective_function,variable_number);

	//输出等式矩阵系数：Matrix_equation
	int Matrix_equation[equation_num][variable_num];
	int Matrix_equation_value[MaxRelayNum];
	int equation_number = MaxRelayNum;
	Get_Matrix_equation(Matrix_equation_value,Matrix_equation, Mode_Table, Mode_Num_Real,equation_number,User_Mode_Num);
	Print_Matrix_equation(Matrix_equation_value,Matrix_equation,equation_number,variable_number);
	
	//输出不等式矩阵系数：Matrix_inequality 	
	//int Matrix_inequality[inequality_num][variable_num];
	int Matrix_inequality_value[inequality_num];         // 不等式矩阵值
    const int inequality_number=Get_Matrix_inequality(Mode_Table,Matrix_inequality_value,Mode_Num_Real,User_Mode_Num,NodeNeighborTable,Rate,Cache_data, Matrix_inequality);
    Print_Matrix_inequality(Matrix_inequality_value,inequality_number,variable_number, Matrix_inequality);
	
   //getchar();
}










