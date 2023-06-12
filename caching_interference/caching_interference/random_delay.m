

function random_delay
try
    u_num=50;   %用户数
    r_num=5;     %基站数
    f_num=200;    %总文件数
    rba_num = 50;  %接入RB的数目
    rbb_num = 25;   %回程RB的数目
    ra=zeros(1,u_num);   %接入资源的分配数组，只记录每个用户能够分得多少个RB
    rb=zeros(1,u_num);    %回程资源的分配数组，只记录每个用户能够分得多少个RB
    access_table=zeros(u_num, r_num);   %定义用户的接入矩阵，是用传输模式选择变量的结果和传输模式矩阵计算出来的
    rate_array=zeros(1,u_num);     %定义用户的频谱速率数组
    through_array=zeros(1,u_num);     %定义用户的接入速率数组，Mbit/s
         
    a=load('传输模式个数.txt');
    %disp(a);
    T=load('仿真结果.txt');
    y=T(1:a);      %将仿真结果中的传输模式变量的值放在数组y中
    %disp(length(y));
    l=T(a+1:length(T));   %将仿真结果中的缓存变量的值放在数组l中
    %disp(length(l));
    L=reshape(l, [r_num,f_num]);   %基站缓存结果
    A=load('传输模式矩阵.txt');
    R=load('速率.txt');
    Req=load('用户请求.txt');        %用户请求信息
    
    %得到用户的接入矩阵和接入速率。
    j=1;
    for i=1:length(y)
        if y(i)==1            %当用户的传输模式选择变量取1时，将对应行的接入添加到access_table中，对应行的速率添加到rate_array中
            access_table(j,:) = A(i,:);
             rate_array(1,j)=R(1,i);
            j=j+1;
        end            
    end
    %disp(access_table);
   % disp(rate_array);
    
 	 vec_id=zeros(1,u_num );          %记录接入到基站i的用户的id
    
     %接入资源的分配
	 for i=1 : r_num %#ok<ALIGN>
	    k=1;
        for j=1 : u_num
            if access_table(j,i)==1 && ra(1,j)==0        %如果用户j接入到基站i，且目前还没有分配到资源，在基站i在分配资源时要考虑到用户j
              vec_id(1,k)=j;                                  %将用户j的id记录到vec_id中
                k=k+1;
            end
        end
        vec_id =  vec_id(1, 1:k-1);
		div = length(vec_id);
		x1 = rba_num/div;   
		x2=floor(x1);    		
        for m=1 : div           
            ra(vec_id(m)) = x2;
        end
     end
    % disp('接入资源的分配：');
    % disp(ra);     
     %disp(rate_array);
     
     %计算接入时延
     access_delay=zeros(1,u_num);
     for i=1 : u_num
         access_delay(1,i) = 1024*1024/(1800*ra(1,i)*rate_array(1,i));
     end
     a_result=sum(access_delay);
     %disp('每个用户的接入时延：');
     %disp(access_delay);
     %disp('接入时延');
    % disp(a_result);
     
     %回程资源的分配
     bac_delay=zeros(1,u_num);      %记录每个用户的回程时延
     for i=1:r_num
         x1=sum(access_table(:,i));
         x2=rbb_num/x1;
         x3=round(x2);
         for j=1: u_num
             if rb(1,j)==0 && access_table(j,i)==1
                 rb(1,j)=x3;
             end
         end
     end     
     %disp('回程资源的分配：')
     %disp(rb);
     
     %计算回程时延
     for i=1 : u_num
             bac_delay(1,i) = 1/rb(1,i);
     end     
     %disp('每个用户的回程时延：')
     %disp(bac_delay);     
     b_result = sum(bac_delay);
     % disp('回程时延');
     % disp(b_result);   
    
    %计算总时延
     total_deday = a_result + b_result;
     disp('总时延：');
     disp(total_deday);
     %将总时延写入到文档中
     fid = fopen('random_时延.txt', 'a');
     fprintf(fid, '%d\t', total_deday);
     fclose(fid);
     
       %计算吞吐量
     for i=1 : u_num
         through_array(1,i)=rate_array(1,i)*ra(1,i)*0.18;
     end
     total_through=sum(through_array);
     %disp('总吞吐量：');
     %disp(total_through);
     %将吞吐量写入到文档中
     fid = fopen('3-随机分配吞吐量.txt','a');
     fprintf(fid, '%d\t', total_through);
     fclose(fid);
    
catch m
   disp(m.message);
end
end