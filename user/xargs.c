# include<kernel/types.h>
# include<user/user.h>
# include<kernel/param.h>

char *my_gets(char *buf, int max){
    int i, n;  // i是索引下标，n是read函数返回值
    char ch;
    for(i = 0; i < max - 1;){
        n = read(0, &ch, 1); 
        if(n < 1)  break;
        if(ch == '\n' || ch == '\r') break;
        buf[i ++] = ch;
    }
    buf[i] = '\0';

    return buf;
}

int my_getcmd(char *buf, int nbuf){
    memset(buf, 0, nbuf); // 将buf清零
    my_gets(buf, nbuf);
    if(buf[0] == 0) {
        return -1;
    }
    return 0;
}

int main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(2, "xargs命令后缺少参数\n");
        exit(1);
    }
    char *_argv[MAXARG];
    int _argc = argc - 1;
    memcpy(_argv, argv + 1, _argc * sizeof(char *));

    char buf[512]; // 读取用户输入
    while(my_getcmd(buf, sizeof(buf)) != -1){
        if(fork() == 0){
            _argv[_argc] = buf;
            _argc ++;
            exec(_argv[0], _argv);
            fprintf(2, "exec %s failed!\n", _argv[0]);
            exit(0);
        } else {
            wait(0);
            // exit(0); // 这里不能添加exit(0)，否则会导致子进程无法执行
        }
    }
    exit(0);
}
