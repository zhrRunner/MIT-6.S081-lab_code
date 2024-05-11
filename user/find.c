// find.c : find files with a specific name

// find.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

// 递归查找文件名为 `target` 的文件
void find(char *path, char *target) {
	char buf[512], *p;
	int fd;
	struct dirent de;  // 目录项 
	struct stat st;   // 文件状态

	if((fd = open(path, 0)) < 0){
		fprintf(2, "find: cannot open %s\n", path);
		return;
	}

	// 获取文件状态，如果失败则报错
	if(fstat(fd, &st) < 0){
		fprintf(2, "find: cannot stat %s\n", path);  
		close(fd);
		return;
	}

	switch(st.type){
	case T_FILE:  // 如果path是文件
		// 如果文件名结尾匹配 `/target`，则视为匹配
		if(strcmp(path+strlen(path)-strlen(target), target) == 0) {
			printf("%s\n", path);
		}
		break;
	case T_DIR:  // 如果path是目录
	
		if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){  // DIRSIZ是文件名的最大长度
			printf("find: path too long\n");
			break;
		}
		strcpy(buf, path);
		p = buf+strlen(buf);  // 将指针p指向buf末尾的 `\0`
		*p++ = '/';  // 先执行 *p = '/'，再执行 p++
		while(read(fd, &de, sizeof(de)) == sizeof(de)){  // 读取目录项
			if(de.inum == 0)  // 如果目录项的inode号为0，说明该目录项为空
				continue;
			memmove(p, de.name, DIRSIZ);  // 将目录项的文件名拷贝到buf的末尾
			p[DIRSIZ] = 0;  // 文件名后面加上 `\0`
			if(stat(buf, &st) < 0){
				printf("find: cannot stat %s\n", buf);
				continue;
			}
			// 不要进入 `.` 和 `..`
			if(strcmp(buf+strlen(buf)-2, "/.") != 0 && strcmp(buf+strlen(buf)-3, "/..") != 0) {
				find(buf, target); // 递归查找
			}
		}
		break;
	}
	close(fd);
}

int main(int argc, char *argv[])
{
	// *argv[] = {"find", ".", "b"} 
	if(argc < 3){
		exit(0);
	}
	char target[512];
	target[0] = '/'; // 为查找的文件名添加 / 在开头
	strcpy(target+1, argv[2]);  // target = "/b"
	find(argv[1], target);
	exit(0);
}