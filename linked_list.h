#ifndef LINKLIST_H
#define LINKLIST_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 80




typedef struct Node * linklist_t;


linklist_t CreateLinkList();

void DestroyLinkList(linklist_t head);

Struct Node *InserNode(linklist_t head, struct Node *node_to_insert);

/*struct Node *RemoveNode(linklist_t head, struct Node *node_to_remove);*/

struct Node *SearchNode(linklist_t head, void *data,int(*compare_func)(void *, void *));

#endif
