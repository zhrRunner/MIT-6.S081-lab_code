#include <kernel/types.h>
#include <user/user.h>

int main()
{
    // p1：父进程写，子进程读
    // p2：父进程读，子进程写
    int p1[2], p2[2]; 
    pipe(p1);
    pipe(p2);
    char buf[] = {"!"};  // 这里!只是一个标志，可以是任意字符
    if (fork() == 0){  // 子进程
        close(p1[1]);
        close(p2[0]);
        if(read(p1[0], buf, 1) < 0) {
            fprintf(2, "childread is error\n");
        }
        printf("%d: received ping\n", getpid());
        if(write(p2[1], buf, 1) < 0) {
            fprintf(2, "childwrite is error\n");
        }
        exit(0);
    } else {  // 父进程
        close(p1[0]);
        close(p2[1]);
        if(write(p1[1], buf, 1) < 0){
            fprintf(2, "parentwrite is error\n");
        }
        wait((int *)0);
        if(read(p2[0], buf, 1) < 0){
            fprintf(2, "parentread is error\n");
        }
        printf("%d: received pong\n", getpid());

    }

    exit(0);
}