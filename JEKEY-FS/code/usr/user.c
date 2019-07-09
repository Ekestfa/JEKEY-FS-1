#include<stdbool.h>
#include"user.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<dirent.h>


int checkUser(const char* name){    // EXISTS = -1, DOESN'T EXIST = i+1
    int i = 0;
    int found = 0;
    while(u[i].user_name[0] != '\000'){
        if(!strcmp(u[i].user_name,name)){
            found = 1;
            break;
        }else{
            found = 0;
        }
        i++;
    }
    if(found == 1){
        printf("User exists!\n");
        return -1;
    }else{
        printf("User doesn't exist, you can create new one!\n");
        return i;
    }
}

int getFoundedID(const char* name){
    int i = 0;
    int found = 0;
    while(u[i].user_name[0] != '\000'){
        if(!strcmp(u[i].user_name,name)){
            found = 1;
            return i;
        }
        i++;
    }
}

bool createUser(const char* name, const char* password){
    char* fn = NULL;
    char* command = NULL;
    char* command_mkdr = NULL; 
    char* command_chmod = NULL;
    char* logPath = NULL;
    
    int checker = -1;
    int mkdrLen = strlen("sudo mkdir ");
    int chmodLen = strlen("sudo chmod 777");
    int argvLen = strlen(name);


    command_mkdr = malloc(mkdrLen);
    fn = malloc(sizeof(OPTFILE) + argvLen + 1);
    fn = strcpy(fn, OPTFILE); // fn: /opt/
    fn = strcat(fn, name); // fn: /opt/$Username
    int fnLen = strlen(fn);

    printf("Checking for user...\n");
    checker = checkUser(name);
    strcpy(u[checker].user_name,name);
    strcpy(u[checker].user_password,password);
    if((checker != -1) && (checker <=TOTAL_USER)){
        // Creating user directory;
        command = malloc(mkdrLen + fnLen);
        command_mkdr = "sudo mkdir ";
        command_chmod = "sudo chmod 777 ";
        command = strcpy(command, command_mkdr);
        command = strcat(command, fn);
        system(command);
        
        printf("Created user folder!\n");

        // Changing auth of the dir
        command = malloc(chmodLen + fnLen);
        command = strcpy(command, command_chmod);
        command = strcat(command, fn);
        system(command);
    }

    logPath = returnPath(u[checker].user_name);
    FILE* userlog = fopen(logPath,"r");

    printf("Checking for user log...\n");

    if(userlog = fopen(logPath,"r")){
        fclose(userlog);
        printf("----- User log already exists! -----\n");
        return 0;
    }

    userlog = fopen(logPath,"wb+");
    printf("----- User log doesn't exist! -----\n");
    printf("----- Creating logs! -----\n");
    fwrite(&u, sizeof(u), 1, userlog);
    printf("----- Logs Created. -----\n");
    fclose(userlog);
        
    free(fn);free(logPath);free(command);free(command_mkdr);free(command_chmod);free(logPath);free(userlog);
    return 1;
}

char* returnPath(char* name){
    char* path = IDFILE;
    char* fn = NULL;
    char* input = NULL; 
    int argvLen = strlen(name);
    int logLen = strlen(path);

    fn = malloc(sizeof(OPTFILE) + argvLen + 1);
    fn = strcpy(fn, OPTFILE); // fn: /opt/
    fn = strcat(fn, name); // fn: /opt/$Username

    int fnLen = strlen(fn);
    input = malloc(fnLen + logLen + sizeof("/"));
    input = strcpy(input,fn); // opt/$Username
    input = strcat(input,"/");
    input = strcat(input,path); // /opt/$Username/log

    free(fn);
    return input;
}

void listUsers(){

    int i = 0;
    char* inputPath = NULL;
    FILE* f = NULL;
    while(u[i].user_name[0] != '\000'){
        inputPath = returnPath(u[i].user_name);
        if(f = fopen(inputPath,"rb")){
            fread(&u[i],sizeof(u),1,f);
            printf("User ID: %d, User name: %s, Pass: %s\n",u[i].user_id, u[i].user_name, u[i].user_password);
        }
        i++;
        fclose(f);
    }
    free(inputPath);
    free(f);
}

struct user* login(const char* name, const char* password){
    int checker = -1;
    checker = checkUser(name);
    int id =-1;
    char* inputPath = NULL;
    // Checker == -1 is found name
    if(checker == -1){
        id = getFoundedID(name);
        FILE* f = NULL;
        inputPath = returnPath(u[id].user_name);
        if(f = fopen(inputPath,"rb")){
            fread(&u[id],sizeof(u),1,f);
            if(strcmp((u+id)->user_password,password)){
                printf("Password is not correct!\n");
                return NULL;
            }else{
                printf("Successfully logined.\n");
                return(u+id);
            }// else end
        } // if end
        fclose(f);
    }// if end
    free(inputPath);
}

void initUser(){
    // Initialization for NULL
    for(int i = 0; i < TOTAL_USER; i++){
        u[i].user_id = i;
        memset(u[i].user_name, '\0',sizeof(u[i].user_name));
        memset(u[i].user_password, '\0',sizeof(u[i].user_password));
    }
}

bool openUser();

void saveUser(){
    int j = 0;
    FILE* fp;
    DIR* d;
    struct dirent* dir;
    char* filenames[USER_NAME_MAX_LENGTH];
    char* fn = NULL;
    fn = malloc( sizeof(strlen(OPTFILE)) + 1 );
    fn = strcpy(fn, OPTFILE);
    d = opendir(fn);
    for(int i = 0; i<TOTAL_USER; i++){
        if(d){
        while((dir = readdir(d)) != NULL){
                if(strcmp(dir->d_name,".") != 0  && strcmp(dir->d_name,"..") != 0){
                    filenames[i] = malloc(sizeof(TOTAL_USER));
                    strcpy(filenames[i],dir->d_name);
                    strcpy(u[j].user_name,filenames[i]);
                    u[j].user_id = j;
                    j++;
                }// if end
            }// while end*/
        } //if end
    }// for end
    free(fp);free(d);free(fn);
}