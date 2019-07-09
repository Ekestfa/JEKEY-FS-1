#include"block/block.c"
#include"usr/user.h"
#include"inode/inode.c"
#include"dirent/dirent.c"
int main(){
    initUser(); saveUser();
    //cleanblock();//³õÊŒ»¯
	//initInode();//³õÊŒ»¯
	int dirchoose = -1;
    int loginchoose = -1;

	char dir[100];
	char name[10];

    int x=1;

    char* username;
    username = malloc(sizeof(USER_NAME_MAX_LENGTH));
    char* pass;
    pass = malloc(sizeof(USER_PASSWORD_MAX_LENGTH));
    char* userPath;

    while(x==1){
        printf("\t Welcome to JEKEY File System!\n");
        printf("\t *** LOGIN PAGE ***\n");
        printf("\t 1 - Create User.\n");
        printf("\t 2 - Login User.\n");
        printf("\t Please choose your selection: ");
        scanf("%d",&loginchoose);
        switch(loginchoose){
            case 1:{
                printf("Username: ");
                scanf("%s",username);
                printf("Password: ");
                scanf("%s",pass);
                createUser(username,pass);
                break;
            }
            case 2:{
                printf("Username: ");
                scanf("%s",username);
                printf("Password: ");
                scanf("%s",pass);
                if((user = login(username,pass))!=NULL){
                    userPath = returnPath(user->user_name);
                    printf("%s>>",nowins);
                    scanf("%d",&dirchoose);
                    switch(dirchoose){
                        case 0:x++;break;
		                case 1:{create(userPath);break;}
		                case 2:printf("please input your dir£º"); scanf("%s",dir);chdir(dir,userPath);printf("%d",nowin); break;
		                case 3:printf("please input readfilename:");scanf("%s",name);read(name,userPath);break;
                        case 4:printf("please input writefilename:");scanf("%s",name);write(name,userPath);break;
		                case 5:_dir(userPath);break;
                        case 6:mkdir(userPath);break;
		                case 7:open(userPath);break;
	                    case 8:close(userPath);break;
                        default:printf("??");break;
                    }
                }
            }// end of case 2
        }// end of login switch
    return 0;
    }// end of while
}