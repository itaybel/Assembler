#include "macro_table.h"




Node* CreateNode(char* macro_name){
    Node* new_node = malloc(sizeof(struct Node));
    if(new_node == NULL){
        printf("Error, couldn't allocate memory");
        return NULL;
    }

    new_node -> name = (char*)malloc(sizeof(char) * (strlen(macro_name) + 1));
    strcpy(new_node->name, macro_name);
    new_node -> content = (char*)malloc(sizeof(char) * (MAX_LINE_LENGTH));
    new_node -> contentLength = 0;
    new_node -> next = NULL;
    
    return new_node;
}


void InsertNode(struct Node** head_ref, struct Node* new_node)
{

    /*Make next of new node as head*/
    new_node->next = (*head_ref);

    /*move the head to point to the new node*/

    (*head_ref)    = new_node;
}



struct Node *SearchNode(Node* head, char* name){
    while(head!= NULL)
    {
        if(strcmp(name,head -> name) == 0)
            return head;

        head = head -> next;
    }

    return NULL;
}




