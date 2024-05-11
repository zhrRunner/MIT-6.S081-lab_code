# include<kernel/types.h>
# include<user/user.h>

int main() {
    char *argv[] = {"echo", "My", "name", "is", "zhr", 0};
    exec("echo", argv);
    printf("exec failed\n");  // 如果exec失败，就会执行这一行，成功的话就不会执行，因为exec会替换当前进程的代码和数据
    exit(0);
}