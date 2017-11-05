#ifndef _MYMENU_H_
#define _MYMENU_TABLE_H_

//add cmd to Menu
int MenuConfig(char *cmd, char *desc, void (*handler)(int argc, char *argv[]));

//Menu Engine Execute
int ExecuteMenu();


#endif
