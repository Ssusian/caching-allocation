#include "st.h"

void ST_throughput(double *Rate, int *User_Mode_Num, double * ST_rate)
{
	double throughput = 0.0;  //记录总的吞吐量
	double mmax = 0.0;   //记录每个用户的最大接入速率
    int temp = 0;     //记录传输模式遍历的下标
    int i=0;           //记录用户id
	int j=0;
	//找出每个用户最大接入速率，并记录在ST_rate中
    while(i<MaxUserNum)
    {
	  //用户i只有一种接入方式
	  if(User_Mode_Num[i] == 1)
        {
		   ST_rate[i] = Rate[temp];
		   throughput += Rate[temp];
		   temp += 1;
           ++i;
        }
		//用户i有多种接入方式
      else
       {
	       mmax = Rate[temp];
		   for(j=temp; j<(temp+User_Mode_Num[i]); ++j)
		   {
		       if(mmax < Rate[j])
			       mmax=Rate[j];
		   }
		   ST_rate[i] = mmax;
		   throughput += mmax;
		   temp += User_Mode_Num[i];
		   ++i;
	   }	  
	}
	//将总的吞吐量写入到文档中
	ofstream outfile;
	outfile.open("ST_throughput.txt", ios::app);
	outfile<<throughput<<"\t";
	cout<<"单接入下的吞吐量为："<<throughput<<endl;
}

void Print_ST(double * ST_rate)
{
	cout<<"每个用户的接入速率为："<<endl;
    for(int i=0; i<MaxUserNum; ++i)
	{
	   cout<<"user "<<i<<": "<<ST_rate[i]<<endl;
	}
}	
	