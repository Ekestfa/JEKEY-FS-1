#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#include"dirent.h"
#include"../inode/inode.h"
#include"../block/block.h"
#include"../usr/user.h"

short nowin = 0;//��ǰĿ¼
char nowins[10]="user";
short openinode[]={0,0,0,0,0};

void create(char* uPath){
    struct block re[10];
	if (readblock(re,uPath)){
		int i = 0, n = 1;
		for (; i < 10; i++) {
			if (re[i].isused == 0)break;
		}
		if (i < 10){
			readinode(uPath);
			for (; n < TOTAL_INODE; n++) if (inode[n].file_type == 0) break;
		if (n == TOTAL_INODE)printf("no enough inode");
		else {
			printf("input your file name:");
			char name[10];
			scanf("%s", name);
			printf("input 0:read 1:write 2:read&write\n");
			int r;
			scanf("%d", &r);
			inode[n].blockid = i;
			inode[n].file_size = 0;
			inode[n].file_type = 1;
			inode[n].protection = 2;
			inode[n].lastInode = nowin;
			strcpy(inode[n].name,name);
			saveInode(uPath);
		}
	}
    else printf("not enough storage space!\n");
   }    
}
void open(char* uPath){
	int j = 0, k = 0;
	int saveinodeid;
	char openadd[FILE_MAX_LENGTH];
	scanf("%s", openadd);
	char getfilename[FILE_MAXNUM][FILENAME_MAX_LENGTH];
	char checkfilename[FILE_MAXNUM][FILENAME_MAX_LENGTH];
	memset(checkfilename, '\0', sizeof(checkfilename));
	memset(getfilename, '\0', sizeof(getfilename));
	for (int i = 0; i < FILE_MAX_LENGTH; i++)//��ȡÿһ��Ŀ¼����
	{
		if (openadd[i] == '\0')
			break;
		if (openadd[i] == '/')
		{

			j = 0;
			k++;
		}
		else
		{
			getfilename[k][j] = openadd[i];
			j++;
		}
	}

	int openFile;
	readinode(uPath);
	for (int i = 0; i < TOTAL_INODE; i++)
	{
		openFile = -1;
		for (int i1 = 0; i1 < FILENAME_MAX_LENGTH; i1++)
		{
			if (inode[i].name[i1] != getfilename[k][i1])//��ͬ���ļ���������һ���ڵ��жϡ�
			{
				break;

			}
			if (i1 == FILENAME_MAX_LENGTH - 1 || getfilename[k][i1 + 1] == '\0')//����ͬ���ļ�����ȡͬ���ļ�·�����ж��Ƿ��봴��·����ͬ
			{
				saveinodeid = i;
				int lastinode;
				lastinode = inode[i].lastInode;
				for (int i2 = 1;; i2++)
				{
					if (k - i2 < 0)
					{
						printf("·����ͬ��������ͬ�ļ�");
						openFile = 4;//
						break;
					}
					for (int i3 = 0; i3 < FILENAME_MAX_LENGTH; i3++)
					{
						if (inode[lastinode].name[i3] != getfilename[k - i2][i3])
						{
							openFile = 1;
							break;

						}
						if (i3 == FILENAME_MAX_LENGTH - 1 || getfilename[k - i2][i3 + 1] == '\0')
						{
							lastinode = inode[lastinode].lastInode;
							break;
						}
					}
					if (openFile == 1)
						break;
					if (k - i2 == 0)
					{
						//printf("·����ͬ��������ͬ�ļ�");
						openFile = 4;//
						break;
					}
				}
			}
			if (openFile == 1 || openFile == 4)
				break;

		}
		if (openFile == 4)
			break;
	}
	if (openFile == -1)
		printf("�����ڸ��ļ�");
	if (openFile == 4)
	{   int x;
	for(x=0;x<5;x++){if(openinode[x]==0)openinode[x]=saveinodeid;break;}
	if(x==5)printf("��̫���ļ�");
	}

}
void close(char* uPath){
		//�ر��ļ�
	char closefile[FILE_MAX_LENGTH];
	scanf("%s", closefile);
	int closeFile;
	int saveinodeid;
	char getfilename[FILE_MAXNUM][FILENAME_MAX_LENGTH];
	char checkfilename[FILE_MAXNUM][FILENAME_MAX_LENGTH];
	memset(checkfilename, '\0', sizeof(checkfilename));
	memset(getfilename, '\0', sizeof(getfilename));
	int j = 0, k = 0;
	for (int i = 0; i < FILE_MAX_LENGTH; i++)//��ȡÿһ��Ŀ¼����
	{
		if (closefile[i] == '\0')
			break;
		if (closefile[i] == '/')
		{

			j = 0;
			k++;
		}
		else
		{
			getfilename[k][j] = closefile[i];
			j++;
		}
	}
	
	readinode(uPath);
	for (int i = 0; i < TOTAL_INODE; i++)
	{
		closeFile = -1;
		for (int i1 = 0; i1 < FILENAME_MAX_LENGTH; i1++)
		{
			if (inode[i].name[i1] != getfilename[k][i1])//��ͬ���ļ���������һ���ڵ��жϡ�
			{
				break;

			}
			if (i1 == FILENAME_MAX_LENGTH - 1 || getfilename[k][i1 + 1] == '\0')//����ͬ���ļ�����ȡͬ���ļ�·�����ж��Ƿ��봴��·����ͬ
			{
				saveinodeid = i;
				int lastinode;
				lastinode = inode[i].lastInode;
				for (int i2 = 1;; i2++)
				{
					if (k - i2 < 0)
					{
						printf("·����ͬ��������ͬ�ļ�");
						closeFile = 4;//
						break;
					}
					for (int i3 = 0; i3 < FILENAME_MAX_LENGTH; i3++)
					{
						if (inode[lastinode].name[i3] != getfilename[k - i2][i3])
						{
							closeFile = 1;
							break;

						}
						if (i3 == FILENAME_MAX_LENGTH - 1 || getfilename[k - i2][i3 + 1] == '\0')
						{
							lastinode = inode[lastinode].lastInode;
							break;
						}
					}
					if (closeFile == 1)
						break;
					if (k - i2 == 0)
					{
						//printf("·����ͬ��������ͬ�ļ�");
						closeFile = 4;//
						break;
					}
				}
			}
			if (closeFile == 1 || closeFile == 4)
				break;

		}
		if (closeFile == 4)
			break;
	}

	if (closeFile == 4)
	{
		int x;
	for(x=0;x<5;x++){if(openinode[x]==saveinodeid)openinode[x]=0;break;}
	if(x==5)printf("�ļ�δ��");
	}

}
void read(char* name,char* uPath){
	readinode(uPath);
	int i;
	for(i=0;i<TOTAL_INODE;i++){
	  if(inode[i].file_type==1&&inode[i].lastInode==nowin&&strcmp(name,inode[i].name)==0)
		  break;
	}
	if(i==TOTAL_INODE)printf("can't find such file!\n");
	else {
		int x;
		for(x=0;x<5;x++)if(openinode[x]==i)break;
		if(x==5)printf("file has not open!\n");
		else if(inode[i].protection==0)printf("this file cant be read");
		else{
		struct block re[10];
		readblock(re,uPath);
		printf("%s:%s",name,re[inode[i].blockid].data);
		}
	}
}
void write(char*name,char* uPath){
	readinode(uPath);
	int i;
	for(i=0;i<TOTAL_INODE;i++){
	  if(inode[i].file_type==1&&inode[i].lastInode==nowin&&strcmp(name,inode[i].name)==0)
		  break;
	}
	if(i==TOTAL_INODE)printf("can't find such file!\n");
	else {
		int x;
		for(x=0;x<5;x++)if(openinode[x]==i)break;
		if(x==5)printf("file has not open!\n");
		else if(inode[i].protection==1)printf("this file cant be write");
		else{
		struct block re[10];
		readblock(re,uPath);
		printf("please input date:");
		scanf("%s",re[inode[i].blockid].data);
		writeblock(re,uPath);
		}
	}
}
void chdir(char* di, char* uPath){
	char*token;
	short fir=nowin;
	int i=0;
	token = strtok(di,"/");
	while (token!= NULL) {
		if(strcmp(token,".")!=0){
			readinode(uPath);
			for(i=0;i<TOTAL_INODE;i++){
				if(inode[i].file_type==2&&inode[i].lastInode==fir&&strcmp(token,inode[i].name)==0){
				    fir=i;
					break;}
			}
			if(i==TOTAL_INODE){
            i=999;
			break;
			}
		}

		token = strtok(NULL, "/");
	}
	if(i==999)printf("no such dir\n");
	else if(i==0){nowin=inode[nowin].lastInode;strcpy(nowins,inode[nowin].name);}
	else {nowin=fir;strcpy(nowins,inode[nowin].name);}
}
void mkdir(char* uPath){
	char createfile[FILE_MAX_LENGTH];
	memset(createfile, '\0', sizeof(createfile));
	printf("input dir:");
	scanf("%s",createfile);
	char getfilename[FILE_MAXNUM][FILENAME_MAX_LENGTH];
	char checkfilename[FILE_MAXNUM][FILENAME_MAX_LENGTH];
	memset(checkfilename, '\0', sizeof(checkfilename));
	memset(getfilename, '\0', sizeof(getfilename));
	int j = 0, k = 0,s=0;;
	for (int i = 0;i<FILE_MAX_LENGTH; i++)//��ȡÿһ��Ŀ¼����
	{
		if (createfile[i] == '\0')
			break;
		if (createfile[i] == '/')
		{
			
			j = 0; 
			k++;
		}
		else 
		{
			getfilename[k][j] = createfile[i];
			j++;
		}
	}
	
	//����ļ����Ƿ��ظ�
	readinode(uPath);

	//����Ŀ¼
	int createFile=-1;
	for (int i = 0; i < TOTAL_INODE; i++)
	{

		createFile = -1;

		if (inode[0].name[0] == '\0')
		{
			createFile = 0;
			break;
		}
		createFile=1;
		for(int i=0;i<TOTAL_INODE;i++)if(inode[i].file_type==0){createFile=0;break;}
		if(createFile==1)break;
		//��i���ڵ���ϢΪ�գ�ǰ������ͬ�ڵ���Ϣ�ļ������ж�·���Ƿ���ȷ
		if (inode[i].name[0] == '\0')
		{
			for (int i2=0; i2 < TOTAL_INODE; i2++)//���Ҵ����ļ�����һĿ¼��Ϣ
			{
				if (inode[i2].name[0] == '\0')
				{
					createFile = 2;//·�������޷������ļ�
					break;
				}
				for (int l = 0; l < FILENAME_MAX_LENGTH; l++)
				{
					int lastnode;
					if (inode[i2].name[l] != getfilename[k - 1][l])//��ͬ���ļ���������һ�ڵ��ж�
					{
						break;
					}
					if (l==FILENAME_MAX_LENGTH-1||getfilename[k - 1][l+1] == '\0')//��������һ�ļ�ͬ���ļ�,�ж���һ�ļ�·���봴��·���Ƿ���ͬ
					{

						if (k - 1 == 0)
						{
							createFile = 3;
							break;
						}
						s=i2;
						lastnode = inode[i2].lastInode;
						
						for (int i4 = 2;; i4++)
						{
							for (int i5 = 0; i5 < FILENAME_MAX_LENGTH; i5++)
							{
								if (inode[lastnode].name[i5] != getfilename[k - i4][i5])
								{
									createFile = 0;
									break;//�ýڵ���Ϣ���Ǵ���
								}
								if (i5 == FILENAME_MAX_LENGTH - 1 || getfilename[k - i4][i5 + 1] == '\0')
								{
									lastnode = inode[lastnode].lastInode;
									break;
								}

							}
							if (createFile == 0)
								break;
							if (k - i4 == 0)
							{
								
								createFile = 3;//·����ȷ�����������ļ�
								break;
							}

						}
						
					}
					if (createFile == 3)
						break;//·����ȷ�����������ļ�
					if (l == FILENAME_MAX_LENGTH - 1 && createFile == 0)
					{
						createFile = 2;//·�������޷������ļ�
						break;
					}
					
				}
				if (createFile != -1)
						break;
			}
			break;
		}

		for (int i1 = 0; i1 < FILENAME_MAX_LENGTH; i1++)
		{
			if (inode[i].name[i1] != getfilename[k][i1])//��ͬ���ļ���������һ���ڵ��жϡ�
			{
				break;
			
			}
			if ( i1 == FILENAME_MAX_LENGTH - 1||getfilename[k][i1+1]=='\0')//����ͬ���ļ�����ȡͬ���ļ�·�����ж��Ƿ��봴��·����ͬ
			{
				int lastinode;
				lastinode = inode[i].lastInode;
				for (int i2 = 1;; i2++)
				{
					if (k - i2< 0)
					{
						printf("·����ͬ��������ͬ�ļ�");
						createFile = 4;//
						break;
					}
					for (int i3 = 0; i3 < FILENAME_MAX_LENGTH; i3++)
					{
						if (inode[lastinode].name[i3] != getfilename[k - i2][i3])
						{
							createFile = 1;
							break;
							
						}
						if (i3 == FILENAME_MAX_LENGTH - 1 || getfilename[k - i2][i3 + 1] == '\0')
						{
							lastinode = inode[lastinode].lastInode;
							break;
						}
					}
					if (createFile == 1)
						break;
					if (k - i2 == 0)
					{
						printf("·����ͬ��������ͬ�ļ�");
						createFile = 4;//
						break;
					}
				}
			}
			if (createFile == 1 || createFile == 4)
			{
				break;
			}
				
		}
		if (createFile == 4)
			break;//����ͬ���ļ�
	}

	if (createFile == 0) 
	{
		for (int i = 0; i < FILENAME_MAX_LENGTH; i++)
		{
			if (getfilename[k][i] == '\0')
				break;
			inode[0].name[i] = getfilename[k][i];
			
		}
		
		printf("%s", inode[0].name);
		saveInode(uPath);
		printf("�洢������Ϣ\n");
	}
	if (createFile == 1)
		printf("�����������޷������ļ�\n");
	if (createFile == 2)
		printf("·�������޷������ļ�\n");
	if (createFile == 3)
	{   
		int x;
		for( x=0;x<TOTAL_INODE;x++)if(inode[x].file_type==0)break;
		if(x==TOTAL_INODE)printf("no inode");
		else{
			inode[x].lastInode=s;
			inode[x].file_size = 0;
			inode[x].file_type = 2;
			inode[x].protection = 2;
			inode[x].lastInode = nowin;
			strcpy(inode[x].name,getfilename[k]);
		}
		
		saveInode(uPath);
		printf("·����ȷ�����������ļ�\n");
		//node.file_type = 1;
		//node.user_id=
	}
	if (createFile == 4)
	printf("����ͬ���ļ�\n");



}
void _dir(char* uPath){
	readinode(uPath);
	printf("files:\n");
	for(int i=0;i<TOTAL_INODE;i++)
		if(inode[i].lastInode==nowin&&inode[i].file_type==1)printf(" %s  ",inode[i].name);
	printf("\ndirs:\n");
	for(int i=0;i<TOTAL_INODE;i++)
		if(inode[i].lastInode==nowin&&inode[i].file_type==2&&i!=0)printf(" %s  ",inode[i].name);
	printf("\n");
}
