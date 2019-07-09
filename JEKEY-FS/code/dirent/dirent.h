#define FILE_MAX_LENGTH 200
#define FILENAME_MAX_LENGTH 20
#define FILE_MAXNUM 10

void create(char* uPath);

void open();

void close();

void read(char* name, char* uPath);

void write(char*name, char* uPath);

void chdir(char* di, char* uPath);

void mkdir();

void _dir(char* uPath);

char* getName(char* username);
