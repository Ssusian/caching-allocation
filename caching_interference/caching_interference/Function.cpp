//#include "Node.h"
#include "Function.h"
#include <math.h>


//两个基站的生成方式
void NodesGenerator(int num,Node *p)
{         

	srand((unsigned)time(0)) ;	
	//两个基站坐标
	//p[0] = Node(50,50);
	//p[1] = Node(125,50);
	//三个基站坐标
	p[0] = Node(50,50);
	p[1] = Node(125,50);
	p[2] = Node(200,50);
	p[3] = Node(75,125);
	p[4] = Node(180,125);
	/*p++=Node(125,50);
	*p++=Node(125,100);
	*p++=Node(50,100);
	*p++=Node(100,50);
	*p++=Node(100,150);*/
	int count=0;
	
    for(int i=0;i<5000;i++)
    {

		//double x=rand()%175;      //两个基站时，用户坐标的产生
		double x=rand()%250;        //三个基站，用户坐标的产生
	    double y=rand()%175;	
		
		for(int j=0;j<MaxRelayNum;j++)
		{
          double x1=p[j].NodeGetXAxis();
		  double y1=p[j].NodeGetYAxis();
		  double distance=sqrt(pow((x-x1),2) + pow((y-y1),2));
		  if(distance<TRANSMISSION_DISTANCE)
		  {
			  p[count+MaxRelayNum] = Node(x,y);
			  count++;
			  break;
		  }

		}	
        if(count==num-MaxRelayNum)
		 {
		   break;
		 }
        
	}			
}



//描绘出产生的节点
void print_node(int num,Node *p)
{ 
	int nodenumber=0;
	for(int i=0;i<num;i++)
	{
		++nodenumber;
		p[i].NodeSetnodenum(nodenumber);
		p[i].ShowNode();
	}
    cout<<endl;
}

//产生基站初始缓存情况,指定基站或随机缓存部分文件，或缓存全为零(有缓存时，用方法一；没有缓存时，用方法二)
void Cache_Generator(int (& Cache_data)[MaxRelayNum][MaxFileNum],int *Cache_remain)
{
	//初始化
	for(int i=0;i<MaxRelayNum;i++)
	{
		for(int j=0;j<MaxFileNum;j++)
		{
			 Cache_data[i][j]=0;
		}
		Cache_remain[i]=Cache_Max;
	}
	
	//方法一;随机产生	
/*	srand((unsigned)time(0)) ;
	for(int i=0;i<MaxRelayNum;i++)
    {	  
	  int count = 0;
	  for(int j=0;j<MaxFileNum;j++)
	  {		
		int a = rand()%100;
		if(a<60)
		{
		  Cache_data[i][j]=0;
		}
		else
		{
	     Cache_data[i][j]=1;
		 count++;    //count记录了当前基站占用了多少缓存空间
		}
		if(count==Cache_Max)
		{
			break;
		}
	  }
	  Cache_remain[i] = Cache_Max - count;
    }*/
	//方法二：缓存全为零
	/*for(int i=0;i<MaxRelayNum;i++)
	{
		for(int j=0;j<MaxFileNum;j++)
		{
			Cache_data[i][j]=0;
		}
	}*/
}
//描绘基站当前的缓存状态
void Print_Cache(int (& Cache_data)[MaxRelayNum][MaxFileNum],int *Cache_remain)
{
	cout<<"基站当前的缓存状态为： "<<endl;
	for(int i=0;i<MaxRelayNum;i++)
	{
		for(int j=0;j<MaxFileNum;j++)
		{
			cout<<Cache_data[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	cout<<"基站当前可用的缓存为： "<<endl;
	for(int i=0;i<MaxRelayNum;i++)
	{
		cout<<*(Cache_remain++)<<" ";
	}
	cout<<endl<<endl;
}

//用户请求,在另一个request.h中写了随机请求和按受欢迎度请求，这段不需要了
/*void Request_Generator(int (& User_Request)[MaxUserNum][MaxFileNum])
{
	srand((unsigned)time(0)) ;
	for(int i=0;i<MaxUserNum;i++)
    {
	  for(int j=0;j<MaxFileNum;j++)
	  {

		int temp = rand()%MaxFileNum;
		User_Request[i][temp] = 1;   //保证每个统计的每个用户都有请求
		break;
	  }
    }
}
void Print_Request(int *User_Request)
{
	cout<<"用户请求为 "<<endl;
	for(int i=0;i<MaxUserNum;i++)
	{
		for(int j=0;j<MaxFileNum;j++)
		{
		    cout<<*(User_Request++)<<" ";
		}
		cout<<endl;		
	}
	cout<<endl;	
}*/


//判断两个节点之间是否邻近
bool NodeDistanceJudgement(Node src,Node dest)
{
	//TRANSMISSION_DISTANCE表示两节点间构成链路的最大距离，返回值为true，表示两节点能构成链路；false则不能
	if(DistanceCalculation(src,dest)<=TRANSMISSION_DISTANCE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GetNodeNeighborTable(int *NodeNeighborTable,Node *Nodesarray)
{
	for(int i=0;i<MaxRelayNum;i++)
	{
		for(int j=0;j<MaxUserNum;j++)
		{
			if(NodeDistanceJudgement(Nodesarray[j+MaxRelayNum],Nodesarray[i]))
			{
			   *NodeNeighborTable=1;
			}
			else
			{
				*NodeNeighborTable=0;
			}
			NodeNeighborTable++;
		}
	}

}

//表示节点邻居表
void Print_NodeNeighborTable(int *NodeNeighborTable)
{
	cout<<"用户与基站的邻接关系: "<<endl;
	for(int i=0;i<MaxRelayNum;i++)
	{
		for(int j=0;j<MaxUserNum;j++)
		{
		    cout<<*(NodeNeighborTable++)<<" ";
		}
		cout<<endl;		
	}
	cout<<endl;	
}

//UserRelayTable是一维数组，记录每个用户可连接的基站的数目
void Get_UserRelayArray(int (& NodeNeighborTable)[MaxRelayNum][MaxUserNum],int *UserRelayArray)
{
	 for(int i=0;i<MaxUserNum;i++)
	{
		int a=0;
	    for(int j=0;j<MaxRelayNum;j++)
		{
		    if(NodeNeighborTable[j][i]==1)
			{
			    a = a+1;
			}
		}
		UserRelayArray[i]=a;
	}
}
//输出UserRelayTable
void Print_UserRelayArray(int *UserRelayArray)
{
	cout<<"用户可连接的基站数目为： "<<endl;
	for(int i=0;i<MaxUserNum;i++)
	{
		cout<<UserRelayArray[i]<<" ";
	}
	cout<<endl;
}


//计算传输模式矩阵,采用了CoMP技术的
 int Get_Mode_Table(int (& NodeNeighborTable)[MaxRelayNum][MaxUserNum],Node *Nodesarray,int *UserRelayArray,int (& Mode_Table)[Mode_Num][MaxRelayNum],int *User_Mode_Num)
{
	//初始化
	for(int m=0;m<Mode_Num;m++)
	{
		for(int n=0;n<MaxRelayNum;n++)
		{
			Mode_Table[m][n]=0;
		}
	}
	for(int n=0;n<MaxUserNum;n++)
	{
		User_Mode_Num[n]=0;
	}

	int mode_num_real=0;	//记录实际产生了多少个传输模式
    for(int i=0;i<MaxUserNum;i++)
	{
	   
		 if(UserRelayArray[i]==1)   //用户只有一个邻接基站
		 {
		     User_Mode_Num[i]=1;
			 for(int j=0;j<MaxRelayNum;j++)
			 {
			    if(NodeNeighborTable[j][i]==1)
			    { 
			        Mode_Table[mode_num_real][j]=1;
				    mode_num_real++;
				    break;
			    }	    
		     }
	     }
		 else        //用户有多个邻接基站
	      {
	         int a=0;                         //用于记录用户i一共会有多少种传输模式
             int Temp[MaxRelayNum]={0};      //用于临时存放用户i的一种传输模式
			 fill_n(Temp,MaxRelayNum,1);     //Temp初始元素全部为1.从有多个基站的传输模式开始，逐渐减少基站
			 int b=1;
			 for(int m=0;m<MaxRelayNum;m++)
			 {
				 b=b*2;
			 }			 
	         for(int k=0;k<(b-1);k++)       //Temp不会执行到全0的情况
			 {

				 int flag=1;
				 for(int m=0;m<MaxRelayNum;m++)           //判断传输模式中的基站是否为用户的邻接基站
				  {
					
                    if(Temp[m]==1 && NodeNeighborTable[m][i]==1)   
	                {		              			           
						continue;					              
	                 }
					else if(Temp[m]==1 && NodeNeighborTable[m][i]==0)
					{
						flag=0;
					    break;
					}
                  }
				 if(flag==1)         //说明传输模式是可行的
				 {
					 for(int g=0;g<MaxRelayNum;g++)
					 {
						 Mode_Table[mode_num_real][g]=Temp[g];
					 }
					 mode_num_real++;
					 a++;
				 }
				 //修改Temp的值
				 Temp[0]=Temp[0]-1;
				 if(Temp[0]<0)
				 {
					 int j=1;
					 while(Temp[j]!=1)
					 {
						 j++;
					 }
					 Temp[j]=0;
					 for(int e=0;e<j;e++)
					 {
						 Temp[e]=1;
					 } 
				 }
			 }
			
			User_Mode_Num[i]=a;	 
		 }
	    }	   		
		
	  
	ofstream file;
	file.open("传输模式个数.txt");
	file<<mode_num_real;
	file.close();
	cout<<"传输模式的个数为： "<<mode_num_real<<endl;	
	return mode_num_real;
}


//计算传输模式矩阵,没采用CoMP技术的
/*int Get_Mode_Table(int (& NodeNeighborTable)[MaxRelayNum][MaxUserNum],Node *Nodesarray,int *UserRelayArray,int (& Mode_Table)[Mode_Num][MaxRelayNum],int *User_Mode_Num)
{
	//初始化
	for(int m=0;m<Mode_Num;m++)
	{
		for(int n=0;n<MaxRelayNum;n++)
		{
			Mode_Table[m][n]=0;
		}
	}
	for(int n=0;n<MaxUserNum;n++)
	{
		User_Mode_Num[n]=0;
	}

	int mode_num_real=0;	//记录实际产生了多少个传输模式
    for(int i=0;i<MaxUserNum;i++)
	{
	   
		 if(UserRelayArray[i]==1)   //用户只有一个邻接基站
		 {
		     User_Mode_Num[i]=1;
			 for(int j=0;j<MaxRelayNum;j++)
			 {
			    if(NodeNeighborTable[j][i]==1)
			    { 
			        Mode_Table[mode_num_real][j]=1;
				    mode_num_real++;
				    break;
			    }	    
		     }
	     }
		 else        //用户有多个邻接基站
	      {
	         int a=0;                         //用于记录用户i一共会有多少种传输模式
	         for(int k=0;k<MaxRelayNum;k++)       //
			 {

				 if(NodeNeighborTable[k][i]==1)
				 {
					 Mode_Table[mode_num_real][k]=1;
					 mode_num_real++;
					 a++;
				 }
			 }			
			User_Mode_Num[i]=a;	 
		  }
	  }	   		
		
	  
	ofstream file;
	file.open("传输模式个数.txt");
	file<<mode_num_real;
	file.close();
	cout<<"传输模式的个数为： "<<mode_num_real<<endl;	
	return mode_num_real;
}*/
 
 //判断传输模式Temp传输模式是否成立
/*bool Judge_Temp(int *Temp,int num1,int (& NodeNeighborTable)[MaxRelayNum][MaxUserNum])
 {
	 int flag=0;
	 for(int i=0;i<MaxRelayNum;i++)
	 {
		 while(Temp[i]==1)
		 {
			 if(NodeNeighborTable[i][num1]==0)
			 {
				 flag=1;
			 }
		 }
	 }
	 if(flag==0)
	 {
		 return true;
	 }
	 else
	 {
		 return false;
	 }
 }*/

//输出Mode_Table
void Print_Mode_Table(int (& Mode_Table)[Mode_Num][MaxRelayNum],int Mode_Num_Real)
{
	cout<<"传输模式矩阵为： "<<endl;
	for(int i=0;i<Mode_Num_Real;i++)
	{
		for(int j=0;j<MaxRelayNum;j++)
		{
			cout<<Mode_Table[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

//将传输模式矩阵写入到本地文档中
void Out_Mode_Table(int (& Mode_Table)[Mode_Num][MaxRelayNum],int Mode_Num_Real)
{
	ofstream file;
	file.open("传输模式矩阵.txt");
	for(int i=0;i<Mode_Num_Real;i++)
	{
		for(int j=0;j<MaxRelayNum;j++)
		{
			file<<Mode_Table[i][j]<<" ";
		}
		file<<endl;
	}
	file.close();
}

//计算每一种传输模式下用户端可达的数据速率

//计算在用户dest处接收到的基站src发送的功率的大小
double Calculate_Power(Node dest,Node src)   //用户，基站
{
	double temp=0.0;
	double power=0.0;
	//double b = pow(10,2) * pow(1.5,2);
	//power=(POWER* b)/( pow (DistanceCalculation(dest,src) , 4 ));
	double distan = DistanceCalculation(dest,src)/1000;     //距离，km
	temp = POWER - 152-36.7*log10(distan);                //功率dBm	
	power = Dbm_To_W(temp);                                //将dBm转换为W 
	return power;
}

//将dBm转换为W
double Dbm_To_W(double dBm)
{
	double mW = pow (10.0, dBm/10.0);
    return mW / 1000.0;
}

//计算用户dest到基站src之间的距离
double DistanceCalculation(Node src,Node dest)
{         
	//计算节点src和节点dest之间的距离
	double xy_distance=0;
	double x_src, y_src, x_dest, y_dest; 
	x_src = src.NodeGetXAxis();
	y_src = src.NodeGetYAxis();
	x_dest = dest.NodeGetXAxis();
	y_dest = dest.NodeGetYAxis();
	xy_distance =sqrt(pow((x_dest - x_src),2) + pow((y_dest- y_src),2));
	return xy_distance;
}


void Get_Rate(double *Rate,int Mode_Num_Real,int (& Mode_Table)[Mode_Num][MaxRelayNum],int *User_Mode_Num,Node *Nodesarray,int (& NodeNeighborTable)[MaxRelayNum][MaxUserNum])
{
    //cout<<"各传输模式下的速率为："<<endl;
    int temp1=0;

	for(int i=0;i<MaxUserNum;i++)
	{
		for(int j=temp1;j<temp1+User_Mode_Num[i];j++)
		{
			double temp2=0.0;
			double temp3=0.0;
			for(int k=0;k<MaxRelayNum;k++)
			{
				
				
				if((Mode_Table[j][k]==1) && (NodeNeighborTable[k][i]==1))                       //有用信号
				{
					temp2=temp2+Calculate_Power(Nodesarray[i+MaxRelayNum],Nodesarray[k]);      //这里的power的单位必须是W
				}
				else if((Mode_Table[j][k]==0) && (NodeNeighborTable[k][i]==1))                 //干扰信号
				{
					temp3=temp3+Calculate_Power(Nodesarray[i+MaxRelayNum],Nodesarray[k]);
				}

			}			
			double sinr = temp2/(temp3 + Environmentalnoise);
			Rate[j] = log10(1+sinr)/log10(2.0);	 //如果计算的是频谱效率则不用乘以带宽，Rate[j] = Band * log10(1+sinr)/log10(2.0);
			//cout<<Rate[j]<<endl;
		}
		temp1=temp1+User_Mode_Num[i];
	}
}

//将每种传输模式下的速率输出到文档中
void Out_Rate(double *Rate,int Mode_Num_Real)
{
	ofstream file;		
	file.open("速率.txt");
	for(int j=0;j<Mode_Num_Real;j++)
	{
		file<<*(Rate++)<<" ";
	}	
	file.close();
}

//将实际变量中缓存决策的部分设为1输出，用于计算缓存消耗
/*void Out_Cache(int variable_number,int Mode_Num_Real)
{
	ofstream file;	
	int a[variable_num]={0};
	int temp = Mode_Num_Real*SubcarrierNum*2 + Mode_Num_Real + MaxUserNum*SubcarrierNum;
	for(int i=0;i<MaxRelayNum*MaxFileNum;i++)
	{
		a[temp+i] =1;
	}
	file.open("缓存文件.txt");
	for(int j=0;j<variable_number;j++)
	{
		file<<a[j]<<" ";
	}
	file.close();
}*/

//得到数学模型中变量的个数
int Get_variable_number(int *User_Mode_Num)

{
    int variable_number=0;
	int a=0;
	int b=0;
	for(int i=0;i<MaxUserNum;i++)
	 {
	    a=User_Mode_Num[i]+a;
		//b=b+User_Mode_Num[i]*SubcarrierNum;
	 }
	//variable_number=a;     //ln,i已知
	variable_number=a+MaxRelayNum*MaxFileNum;  //ln,i是变量
	//cout<<"总变量个数为： "<<variable_number<<endl;
	return variable_number;
}

//初始化目标函数：
void Get_Objective_function(int (& Objective_function)[variable_num],int (& NodeNeighborTable)[MaxRelayNum][MaxUserNum],int (& User_Request)[MaxUserNum][MaxFileNum],int (& Cache_data)[MaxRelayNum][MaxFileNum],int (& Mode_Table)[Mode_Num][MaxRelayNum],int Mode_Num_Real,int *User_Mode_Num)
{
	//初始化
	for(int i=0;i<variable_num;i++)
	{
		Objective_function[i]=0;
	}	
	int temp = 0;
   // int fore = Mode_Num_Real*SubcarrierNum;
	//对y的系数
    for(int i=0;i<MaxUserNum;i++)
    {
		int flag=0;
		while(User_Request[i][flag]==0)
		{
			flag = flag+1;       //flag记录了用户i请求下标为flag的文件
		} 
        for(int j=temp;j<temp+User_Mode_Num[i];j++)
	    {
		   	int temp1 = 0;              
		    for(int k=0;k<MaxRelayNum;k++)
		    {
			    if(Mode_Table[temp][k]==1)   //am,i=1用户请求文件 并且wn,i=0基站没有缓存
			    {
				    temp1++;
			    }
		    }	
		    Objective_function[j] =temp1; 		    
	    }
		temp=temp+User_Mode_Num[i];
    }
	//对L的系数(有缓存时，采用有缓存的代码；没有缓存时，将以下这段都隐藏; 缓存已知时，将以下代码隐藏)
	int fore1 = Mode_Num_Real;
   //有缓存
	for(int i=0;i<MaxRelayNum;i++)
    {
	    for(int j=0;j<MaxFileNum;j++)
	    {
		    int temp2 = 0;
		    for(int k=0;k<MaxUserNum;k++ )
		    {
			    if((NodeNeighborTable[i][k]==1) && (User_Request[k][j]==1))
			    {
				    temp2++;
			    }
		    }
	        Objective_function[fore1 + i*MaxFileNum + j] = -temp2;
	    }
    }
	//没有缓存,l的系数都是0,或者将对l的系数以下这段，都隐藏
	/*for(int i=0;i<MaxRelayNum;i++)
	{
		for(int j=0;j<MaxFileNum;j++)
		{
			Objective_function[fore1 + i*MaxFileNum + j] = 0;
		}
	}*/
}


//输出目标函数：
void Print_Objective_function(int (& Objective_function)[variable_num],int variable_number)
{
	ofstream file;
	file.open("目标函数.txt");
	for(int i=0;i<variable_number;i++)
	{
		//cout<<Objective_function[i]<<" ";
		file<<Objective_function[i]<<" ";
	}
	//cout<<endl;
	file.close();
	//cout<<"目标函数中变量个数为; "<<variable_number<<endl;
}

//得到等式矩阵系数
void Get_Matrix_equation(int ( & Matrix_equation_value)[equation_num], int ( & Matrix_equation)[equation_num][variable_num],int ( & Mode_Table)[Mode_Num][MaxRelayNum],int Mode_Num_Real,int equation_number,int *User_Mode_Num)
{
	//等式矩阵初始化
	for(int i=0;i<equation_num;i++)
	{
		for(int j=0;j<variable_num;j++)
		{
			Matrix_equation[i][j]=0;
		}
	}	
	//等式矩阵值初始化
	for(int i=0; i<MaxRelayNum; ++i)
	{
		Matrix_equation_value[i] = 0;
	}
	/*int temp = 0;
	//等式1 ，y传输模式选择
	for(int i = 0;i<equation_number;i++)
    {
		for(int j=temp;j<temp+User_Mode_Num[i];j++)
		{
	         Matrix_equation[equation_number][j] = 1;
	    }

	    temp = temp + User_Mode_Num[i];
    }*/
	//Ln,i基站缓存
   int fore_num2 = Mode_Num_Real;
   int temp2=0;
   for(int i=0;i<MaxRelayNum;i++)
   {	 
	 for(int j=i*MaxFileNum;j<(i+1)*MaxFileNum;j++)
	 {
		Matrix_equation[i][fore_num2 + j]=1;
	 }	
	Matrix_equation_value[i] = Cache_Max;
	temp2=temp2+MaxFileNum;
   }
	//cout<<"等式的数目为： "<<equation_number<<endl;
}    

//将等式矩阵和等式矩阵值写入到文档
void Print_Matrix_equation(int ( & Matrix_equation_value)[equation_num],int ( & Matrix_equation)[equation_num][variable_num],int equation_number,int variable_number)
{
	cout<<"等式行列数： "<<equation_number<<" "<<variable_number<<endl;
	ofstream file;
	file.open("等式矩阵.txt");
	for(int i=0;i<equation_number;i++)
	{
		for(int j=0;j<variable_number;j++)
		{
			//cout<<Matrix_equation[i][j]<<" ";
			file<<Matrix_equation[i][j]<<" ";
		}
		//cout<<endl;
		file<<endl;
	}
	file.close();
	file.open("等式矩阵值.txt");
	for(int i=0;i<MaxRelayNum;i++)
	{
		file<<Matrix_equation_value[i]<<endl;	
	}
	file.close();	
}


int Get_Matrix_inequality(int (& Mode_Table)[Mode_Num][MaxRelayNum],int (& Matrix_inequality_value)[inequality_num],int Mode_Num_Real,int *User_Mode_Num,int(& NodeNeighborTable)[MaxRelayNum][MaxUserNum],double *Rate,int (& Cache_data)[MaxRelayNum][MaxFileNum], int(& Matrix_inequality)[inequality_num][variable_num])
{
	//不等式矩阵初始化
	for(int i=0;i<inequality_num;i++)           
	{
		for(int j=0;j<variable_num;j++)
		{
			Matrix_inequality[i][j]=0;         //不等式系数矩阵 
		}
	}	
	int inequality_number = 0;                 //用于记录实际产生的不等式个数

	//不等式矩阵值初始化
	for(int i=0;i<inequality_num;i++)  
	{
		Matrix_inequality_value[i]=0;         
	}


	//开始得到不等式矩阵
   // int fore_num = Mode_Num_Real * SubcarrierNum;
	int temp = 0;
	//不等式1 ，y传输模式选择
	for(int i = 0;i<MaxUserNum;i++)
    {
		for(int j=temp;j<temp+User_Mode_Num[i];j++)
		{
	         Matrix_inequality[inequality_number][j] = 1;
	    }
	    Matrix_inequality_value[inequality_number] = 1;
	    inequality_number++;
	    temp = temp + User_Mode_Num[i];
    }
	//cout<<inequality_number<<endl;

	//不等式2，λ信道分配
  /* int fore_num1 = Mode_Num_Real * SubcarrierNum*2 + Mode_Num_Real;
   for(int i=0;i<MaxRelayNum;i++)
   {
	 int user_num = 0;
	 while(NodeNeighborTable[i][user_num]==0)
	 {
		 user_num++;
	 }
	 if(user_num<MaxUserNum)  //说明在基站i的范围内有用户
	 {
		 for(int j=0;j<SubcarrierNum;j++)
	      {
	        for(int k=0;k<MaxUserNum;k++)
		    {
		      if(NodeNeighborTable[i][k]==1)
		       {
			    Matrix_inequality[inequality_number][fore_num1 + k*SubcarrierNum + j] = 1;
		       }
		    }
		   Matrix_inequality_value[inequality_number] = 1;
		   inequality_number++;		
	     }    
     }
   }*/
   //cout<<inequality_number<<endl;

  //不等式3，L基站缓存策略,（在ln,i缓存已知时，不等式3需要隐藏）
 /*  int fore_num2 = Mode_Num_Real;
   int temp2=0;
   for(int i=0;i<MaxRelayNum;i++)
   {	 
	 for(int j=temp;j<(i+1)*MaxFileNum;j++)
	 {
		Matrix_inequality[inequality_number][fore_num2 + j]=1;
	 }	
	Matrix_inequality_value[inequality_number] = Cache_Max;
	inequality_number++;
	temp2=temp2+MaxFileNum;
   }*/
   //cout<<inequality_number<<endl;

   //不等式4，速率需求
   
   int temp3=0;
   for(int i=0;i<MaxUserNum;i++)
   {
	 for(int j=temp3; j<temp3+User_Mode_Num[i];j++)
	 {

		  Matrix_inequality[inequality_number][j] = - (int)Rate[temp3];	   // - (int)(Rate[temp3]*1000), 将速率乘以1000，mbps转换为kbps
		  
		
	 }
	Matrix_inequality_value[inequality_number] = -Rate_Request;
	inequality_number++;
	temp3=temp3+User_Mode_Num[i];
   }
  //cout<<inequality_number<<endl;

 /*  //不等式5 y与Q
   int fore_num4 = Mode_Num_Real * SubcarrierNum;
   int temp4 = 0;
   for(int i=0;i<MaxUserNum;i++)
   {
	 for(int j=temp4;j<temp4+User_Mode_Num[i];j++)
	  {
		for(int k=0;k<SubcarrierNum;k++)
		{
		   Matrix_inequality[inequality_number][fore_num4 + j*SubcarrierNum + k] = -1;
		   Matrix_inequality[inequality_number][fore_num4 * 2 + j] = -1;
		   Matrix_inequality_value[inequality_number] = -1;
		   inequality_number++;
		}		
	  }
     temp4 = temp4+User_Mode_Num[i];
   }
   //cout<<inequality_number<<endl;s

   //不等式6 λ与Q
   int fore_num5 = Mode_Num_Real * SubcarrierNum;
   int temp5 = 0;
   for(int i=0;i<MaxUserNum;i++)
   {
	 for(int j=temp5;j<temp5+User_Mode_Num[i];j++)
	  {
		for(int k=0;k<SubcarrierNum;k++)
		 {
		   Matrix_inequality[inequality_number][fore_num5 + j*SubcarrierNum + k ] = -1;
		   Matrix_inequality[inequality_number][fore_num5*2 + Mode_Num_Real + i*SubcarrierNum + k] = -1;
		   Matrix_inequality_value[inequality_number] = -1;
		   inequality_number++;
		 }
	  }
	temp5 = temp5+User_Mode_Num[i];	
   }
  //cout<<inequality_number<<endl;

   //不等式7，y，λ与Q
   int fore_num_6 = Mode_Num_Real * SubcarrierNum;
   int temp6 = 0;
   for(int i=0;i<MaxUserNum;i++)
    {
	  for(int j=temp6;j<temp6+User_Mode_Num[i];j++)
	   {
		 for(int k=0;k<SubcarrierNum;k++)
		  {
			Matrix_inequality[inequality_number][fore_num_6 + j*SubcarrierNum + k ] = 1;
			Matrix_inequality[inequality_number][fore_num_6 * 2 + j] = 1;
			Matrix_inequality[inequality_number][fore_num_6 * 2 + Mode_Num_Real + i*SubcarrierNum + k] = 1;			
			Matrix_inequality_value[inequality_number] = 2;
			inequality_number++;
	 	  }
	   }
	  temp6 = temp6+User_Mode_Num[i];	
    }
   //cout<<inequality_number<<endl;

   //不等式8(在不考虑缓存时，不等式8需要隐藏)
   int fore_num7 = Mode_Num_Real * SubcarrierNum * 2 + Mode_Num_Real + MaxUserNum * SubcarrierNum;   
   for(int i=0;i<MaxRelayNum;i++)
   {
	   for(int j=0;j<MaxFileNum;j++)
	   {
		   Matrix_inequality[inequality_number][fore_num7 + i*MaxFileNum + j] = 1;
		   Matrix_inequality_value[inequality_number] = 1-Cache_data[i][j];
		   inequality_number++;
	   }	   
   }*/
   

//	cout<<"不等式的数目为："<<inequality_number<<endl;
	return inequality_number;
}

//输出不等式矩阵
void Print_Matrix_inequality(int (&Matrix_inequality_value)[inequality_num],int inequality_number,int variable_number, int(& Matrix_inequality)[inequality_num][variable_num])
{
	ofstream file;
	file.open("不等式矩阵.txt");
	for(int i=0;i<inequality_number;i++)
	{
		for(int j=0;j<variable_number;j++)
		{
			//cout<<Matrix_inequality[i][j]<<" ";
			file<<Matrix_inequality[i][j]<<" ";
		}
		//cout<<endl;
		file<<endl;

	}
	file.close();
	file.open("不等式矩阵值.txt");
	for(int i=0;i<inequality_number;i++)
	{
		file<<Matrix_inequality_value[i]<<endl;	
	}
	file.close();
	cout<<"不等式行列数： "<<inequality_number<<" "<<variable_number<<endl;
}




