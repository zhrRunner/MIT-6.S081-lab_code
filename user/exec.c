// exec.c: replace a process with an executable file

#include "kernel/types.h"
#include "user/user.h"

int main()
{
    // argv中的第一个参数是程序名，可以任意，起作用的是exec的第一个参数，它是一个指针数组，
    // 0是一个空指针，用常量NULL表示，将无法确定参数列表何时结束，如果没有0，可能导致程序尝试访问数
    // 组边界之外的内存，从而引发未定义行为，包括程序崩溃或不正确的行为
    char *argv[] = {"echo", "this", "is", "echo", "command", 0}; // argv[0]是程序名，可以任意

    exec("echo", argv); // 将当前进程替换为 echo 命令

    printf("exec failed\n");

    exit(0);
}