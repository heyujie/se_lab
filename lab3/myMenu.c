/****************************************
* @file			command line menu V2.0
* @author		HEYUJIE SA17225115
* @version		V2.0
* @date			2017-10-06
* @brief	
****************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<dirent.h>
#include "linklist.h"

#define FILEPATH_MAX 80
#define CMD_MAX_LENGTH 128

void help();		
void getTime();
void getDirectory();
void ls();
void cd();
void cat();
void echo();
void clear();
void exit0();
void cdUpper();
void cdNext(char *nextPath);
void readFile(char *fileName);

char cwdbuff[64] = {0};
char cwdbuffsub[64] = {0};
static tCMDNode head[] =
{
	{"help", "This is help command.", help, &head[1]},
	{"date", "Get current time.", getTime, &head[2]},
	{"pwd", "Show current directory.",getDirectory,&head[3]},
	{"ls", "Show all file of current directory.", ls, &head[4]},
	{"cd", "Open ** derictory.", cd, &head[5]},
	{"cat", "Read the file.", cat, &head[6]},
	{"echo", "printf the message.", echo, &head[7]},
	{"clear", "Clear command line.", clear, &head[8]},
	{"exit", "exit the command line.", exit0, NULL}
};

int main()
{
	char getCommand[CMD_MAX_LENGTH];
	while(1)
	{
		printf("yujie@shell:~$ ");
		scanf("%s",getCommand);
		tCMDNode *p = FindCmd(head,getCommand);
		if(p == NULL)
		{
			printf("error: Wrong Command!!\n");		
		}
		else
		{
			p -> handler();
		}
	}
    return 0;
}

//show help imformation
void help()
{
	readFile("help.txt");
}

//get date and time
void getTime()
{
	
	time_t *timep = malloc(sizeof(*timep));
	time(timep);
	char *nowTime = ctime(timep);
	printf("%s\n",nowTime);
}

//get currence Diretory
void getDirectory()
{
	char *file_path = (char*)malloc(FILEPATH_MAX);
	getcwd(file_path,FILEPATH_MAX);
	printf("%s\n",file_path);
}

//show all currence Directory file
void ls()
{
	DIR*dir;
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
void cd()
{
	char cmd[32];
	scanf("%s",cmd);
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
void cat()
{
	char cmd[32];
	scanf("%s",cmd);
	readFile(cmd);
}

//echo the word
void echo()
{
	char i = 0;	
	char cmd[64];
	while((cmd[i++] = getchar()) != '\n');
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
void clear()
{
	system("clear");
}

//exit
void exit0()
{
	exit(0);
}
