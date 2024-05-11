// open.c : create a file, write to it
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h" // 包含文件操作的常量

int main() {
    int fd = open("output.txt", O_WRONLY | O_CREATE);  // 0_RDONLY表示只读，O_WRONLY表示只写，O_RDWR表示读写，O_CREATE表示创建文件
    
    write(fd, "hello world\n", 12);
    close(fd); // 写完后应该关闭文件

    exit(0);
}

