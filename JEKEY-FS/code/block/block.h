#include<stdio.h>
#include<string.h>


struct block{
    int Length;
    int isused;
    char data[100];
};

void cleanblock(){
    FILE*fp;
    struct block c;
    c.isused=0;
    c.Length=0;
    c.data[0]='\0';
        if((fp=fopen("D:\\test.txt","w+"))==NULL)printf("block cant open");
         else{for (int i=0;i<10;i++)fwrite(&c,sizeof(struct block),1,fp);
             fclose(fp);
         }
}
void writeblock(struct block Block[]){
        FILE*fp;
        if((fp=fopen("D:\\test.txt","w+"))==NULL)printf("block cant open");
         else{for (int i=0;i<1;i++)fwrite(&Block[i],sizeof(struct block),1,fp);
             fclose(fp);
         }
    }
 bool readblock(struct block re[10]){
        FILE*fp;
		if((fp=fopen("D:\\test.txt","r+"))==NULL){printf("block cant open\n");return false;}
         else{for (int i=0;i<1;i++)fread(&re[i],sizeof(struct block),1,fp);
             fclose(fp);
			 return true;
         }
       
    }