#ifndef MACRO_H
#define MACRO_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#define MAX_LINE_LENGTH 80

typedef struct Node
{
    char* name;
    char* content;
    int contentLength;
    struct Node *next;
} Node;

Node* CreateNode(char *macro_name);

void DestroyLinkList(Node* head);

/*Struct Node *InserNode(linklist_t head, struct Node *node_to_insert);*/

void InsertNode(struct Node** head_ref, struct Node* new_node);

/*struct Node *RemoveNode(linklist_t head, struct Node *node_to_remove);*/

struct Node *SearchNode(Node* head, char* name);

#endif
