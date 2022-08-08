#ifndef LINKLIST_H
#define LINKLIST_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

Node* CreateNode();

void DestroyLinkList(Node* head);

/*Struct Node *InserNode(linklist_t head, struct Node *node_to_insert);*/

void InsertNode(Node** head_ref, void* new_data);
/*struct Node *RemoveNode(linklist_t head, struct Node *node_to_remove);*/

Node* SearchNode(Node* head, void *data, int(*cmp_func)(void*, void*));

void freeList(Node* head, void(*free_func)(Node*));
#endif
