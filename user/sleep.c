// sleep.c : sleep for a few seconds

#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) { // argc表示参数个数，argv表示参数列表
    if(argc < 2) {   // 参数个数小于2
        fprintf(2, "the argc of must at least 1\n"); // 输出错误信息
        exit(1);  // 错误退出
    }
    int num = atoi(argv[1]);  // 获取第二个参数并转为整数
    printf("(nothing happens for a little while)\n");
    sleep(num);  // 睡眠num个时间片
    exit(0);
}