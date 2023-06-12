function XHL
    try
        [d1]=load('仿真结果.txt');
        S1 = d1;
        [d2]=load('速率.txt');
        S2 = d2;   
        S3 = S2.';
        disp(size(S1));
        disp(size(S3));
        data=S1*S3;
        
        sum_n = sum(data);  
        disp(sum_n);
        
    catch m
    disp(m.message);
    end
end