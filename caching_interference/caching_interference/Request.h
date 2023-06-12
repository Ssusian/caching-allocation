
#include "Function.h"

//文件的受欢迎度
void Pro_Generator(double *p);
void Print_Pro(double *p);

//用户请求按文件受欢迎度产生
void Request_Generator(int (& User_Request)[MaxUserNum][MaxFileNum],double *File_Pro);

//用户请求随机产生
void Request_Generator(int (& User_Request)[MaxUserNum][MaxFileNum]);

void Print_Request(int *User_Request);

//将用户的文件请求输出到本地文档
void Out_Request(int (& User_Request)[MaxUserNum][MaxFileNum]);