#include<stdbool.h>
#define BLOCKPATH "block"

struct block{
    int Length;
    int isused;
    char data[100];
};

void cleanblock(char* userPath);

void writeblock(struct block Block[],char* userPath);

bool readblock(struct block re[10],char* userPath);

char* blockPath(char* userPath);