/****************************************
* @file			/home/yujie/Code/se_lab/lab4
* @item			command line menu V2.8
* @author		HEYUJIE SA17225115
* @version		V2.8
* @date			2017-10-22
* @brief	
****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
#include <unistd.h>
#include <time.h>
#include <dirent.h>*/
#include "linktable.h"
#include "myMenu.h"

#define 	CMD_MAX_LENGTH 		128
#define		CMD_MAX_ARGV_NUM	32

void help();		

//
tLinkTable * head = NULL;

/* data struct and its operations */

typedef struct DataNode
{
    tLinkTableNode * pNext;
    char*   cmd;
    char*   desc;
    void     (*handler)();
} tDataNode;


int SearchCondition(tLinkTableNode * pLinkTableNode,char *cmd)
{
    tDataNode * pNode = (tDataNode *)pLinkTableNode;
    if(strcmp(pNode->cmd, cmd) == 0)
    {
        return  SUCCESS;  
    }
    return FAILURE;	       
}

/* find a cmd in the linklist and return the datanode pointer */
tDataNode* FindCmd(tLinkTable * head, char *argv[])
{
    return  (tDataNode*)SearchLinkTableNode(head,SearchCondition,(void *)argv[0]);
}

/* show all cmd in listlist */
int ShowAllCmd(tLinkTable * head)
{
    tDataNode * pNode = (tDataNode*)GetLinkTableHead(head);
    while(pNode != NULL)
    {
        printf("%s - %s\n", pNode->cmd, pNode->desc);
        pNode = (tDataNode*)GetNextLinkTableNode(head,(tLinkTableNode *)pNode);
    }
    return 0;
}



//Add
int MenuConfig(char *cmd, char *desc, void (*handler)(int argc, char *argv[]))
{
	tDataNode *pNode = NULL;
	if(head == NULL)
	{
		head = CreateLinkTable();
		pNode = (tDataNode *)malloc(sizeof(tDataNode));
    		pNode->cmd = "help";
    		pNode->desc = "This is help command.";
    		pNode->handler = help;
    		AddLinkTableNode(head, (tLinkTableNode *)pNode);	
	}
	pNode = (tDataNode *)malloc(sizeof(tDataNode));
	pNode->cmd = cmd;
	pNode->desc = desc;
	pNode->handler = handler;
	AddLinkTableNode(head, (tLinkTableNode *)pNode);

	return 0;	
}

//
int getPram(char *pcmd, char *argv[])
{
	    char *pcdm0 = 0;
		int argc = 0;
	    pcmd = strtok(pcmd, " ");
        while(pcmd != NULL && argc < CMD_MAX_ARGV_NUM)
        {
            argv[argc++] = pcmd;
            pcmd = strtok(NULL, " ");
        }
        if(argc == 1)
        {
            int len = strlen(argv[0]);
            *(argv[0] + len - 1) = '\0';
        }
		return argc;
}

//ExecuteMenu
int ExecuteMenu()
{
	char getCommand[CMD_MAX_LENGTH];
	char *pcmd = NULL;
   /* cmd line begins */
    while(1)
    {
		int argc = 0;
    	char *argv[CMD_MAX_ARGV_NUM];
        printf("yujie@ubuntu~:$");
//        scanf("%s", getCommand);
	    pcmd = fgets(getCommand,CMD_MAX_LENGTH,stdin);
        if(pcmd == NULL)
        {
            continue;
        }
        argc = getPram(pcmd, argv);
        tDataNode *p = (tDataNode*)SearchLinkTableNode(head,SearchCondition,argv[0]);
        if( p == NULL)
        {
            printf("error: Wrong Command!!\n");
            continue;
        }
//        printf("%s - %s\n", p->cmd, p->desc); 
        if(p->handler != NULL) 
        { 
            p->handler(argc,argv);
        }
   
    }
}

//show commmand imformation
void help()
{
    ShowAllCmd(head);
}

