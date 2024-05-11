// forkexec.c : fork then exec

#include "kernel/types.h"
#include "user/user.h"

int main()
{
    int pid, status;

    pid = fork();
    if (pid == 0)
    {
        char *argv[] = {"echo", "this", "is", "echo", "command", 0};
        // 如果这里改成exec("echoadf", argv);，则会打印：
        // parent waiting
        // exec failed
        // parent: child exited with status 1
        exec("echo", argv);
        printf("exec failed\n");
        exit(1);
    }
    else
    {
        printf("parent waiting\n");
        wait(&status);
        printf("parent: child exited with status %d\n", status);
        }
    exit(0);
}