#include<stdbool.h>
#include"user.c"
#define TOTAL_USER 32 //The file system allows maximum number of users
#define USER_UNDEFINE 32

#define USER_NAME_MAX_LENGTH 32 // Max length of the username
#define USER_PASSWORD_MAX_LENGTH 16 // Max length of the password

#define SUPERUSER 0
#define IDFILE "log"
#define OPTFILE "/opt/user/"

struct user
{
    int user_id;
    char user_name[USER_NAME_MAX_LENGTH];
    char user_password[USER_PASSWORD_MAX_LENGTH];
}u[TOTAL_USER],*user;

int checkUser(const char* name);

int getFoundedID(const char* name);

struct user* login(const char* name,  const char* password);

bool createUser(const char* name, const char* password);

void initUser();

bool openUser();

void listUsers();

void saveUser();

char* returnLog(char* name);

char* returnPath(char* name);