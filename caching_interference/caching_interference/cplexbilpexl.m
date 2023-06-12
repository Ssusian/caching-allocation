
try
    
   % Since cplexbilp solves minimization problems and the problem
   % is a maximization problem, negate the objective
 
  [a]=load('目标函数.txt');
   f     = a;
   [b]=load('不等式矩阵.txt');
   Aineq = b;
   [c]=load('不等式矩阵值.txt');
   bineq = c;
   [d]=load('等式矩阵.txt');
   Aeq   = d;
   [e]=load('等式矩阵值.txt');
   beq   =  e;
   %检验各个矩阵的行数和列数是否一致
   [m,n]=size(f);
   [a,b]=size(Aineq);
   [x,y]=size(bineq); 
   [p,q]=size(Aeq);
   [z,w]=size(beq);
    fprintf('ranks = %d\n',m,n,a,b,x,y,p,q,z,w);
   % fprintf('ranks = %d\n',m,n,a,b,x,y);
   options = cplexoptimset;
   options.Diagnostics = 'on';   
   %Aeq,beq,
   [x, fval, ~, output] = cplexbilp (f, Aineq, bineq,Aeq,beq, ...
      [ ], options);
  
   %将变量的结果输出到文件中
   fid = fopen('仿真结果.txt','w');
   fprintf(fid,'%f\t',x);
   fclose(fid);
   
   %将目标函数的结果输出到文件中
   fid = fopen('backhaul_result.txt', 'a');
   fprintf(fid, '%d\t', fval);
   fclose(fid);
   
   %计算总的频谱效率
  % mode_num=load('传输模式个数.txt');
  % R1 = load('速率.txt');
  % A = load('仿真结果.txt');
  % B = A(1:1:mode_num); 
  % C=B';
  % throughput=R1*C;
   
   %将频谱效率写入到文档中
  % fid = fopen('throughput.txt', 'a');
  % fprintf(fid, '%f\t', throughput);
  % fclose(fid);     
  
  %显示变量结果
   fprintf ('\nSolution status = %s\n', output.cplexstatusstring);   
   disp (x);
   %显示目标函数值
  % disp ('Values = ');
   fprintf ('Solution value = %d\n', fval); 
   %频谱效率总和 
  % fprintf ('Throughput = %f\n', throughput); 
  %变量值之和，主要是为了判断基站是否缓存满
   h = sum(x);
   disp('Sum = ');
   disp(h);
  
catch m
   disp(m.message);
end



