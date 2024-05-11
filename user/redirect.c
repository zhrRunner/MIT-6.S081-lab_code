#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h" // 包含文件操作的常量

// redirect.c :run a command with output redirected

int main() {
    int pid;
    
    pid = fork();
    if(pid == 0){
        close(1); // 关闭标准输出
        // 由于标准输出（文件描述符1）已被关闭，新打开的文件将占用文件描述符1，这实现了输出重定向
        open("output.txt", O_WRONLY | O_CREATE); // 打开文件output.txt，文件描述符为1

        char *argv[] = {"echo", "this", "is", "echo", "redirected", 0};
        exec("echo", argv); // 执行echo命令
        printf("exec failed\n");
        exit(1);
    } else {
        wait((int *)0); // 等待子进程结束 wait返回子进程的状态
    }

    exit(0);
}