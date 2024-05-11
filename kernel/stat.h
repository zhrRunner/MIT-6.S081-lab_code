#define T_DIR     1   // Directory
#define T_FILE    2   // File
#define T_DEVICE  3   // Device

struct stat {
  int dev;     // File system's disk device
  uint ino;    // Inode number
  short type;  // Type of file  文件类型看是目录还是文件 T_DIR or T_FILE
  short nlink; // Number of links to file
  uint64 size; // Size of file in bytes
};
