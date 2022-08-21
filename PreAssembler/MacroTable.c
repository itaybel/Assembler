#include "MacroTable.h"
#include <stdlib.h>
#include "string.h"
#include "../Utility/GeneralFunctions.h"

struct MNode{
    char* name;
    int startIndex;
    int length;
    struct MNode* next;
};



macroNode createMacroNode(char* name){
    macroNode new_node = NULL;
    new_node = (macroNode)calloc(1, sizeof(struct MNode));
    
    new_node -> name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(new_node->name, name);
    new_node -> startIndex = 0;
    new_node -> length = 0;

    return new_node;

}



void InsertMacroNode(struct MNode** head, struct MNode* newNode)
{

    if (!(*head)) /* if the list is empty */
    {
        *head = newNode;

    }else{

        /*Make next of new node as head*/
        newNode->next = (*head);

        /*move the head to point to the new node*/

        (*head)  = newNode;
    }
}

struct MNode* SearchNode(macroNode head, char *name){

    while(head != NULL){
        
        if(name != NULL && head->name && strcmp(head -> name, name) == 0){
            return head;
        }
        head = head -> next;
    }
    return NULL;
}



void freeMacroList(struct MNode* node){
    if(node != NULL){
        freeMacroList(node->next);
        free(node->name);
        free(node);
    }
}

int isValidMacroName(char* name){
    int i = 0;

    if (isalpha(name[0]) && strlen(name) <= MAX_LENGTH && !(reservedWord(name))){
        for (i = 0; i < strlen(name); i++) {/*use loop to check isalnum if the word is alphanumeric*/
            if (!isalnum(name[i])) {
                return 0;
            } 
        }
        return 1;
    }
    return 0;
}

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

