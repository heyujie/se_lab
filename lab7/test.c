#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include "myMenu.h"

#define 	FILEPATH_MAX  		80

char cwdbuff[64] = {0};
char cwdbuffsub[64] = {0};

void getTime(int argc, char *argv[]);
void getDirectory(int argc, char *argv[]);
void ls(int argc, char *argv[]);
void cd(int argc, char *argv[]);
void cat(int argc, char *argv[]);
void echo(int argc, char *argv[]);
void clear(int argc, char *argv[]);
void exit0(int argc, char *argv[]);
void cdUpper();
void cdNext(char *nextPath);
void readFile(char *fileName);

int main(int argc, char *argv[])
{
	MenuConfig("date", "Get current time.", getTime);
	MenuConfig("pwd", "Show current directory.", getDirectory);
	MenuConfig("ls", "Show all file of current directory.", ls);
	MenuConfig("cd", "Open ** derictory.", cd);
	MenuConfig("cat", "Read the file.", cat);
	MenuConfig("echo", "printf the message.", echo);
	MenuConfig("clear", "clear command line.", clear);
	MenuConfig("exit", "exit the command line.", exit0);

	ExecuteMenu();
}

//get date and time
void getTime(int argc,char*argv[])
{
    time_t *timep = malloc(sizeof(*timep));
    time(timep);
    char *nowTime = ctime(timep);
    printf("%s\n",nowTime);
}

//get currence Diretory
void getDirectory(int argc, char *argv[])
{
    char *file_path = (char*)malloc(FILEPATH_MAX);
    getcwd(file_path,FILEPATH_MAX);
    printf("%s\n",file_path);
}

//show all currence Directory file
void ls(int argc, char *argv[])
{
	int parm = 0;
    DIR*dir;
	if(argc > 2)
	{
		printf("error!too many parameter!");
		return;
	}	
	while((parm = getopt(argc, argv, "nb"))!= -1)
	{
		switch(parm)
			{
				case 'n':printf("this command with a n param!\n");
							break;
				case 'b':printf("this command with a b param!!\n");
							break;
				default: break;
			}
			break;
	}
	optind=0;
	opterr=0;
    struct dirent *rent;
    dir = opendir(".");
    int cnt = 0;
    while((rent = readdir(dir)))
    {
        printf("%ld\t%s\n",rent->d_ino,rent->d_name);
    }
    printf("\n");
    closedir(dir);
}

//open the default directory
void cd(int argc, char *argv[])
{
	int parm = 0;
	int i = 0;
    char cmd[32];
	if(argc > 2)
	{
		printf("error!too many parameter!");
		return;
	}	
	while(*argv[1] != '\n')cmd[i++] = *(argv[1]++);
    if(!strcmp(cmd,"/"))
    {
        chdir("/home/yujie");	
    }
    else if(!strcmp(cmd,".."))
    {
        cdUpper();
    }
    else
    {
        cdNext(cmd);			
    }
}

//open the upper directory
void cdUpper()
{
    int cdCount = 0;
    int cdI = 0;
    int cdLen = 0;
    char *result = (char*)malloc(sizeof(char*));
    getcwd(cwdbuff,FILEPATH_MAX);
    strcpy(cwdbuffsub,cwdbuff);
    while(cwdbuffsub[cdLen++]!='\0'); 
    result = strtok( cwdbuff, "/" );
    while( result != NULL ) 
    {
        result = strtok( NULL, "/" );
        cdCount++;
    }
    if(cdCount>0)
    {
        while(cdCount)
        {
            if(cwdbuffsub[cdI++]=='/')
            cdCount--;
        }
        for(;cdI<cdLen;cdI++)
        {
            cwdbuffsub[cdI] = '\0';
        }
        strcpy(cwdbuff,cwdbuffsub);
        chdir(cwdbuffsub);	
    }
}

//open the next directory
void cdNext(char *nextPath)
{
    getcwd(cwdbuff,FILEPATH_MAX);
    strcat(cwdbuff,"/");
    strcat(cwdbuff,nextPath);
    chdir(cwdbuff);
}

//cat a file
void cat(int argc, char *argv[])
{
	int i = 0;
    char cmd[32];
	if(argc > 2)
	{
		printf("error!too many parameter!");
		return;
	}	
	while(*argv[1] != '\n')cmd[i++] = *(argv[1]++);
    readFile(cmd);
}

//echo the word
void echo(int argc, char *argv[])
{
    char i = 0;	
    char cmd[32];
	if(argc > 2)
	{
		printf("error!too many parameter!");
		return;
	}	
	while(*argv[1] != '\n')cmd[i++] = *(argv[1]++);
    cmd[i] = '\0';
    printf("%s\n",cmd);
}

//read the file
void readFile(char *fileName)
{
    FILE *pfile;
    char myChar;
    char *str[127];
    pfile = fopen(fileName,"r");
    while((myChar = fgetc(pfile)) != EOF)
    {
        putchar(myChar);
    }
    putchar('\n');
    fclose(pfile);
}

//clear
void clear(int argc, char *argv[])
{
    system("clear");
}

//exit
void exit0(int argc, char *argv[])
{
    exit(0);
}
