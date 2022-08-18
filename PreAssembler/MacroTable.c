#include "MacroTable.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "../Utility/GeneralFunctions.h"

struct MNode{
    char* name;
    int startIndex;
    int length;
    struct MNode* next;
};


/*
This function is used to allocate memory and create a new macro node
@param name - the name of the macro
@return a pointer to the new empty macro
*/
macroNode createMacroNode(char* name){

    macroNode new_node = checkMalloc(sizeof(struct MNode));

    new_node -> name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(new_node->name, name);
    new_node -> startIndex = 0;
    new_node -> length = 0;

    return new_node;

}




/*
This function is used insert a new macro to the macro list
@param head_ref - the current head of the linked list
@param new_data - the name of the new macro to be added
*/
void InsertMacroNode(struct MNode** head_ref, struct MNode* new_node)
{

    if (!(*head_ref)) /* if the list is empty */
    {
        *head_ref = new_node;

    }else{

        /*Make next of new node as head*/
        new_node->next = (*head_ref);

        /*move the head to point to the new node*/

        (*head_ref)  = new_node;
    }
}


/*
This function is used to search for a specific macro in a linked list
@param head - the current head of the linked list
@param name - the name to search
@return the found node, NULL if it couldn't be found
*/
struct MNode* SearchNode(struct MNode* head, char *name){

    while(head != NULL){

        if(strcmp(head -> name, name) == 0){
            return head;
        }
        head = head -> next;
    }
    return NULL;
}



/*
This function is used to free the macro list
@param head - the current node in the linked list
@return none
*/
void freeMacroList(struct MNode* node){
    if(node != NULL){
        freeMacroList(node->next);
        free(node->name);
        free(node);
    }
}


   char* name;
    int startIndex;
    int length;
    struct MNode* next;

char* getName(struct MNode* node){
    return node->name;
}
int getStartIndex(struct MNode* node){
    return node->startIndex;
}

int getLength(struct MNode* node){
    return node->length;
}

void setStartIndex(struct MNode* node, int startIndex){
    node->startIndex = startIndex;
}
void setLength(struct MNode* node, int length){
    node->length = length;
}