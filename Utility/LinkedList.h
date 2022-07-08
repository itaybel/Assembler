#ifndef LINKLIST_H
#define LINKLIST_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 80

typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

Node* CreateNode();

void DestroyLinkList(Node* head);

/*Struct Node *InserNode(linklist_t head, struct Node *node_to_insert);*/

Node* InsertNode(Node** head_ref,void* new_data);

/*struct Node *RemoveNode(linklist_t head, struct Node *node_to_remove);*/

void *SearchNode(Node* head, void *data, int(*cmp_func)(void*, void*));

#endif
