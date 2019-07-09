#include<time.h>
#include<stdio.h>
#define TOTAL_INODE 100
#define INODE_TO_BLOCK 4
#define FILE_BLOCK_MAX_LENGTH 8

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

void readinode() {//取
	FILE *file;
	file = fopen("D:\\inode.txt", "rb");
	for (int i = 0; i < TOTAL_INODE; i++)
	fread(&inode[i], sizeof(struct inode), 1, file);
	fclose(file);
}
void initInode() {//初始化
	FILE *file;
	file = fopen("D:\\inode.txt", "w");
	for (int i = 0; i < TOTAL_INODE; i++)
	{
		struct inode init;
		if (i == 0){init.file_type = 2;init.lastInode=0;strcpy(init.name,"user");}
		else {init.file_type=0;strcpy(init.name,"\0");}
		fwrite(&init, sizeof(struct inode), 1, file);		
	}
	fclose(file);
}
void saveInode() {//存
	FILE *file;
	file = fopen("D:\\inode.txt", "w");
	for (int i = 0; i < TOTAL_INODE; i++)
	{
		fwrite(&inode[i], sizeof(struct inode), 1, file);	
	}
	fclose(file);
}


