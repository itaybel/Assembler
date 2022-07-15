#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "SymbolTable.h"


typedef struct symbolNode
{
    char* name;
    char* data;
    char* string;
    int startIndex;
    int length;
} SymbolNode;

int compareSymbol(void* symbol, void* name){
    return strcmp(((SymbolNode*)symbol)->name, (char*)name);
}


/*
This function is used to allocate memory and create a new macro node
@param name - the name of the macro
@return a pointer to the new empty macro
*/

struct SymbolNode* createSymbolNode(char* name){

    SymbolNode* new_node = malloc(sizeof(SymbolNode));
    if(new_node == NULL){
        printf("Error, couldn't allocate memory");
        return NULL;
    }
    new_node -> name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(new_node->name, name);
    new_node -> startIndex = 0;
    new_node -> length = 0;

    return (struct SymbolNode *) new_node;

}


/*
This function is used to free a macro node
@param node - the macro to be freed
@return none
*/

void freeNode(void* node){
    free(((SymbolNode *)node)->name);
    free(((SymbolNode *)node));

}






