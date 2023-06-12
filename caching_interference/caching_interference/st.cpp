#include "st.h"

void ST_throughput(double *Rate, int *User_Mode_Num, double * ST_rate)
{
	double throughput = 0.0;  //��¼�ܵ�������
	double mmax = 0.0;   //��¼ÿ���û�������������
    int temp = 0;     //��¼����ģʽ�������±�
    int i=0;           //��¼�û�id
	int j=0;
	//�ҳ�ÿ���û����������ʣ�����¼��ST_rate��
    while(i<MaxUserNum)
    {
	  //�û�iֻ��һ�ֽ��뷽ʽ
	  if(User_Mode_Num[i] == 1)
        {
		   ST_rate[i] = Rate[temp];
		   throughput += Rate[temp];
		   temp += 1;
           ++i;
        }
		//�û�i�ж��ֽ��뷽ʽ
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
	//���ܵ�������д�뵽�ĵ���
	ofstream outfile;
	outfile.open("ST_throughput.txt", ios::app);
	outfile<<throughput<<"\t";
	cout<<"�������µ�������Ϊ��"<<throughput<<endl;
}

void Print_ST(double * ST_rate)
{
	cout<<"ÿ���û��Ľ�������Ϊ��"<<endl;
    for(int i=0; i<MaxUserNum; ++i)
	{
	   cout<<"user "<<i<<": "<<ST_rate[i]<<endl;
	}
}	
	