/****************************************
* @file     	/home/yujie/Code/se_lab/lab4
* @item			command line menu V2.5
* @author		HEYUJIE SA17225115
* @version		V2.5
* @date			2017-10-15
* @brief	
****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include "linktable.h"

#define 	FILEPATH_MAX  		80
#define 	CMD_MAX_LENGTH 		128

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

typedef struct DataNode
{
    tLinkTableNode *pNext;
    char *cmd;
    char *desc;
    void (*handler)();
}tDataNode;

char cwdbuff[64] = {0};
char cwdbuffsub[64] = {0};
//declare a tLinkTable


tLinkTable *head = NULL;
//find the command
tDataNode *FindCmd(tLinkTable *head, char *cmd)
{
    tDataNode *pNode = (tDataNode *)GetLinkTableHead(head);
    while (pNode != NULL)
    {
        if (strcmp(pNode->cmd, cmd) == 0)
        {
            return pNode;
        }
        pNode = (tDataNode *)GetNextLinkTableNode(head, (tLinkTableNode *)pNode);
    }
    return NULL;
}
//show the desc
int ShowAllCmd(tLinkTable *head)
{
    tDataNode *pNode = (tDataNode *)GetLinkTableHead(head);
    while (pNode != NULL)
    {
        printf("%s - %s\n", pNode->cmd, pNode->desc);
        pNode = (tDataNode *)GetNextLinkTableNode(head, (tLinkTableNode *)pNode);
    }
    return 0;
}
//init
int InitMenuData(tLinkTable **ppLinktable)
{
    *ppLinktable = CreateLinkTable();

	tDataNode *pNode = (tDataNode *)malloc(sizeof(tDataNode));
    pNode->cmd = "help";
    pNode->desc = "This is help command.";
    pNode->handler = help;
    AddLinkTableNode(*ppLinktable, (tLinkTableNode *)pNode);

    pNode = (tDataNode *)malloc(sizeof(tDataNode));
    pNode->cmd = "date";
    pNode->desc = "Get current time.";
    pNode->handler = getTime;
    AddLinkTableNode(*ppLinktable, (tLinkTableNode *)pNode);

    pNode = (tDataNode *)malloc(sizeof(tDataNode));
    pNode->cmd = "pwd";
	pNode->desc = "Show current directory.";
	pNode->handler = getDirectory;
	AddLinkTableNode(*ppLinktable, (tLinkTableNode *)pNode);

	pNode = (tDataNode *)malloc(sizeof(tDataNode));
	pNode->cmd = "ls";
	pNode->desc = "Show all file of current directory.";
	pNode->handler = ls;
	AddLinkTableNode(*ppLinktable, (tLinkTableNode *)pNode);

	pNode = (tDataNode *)malloc(sizeof(tDataNode));
	pNode->cmd = "cd";
	pNode->desc = "Open ** derictory.";
	pNode->handler = cd;
	AddLinkTableNode(*ppLinktable, (tLinkTableNode *)pNode);

	pNode = (tDataNode *)malloc(sizeof(tDataNode));
	pNode->cmd = "cat";
	pNode->desc = "Read the file.";
	pNode->handler = cat;
	AddLinkTableNode(*ppLinktable, (tLinkTableNode *)pNode);

	pNode = (tDataNode *)malloc(sizeof(tDataNode));
	pNode->cmd = "echo";
	pNode->desc = "printf the message.";
	pNode->handler = echo;
	AddLinkTableNode(*ppLinktable, (tLinkTableNode *)pNode);

	pNode = (tDataNode *)malloc(sizeof(tDataNode));
	pNode->cmd = "clear";
	pNode->desc = "Clear command line.";
	pNode->handler = clear;
	AddLinkTableNode(*ppLinktable, (tLinkTableNode *)pNode);

	pNode = (tDataNode *)malloc(sizeof(tDataNode));
	pNode->cmd = "exit";
	pNode->desc = "exit the command line.";
	pNode->handler = exit0;
	AddLinkTableNode(*ppLinktable, (tLinkTableNode *)pNode);

	return 0;
}

int main ()
{
	char getCommand[CMD_MAX_LENGTH];
	InitMenuData(&head);
	while(1)
	{
		printf("yujie@shell:~$ ");
		scanf("%s",getCommand);
		tDataNode *p = FindCmd(head,getCommand);
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

//show commmand imformation
void help()
{
	ShowAllCmd(head);
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
