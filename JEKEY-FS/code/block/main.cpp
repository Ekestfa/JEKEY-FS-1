#include<stdio.h>
#include<string.h>
#include"inode.h"
#include"block.h"
#define FILE_MAX_LENGTH 200
#define FILENAME_MAX_LENGTH 20
#define FILE_MAXNUM 10
short nowin = 0;//��ǰĿ¼
char nowins[10]="user";
short openinode[]={0,0,0,0,0};
void createfile(){
    struct block re[10];
	if (readblock(re)) {
		int i = 0, n = 1;
		for (; i < 10; i++) {
			if (re[i].isused == 0)break;
		}
		if (i < 10){
			readinode();
			for (; n < TOTAL_INODE; n++) if (inode[n].file_type == 0) break;
		if (n == TOTAL_INODE)printf("no enough inode");
		else {
			printf("input your file name:");
			char name[10];
			scanf("%s", &name);
			printf("input 0:read 1:write 2:read&write\n");
			int r;
			scanf("%d", &r);
			inode[n].blockid = i;
			inode[n].file_size = 0;
			inode[n].file_type = 1;
			inode[n].protection = 2;
			inode[n].lastInode = nowin;
			strcpy(inode[n].name,name);
			saveInode();
		}
	}
    else printf("not enough storage space!\n");
   }    
}
void openfile(){
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
		if (openadd[i] == NULL)
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
	for (int i = 0; i < TOTAL_INODE; i++)
	{
		openFile = -1;
		for (int i1 = 0; i1 < FILENAME_MAX_LENGTH; i1++)
		{
			if (inode[i].name[i1] != getfilename[k][i1])//��ͬ���ļ���������һ���ڵ��жϡ�
			{
				break;

			}
			if (i1 == FILENAME_MAX_LENGTH - 1 || getfilename[k][i1 + 1] == NULL)//����ͬ���ļ�����ȡͬ���ļ�·�����ж��Ƿ��봴��·����ͬ
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
						if (i3 == FILENAME_MAX_LENGTH - 1 || getfilename[k - i2][i3 + 1] == NULL)
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
void closefile(){
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
		if (closefile[i] == NULL)
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
	
	
	for (int i = 0; i < TOTAL_INODE; i++)
	{
		closeFile = -1;
		for (int i1 = 0; i1 < FILENAME_MAX_LENGTH; i1++)
		{
			if (inode[i].name[i1] != getfilename[k][i1])//��ͬ���ļ���������һ���ڵ��жϡ�
			{
				break;

			}
			if (i1 == FILENAME_MAX_LENGTH - 1 || getfilename[k][i1 + 1] == NULL)//����ͬ���ļ�����ȡͬ���ļ�·�����ж��Ƿ��봴��·����ͬ
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
						if (i3 == FILENAME_MAX_LENGTH - 1 || getfilename[k - i2][i3 + 1] == NULL)
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
void readfile(char* name){
	readinode();
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
		readblock(re);
		printf("%s:%s",name,re[inode[i].blockid].data);
		}
	}




}
void writefile(char*name){
	readinode();
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
		readblock(re);
		printf("please input date:");
		scanf("%s",re[inode[i].blockid].data);
		writeblock(re);
		}
	}
}
void changenowin(char* di){
	char*token;
	short fir=nowin;
	int i=0;
	token = strtok(di,"/");
	while (token!= NULL) {
		if(strcmp(token,".")!=0){
			readinode();
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
void mkdir(){
	
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
		if (createfile[i] == NULL)
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
	readinode();

	//����Ŀ¼
	int createFile=-1;
	for (int i = 0; i < TOTAL_INODE; i++)
	{

		createFile = -1;

		if (inode[0].name[0] == NULL)
		{
			createFile = 0;
			break;
		}
		createFile=1;
		for(int i=0;i<TOTAL_INODE;i++)if(inode[i].file_type==0){createFile=0;break;}
		if(createFile==1)break;
		//��i���ڵ���ϢΪ�գ�ǰ������ͬ�ڵ���Ϣ�ļ������ж�·���Ƿ���ȷ
		if (inode[i].name[0] == NULL)
		{
			for (int i2=0; i2 < TOTAL_INODE; i2++)//���Ҵ����ļ�����һĿ¼��Ϣ
			{
				if (inode[i2].name[0] == NULL)
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
					if (l==FILENAME_MAX_LENGTH-1||getfilename[k - 1][l+1] == NULL)//��������һ�ļ�ͬ���ļ�,�ж���һ�ļ�·���봴��·���Ƿ���ͬ
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
								if (i5 == FILENAME_MAX_LENGTH - 1 || getfilename[k - i4][i5 + 1] == NULL)
								{
									lastnode = inode[lastnode].lastInode;
									break;
								}

							}
							if (createFile == 0)
								break;
							if (k - i4 == 0)
							{
								
								createFile = 3;//·����ȷ���������ļ�
								break;
							}

						}
						
					}
					if (createFile == 3)
						break;//·����ȷ���������ļ�
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
			if ( i1 == FILENAME_MAX_LENGTH - 1||getfilename[k][i1+1]==NULL)//����ͬ���ļ�����ȡͬ���ļ�·�����ж��Ƿ��봴��·����ͬ
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
						if (i3 == FILENAME_MAX_LENGTH - 1 || getfilename[k - i2][i3 + 1] == NULL)
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
			if (getfilename[k][i] == NULL)
				break;
			inode[0].name[i] = getfilename[k][i];
			
		}
		
		printf("%s", inode[0].name);
		saveInode();
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
		
		saveInode();
		printf("·����ȷ���������ļ�\n");
		//node.file_type = 1;
		//node.user_id=
	}
	if (createFile == 4)
	printf("����ͬ���ļ�\n");



}

void dirall(){
	readinode();
	printf("files:\n");
	for(int i=0;i<TOTAL_INODE;i++)
		if(inode[i].lastInode==nowin&&inode[i].file_type==1)printf(" %s  ",inode[i].name);
	printf("\ndirs:\n");
	for(int i=0;i<TOTAL_INODE;i++)
		if(inode[i].lastInode==nowin&&inode[i].file_type==2&&i!=0)printf(" %s  ",inode[i].name);
	printf("\n");
}
void main (){
	cleanblock();//��ʼ��
	initInode();//��ʼ��
	int i;
	char dir[100];
	char name[10];
    int x=1;
    while(x==1){
	printf("%s>>",nowins);
    scanf("%d",&i);
    switch(i){
        case 0:x++;break;
		case 1:{createfile();break;}
		case 2:printf("please input your dir��"); scanf("%s",dir);changenowin(dir);printf("%d",nowin); break;
		case 3:printf("please input readfilename:");scanf("%s",name);readfile(name);break;
        case 4:printf("please input writefilename:");scanf("%s",name);writefile(name);break;
		case 5:dirall();break;
        case 6:mkdir();break;
		case 7:openfile();break;
	    case 8:closefile();break;
        default:printf("??");break;
    }
    }
}
