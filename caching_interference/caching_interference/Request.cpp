#include "Request.h"
#include <math.h>

//文件受欢迎度
void Pro_Generator(double *p)
{
	double deno = 0.0;   //分母
	double nume = 0.0;   //分子
	double temp = 0.0;
	//计算分母
	for(int i=1;i<=MaxFileNum;i++)
	{
		temp = double(1.0/pow(i,γ));
		deno+=temp;
	}
	//cout<<"deno: "<<deno<<endl;
	for(int j=1;j<=MaxFileNum;j++)
	{
		//计算分子
		nume = double(1.0/pow(j,γ));
		//计算概率
		p[j-1]=double(nume/deno);
	}
}
void Print_Pro( double *p)
{
	cout<<"文件受欢迎度为："<<endl;
	for(int i=0;i<MaxFileNum;i++)
	{
		cout<<p[i]<<" ";
	}
	cout<<endl;
}

//用两个随机数来产生较大的随机数，目前是可行的
void Request_Generator(int (& User_Request)[MaxUserNum][MaxFileNum], double *File_Pro)
{
  	int max = File_Pro[0]*pow(10.0, 7);
	srand((unsigned)time(0)) ;
	for(int i=0;i<MaxUserNum;i++)
    {
	    
        int rand1 = rand() %10000;
        int rand2 = rand() % 10000;
        int randV = (rand1 * 10000 + rand2) % (max + 1);//改成这样   
        int x = randV;
		
		if(x <= File_Pro[MaxFileNum-1]*pow(10.0,7) )        //判断第0个文件
		{
			User_Request[i][MaxFileNum-1]=1;
		}
		else                     //判断剩余文件
		{
			int j=0;
			while(j<(MaxFileNum-1))
			{
				if((x > File_Pro[j+1]*pow(10.0,7)) && (x <= File_Pro[j]*pow(10.0,7)))
				{
					User_Request[i][j]=1;
					break;
				}
				else
				{
					j++;
				}
			}
			//if(MaxFileNum-1 == j)
			//	User_Request[i][j]=1;
		}

	}
}

//用户请求随机产生
void Request_Generator(int (& User_Request)[MaxUserNum][MaxFileNum])
{
	srand((unsigned)time(0)) ;
	for(int i=0;i<MaxUserNum;i++)
	{
        int temp = rand()%MaxFileNum;
		User_Request[i][temp]=1;		
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
}

//将用户的文件请求信息输出到本地
void Out_Request(int (& User_Request)[MaxUserNum][MaxFileNum])
{
	ofstream file;
	file.open("用户请求.txt");
	for(int i=0;i<MaxUserNum;i++)
	{
		for(int j=0;j<MaxFileNum;j++)
		{
			file<<User_Request[i][j]<<" ";
		}
		file<<endl;
	}
	file.close();
}