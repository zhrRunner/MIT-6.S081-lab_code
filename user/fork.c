// fork.c : create a new process

#include "kernel/types.h"
#include "user/user.h"

int main() {
    int pid = fork(); // 创建一个新的进程
    printf("fork() returned %d\n", pid);

    if(pid == 0) { // 子进程
        printf("child\n");
    } else { // 父进程
        printf("parent\n");
    }
    exit(0);
}