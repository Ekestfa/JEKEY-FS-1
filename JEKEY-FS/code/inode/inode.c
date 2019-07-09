#include<time.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"inode.h"

char* inodePath(char* userPath){ 
    int userpathLen = strlen(userPath);
    int inodesubLen = strlen(INODEPATH);
    char* iPath = malloc(userpathLen+inodesubLen);
    iPath = strcpy(iPath,userPath);
    iPath = strcat(iPath,INODEPATH);
    return iPath;
}
void readinode(char *userPath) {//取
	char* path = inodePath(userPath);
	FILE *file;
	file = fopen(path, "rb");
	for (int i = 0; i < TOTAL_INODE; i++)
	fread(&inode[i], sizeof(struct inode), 1, file);
	fclose(file);
}
void initInode(char* userPath) {//初始化
	FILE *file;
	char* path = inodePath(userPath);
	file = fopen(path, "w");
	for (int i = 0; i < TOTAL_INODE; i++)
	{
		struct inode init;
		if (i == 0){init.file_type = 2;init.lastInode=0;strcpy(init.name,"user");}
		else {init.file_type=0;strcpy(init.name,"\0");}
		fwrite(&init, sizeof(struct inode), 1, file);		
	}
	fclose(file);
}
void saveInode(char* userPath) {//存
	FILE *file;
	char* path = inodePath(userPath);
	file = fopen(path, "w");
	for (int i = 0; i < TOTAL_INODE; i++)
	{
		fwrite(&inode[i], sizeof(struct inode), 1, file);	
	}
	fclose(file);
}


