#include<time.h>
#define TOTAL_INODE 100
#define INODE_TO_BLOCK 4
#define FILE_BLOCK_MAX_LENGTH 8
#define INODEPATH "inode"

#define WRITE_ONLY 1
#define READ_ONLY 2
#define WRITE_AND_READ 3

struct inode
{   char name[10];
	unsigned short file_type;//fle type 0为未使用 1为文件 2为目录
	unsigned short protection;//0 write 1 read  2write&read
	int user_id;   //�ļ������û���id
	unsigned short file_size;
	int blockid;
	int lastInode;//��һ�ڵ�λ��
	time_t access_time;//last visit time
	time_t modification_time;//last change time
	time_t create_time;
} inode[TOTAL_INODE];

void readinode(char* userPath);

void initInode(char* userPath);

void saveInode(char* userPath);

char* inodePath(char* userPath);


