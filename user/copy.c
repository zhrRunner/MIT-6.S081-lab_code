// copy.c: 将控制台输入内容输出到控制台

#include "kernel/types.h"  // 包含系统调用的封装
#include "user/user.h"   // 包含用户态库函数

int
main()
{
  char buf[64];

  while(1){
    //从console读取输入，通过system call的read函数实现
    int n = read(0, buf, sizeof(buf)); // 0表示标准输入，返回读取的字节数
	  //无输入结束程序
    if(n <= 0)  break;  
    //将console输入输出到控制台，通过system call的write函数实现
    write(1, buf, n); // 1表示标准输出，n表示输出的字节数
  }

  exit(0);
}

