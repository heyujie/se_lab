/****************************************
* @file			command line menu V1.0
* @author		HEYUJIE SA17225115
* @version		V1.0
* @date			2017-09-23
* @brief	
****************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<dirent.h>

#define FILEPATH_MAX 80	
char cwdbuff[64] = {0};
char cwdbuffsub[64] = {0};
		
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
	chdir("/home/yujie");
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


int main()
{
	char getCommand[32];
	while(1)
	{
		printf("yujie@shell:~$ ");
		scanf("%s",getCommand);
		if(!strcmp(getCommand,"date"))			//date
		{
			getTime();
		}
		else if(!strcmp(getCommand,"pwd"))		//pwd	
		{
			getDirectory();
		}
		else if(!strcmp(getCommand,"help"))		//help
		{	
			readFile("help.txt");
			
		}
		else if(!strcmp(getCommand, "cd"))		//cd	
		{
			scanf("%s",getCommand);
			if(!strcmp(getCommand,"/"))
			{
				cd();
				continue;
			}
			else if(!strcmp(getCommand,".."))
			{
				cdUpper();
				continue;
			}
			else
			{
				cdNext(getCommand);
				continue;			
			}
			
		}
		else if(!strcmp(getCommand, "cat"))		//cat	
		{
			scanf("%s",getCommand);
			readFile(getCommand);
		}
		else if(!strcmp(getCommand, "ls"))		//ls	
		{
			ls();
		}
		else if(!strcmp(getCommand, "clear"))		//clear
		{
			system("clear");
		}
		else if(!strcmp(getCommand, "exit"))		//exit
		{
			exit(0);
		}
		else
		{
			printf("error,enter 'help' for help!\n");
		}
	}
    return 0;
}
