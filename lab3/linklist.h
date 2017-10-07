#ifndef __LINKLIST_H__
#define __LINKLIST_H__

typedef struct CMDNode
{
    char* cmd;
    char* disc;
    void (*handler)();
    struct CMDNode *next;
}tCMDNode;

tCMDNode* FindCmd(tCMDNode* head, char* cmd);

void ShowAllCmd(tCMDNode* head);

#endif
