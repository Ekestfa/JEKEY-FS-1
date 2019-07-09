#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"block.h"
#include"../usr/user.h"

char* blockPath(char* userPath){
    int userpathLen = strlen(userPath);
    int blocksubLen = strlen(BLOCKPATH);
    char* blockPath = malloc(userpathLen+blocksubLen);
    blockPath = strcpy(blockPath,userPath);
    blockPath = strcat(blockPath,BLOCKPATH);
    return blockPath;
}
void cleanblock(char* userPath){
    FILE*fp;
    struct block c;

    // Get /opt/user/$user_name/
    char* path = blockPath(userPath);
    c.isused=0;
    c.Length=0;
    c.data[0]='\0';
        if((fp=fopen(path,"w+"))==NULL)
            printf("block cant open");
         else{for (int i=0;i<10;i++)fwrite(&c,sizeof(struct block),1,fp);
             fclose(fp);
         }
}
void writeblock(struct block Block[],char* userPath){
    FILE*fp;
    char* path = blockPath(userPath);
    if((fp=fopen(path,"w+"))==NULL)
        printf("block cant open");
    else{for (int i=0;i<1;i++)fwrite(&Block[i],sizeof(struct block),1,fp);
        fclose(fp);
    }
}
bool readblock(struct block re[10],char* userPath){
    FILE*fp;
    char* path = blockPath(userPath);
	if((fp=fopen(path,"rb+"))==NULL){
        printf("block cant open\n");
        return false;
        }
    else{for (int i=0;i<1;i++)fread(&re[i],sizeof(struct block),1,fp);
        fclose(fp);
		return true;
    }     
}
