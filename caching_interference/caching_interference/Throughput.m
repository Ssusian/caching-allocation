function Throughput


    try
        %user_num = 5;
       % sub_num = 25;
       % mode_num=load('传输模式个数.txt');
       % numb = sub_num*mode_num; 
       % R1 = load('速率.txt');
       % R2 = R1';
       % A = load('仿真结果.txt');
       % B = A(1:1:numb);                       
       % C = reshape(B,sub_num,mode_num);        %信道使用情况
       % E = sum(C);                           %E计算出了每个用户分配有多少个信道
       % output = E*R2;          
        
       mode_num=load('传输模式个数.txt');
       R1 = load('速率.txt');
       A = load('仿真结果.txt');
       B = A(1:1:mode_num); 
       C=B';
       throughput=R1*C;
        %disp(numb);
        %disp(B);
        %disp(C);
        
       %disp(E);
      % disp(R2);
       %disp(user_num);   
        
        disp(throughput);              
 
        
    catch m
    disp(m.message);
    end
end