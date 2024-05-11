// primes.c : print prime numbers

#include "kernel/types.h"
#include "user/user.h"

void dfs(int nums[], int cnt)
{
    if (cnt == 1){
        printf("prime %d\n", *nums);
        return ;
    }
        
    int p[2];
    pipe(p);

    int x = *nums; // 第一个数，也是素数
    printf("prime %d\n", x);

    // 第一个子进程：用于将nums数组中的数写入管道
    if (fork() == 0)
    {
        for (int i = 0; i < cnt; i++)
        {
            write(p[1], (char *)(nums + i), 4);
        }
        exit(0);
    }

    // 关闭父进程中的写端（提示，如果不关闭，后续的read会认为
    // 管道中一直有数据可以写，会进入阻塞
    close(p[1]); 

    // 第二个子进程：用于将管道中的数读取，并做筛选
    if (fork() == 0)
    {
        char buf[4];
        // 更改cnt的值
        cnt = 0;
        while (read(p[0], (int *)buf, 4))
        {
            if (*buf % x)
            { // 不是第一个数的倍数，存入nums
                *nums = *buf;
                nums++;
                cnt++;
            }
        }
        dfs(nums - cnt, cnt);
        exit(0);
    }
    wait(0);
}

int main()
{
    int nums[34];
    for (int i = 0; i < 34; i++)
        nums[i] = i + 2;
    dfs(nums, 34);

    exit(0);
}