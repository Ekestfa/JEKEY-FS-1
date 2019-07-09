#include<stdio.h>
#include<string.h>
#include<stdbool.h>

struct block{
    int Length;
    bool isused;
    char data[100];
};
int findblock();
bool bfree(int id){
   //struct block Block[10]=fopen
   // Block[id].isused=0;
    //Block[id].Length=0;
}
void writeblock(struct block Block[]){
        FILE*fp;
        if((fp=fopen("/home/jwb/code/test.txt","w++"))==NULL)printf("block cant open");
         else{for (int i=0;i<size(Block);i++)fprintf(fp,"%d;%d;%s\n");
             fclose(fp);
         }
    }
void main (){
    struct block Block[1];
    Block[0].isused=1;
    Block[0].Length=5;
    Block[0].data[0]="abcde";
    writeblock(Block);
    
}
