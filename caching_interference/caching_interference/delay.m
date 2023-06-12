

function delay
try
    u_num=100;   %用户数
    r_num=5;     %基站数
    f_num=200;    %总文件数
    rba_num = 50;  %接入RB的数目
    rbb_num = 25;   %回程RB的数目
    ra=zeros(1,u_num);   %接入资源的分配数组，只记录每个用户能够分得多少个RB
    rb=zeros(1,u_num);    %回程资源的分配数组，只记录每个用户能够分得多少个RB
    access_table=zeros(u_num, r_num);   %定义用户的接入矩阵，是用传输模式选择变量的结果和传输模式矩阵计算出来的
    rate_array=zeros(1,u_num);     %定义用户的接入频谱效率数组
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
   % disp(access_table);
   % disp(rate_array);
    
     vec_rate=zeros(1,u_num ) ;     %记录接入到基站i的用户的速率
 	 vec_id=zeros(1,u_num );          %记录接入到基站i的用户的id
    
     %接入资源的分配
	 for i=1 : r_num %#ok<ALIGN>
	    k=1;
        for j=1 : u_num
            if access_table(j,i)==1 && ra(1,j)==0        %如果用户j接入到基站i，且目前还没有分配到资源，在基站i在分配资源时要考虑到用户j
                vec_rate(1,k)=rate_array(1,j);                %将用户j接入基站i时，其传输模式下的速率记录到vec_rate中
                vec_id(1,k)=j;                                  %将用户j的id记录到vec_id中
                k=k+1;
            end
        end
        %disp(vec_rate);
        %disp(k-1);
        vec_rate=vec_rate(1, 1:k-1);       %实际接入到基站i的用户数为k-1个，因此截取vec_rate和vec_id的前k-1项
        vec_id = vec_id(1, 1:k-1);
        %disp(vec_id);
		[~, temp]=sort(vec_rate,'descend');    %对vec_rate递减排序，temp记录了排序后的元素在vec_rate中的下标
		div = length(vec_id);
        id_sort=zeros(1,div);       %记录速率排序后对应的用户id
		for n=1 : div
		    id_sort(1,n)=vec_id(temp(1,n));   
        end	
		x1=fix(rba_num/div);   %商    ，按照速率有限的原则，给前x2个用户分配较多的RB
        x2=rem(rba_num,div);     %余
  
       % disp(id_sort);
        for m=1 : x2
             ra(id_sort(1,m)) = x1+1;
        end
        %disp(ra);
		for m=x2+1 : div
		     ra(id_sort(1,m)) = x1;
		end
     end
     %disp('接入资源的分配：');
     %disp(ra);
     
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
     %disp(a_result);
     
     %回程资源的分配
     bac_delay=zeros(1,u_num);      %记录每个用户的回程时延
     for i=1:r_num
         k=1;
         vec_q=zeros(1,u_num);
         for j=1:u_num
             if access_table(j,i)==1
                 f=find(Req(j,:));
                 if L(i,f)==0
                     vec_q(k)=j;
                     k=k+1;
                 else
                     rb(1,j) = -1;
                 end
             end
         end
         vec_q = vec_q(1,1:k-1);
         %disp(vec_q);         
         div = length(vec_q);
         x1 = fix(rbb_num/div);
         x2 = rem(rbb_num, div);
         for m=1 : x2
             rb(vec_q(m)) = x1+1;
         end
         for m=x2+1 : div
             rb(vec_q(m)) = x1;
         end
     end
     
     %disp('回程资源的分配：')
     %disp(rb);
     %计算回程时延
     for i=1 : u_num
         if rb(1,i)~= -1 && rb(1,i)~=0
             bac_delay(1,i) = 1/rb(1,i);
         end
     end
     
     %disp('每个用户的回程时延：')
     %disp(bac_delay);
     
     b_result = sum(bac_delay);
     %disp('回程时延');
    % disp(b_result);   
    
    %计算总时延
     total_deday = a_result + b_result;
     disp('总时延：');
     disp(total_deday);
     %将总时延写入到文档中
     fid = fopen('时延.txt', 'a');
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
    fid = fopen('1-我的方案吞吐量.txt','a');
    %fid = fopen('1-单接入吞吐量.txt','a');
    fprintf(fid, '%d\t', total_through);
    fclose(fid);
    
    %每个基站接入的用户数
    %for i=1 : r_num
    %    disp(sum(access_table(:,i)));
    %end
catch m
   disp(m.message);
end
end