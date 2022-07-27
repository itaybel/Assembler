#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ctype.h"
#include "SymbolTable.h"
#include "AddressingMode.h"


typedef struct symbolNode
{
    char* name;
    char* address;
    char* def;


/* symbol can be external,can be entry, .data, or command*/
} SymbolNode;



int validLabelName(char *name) {
    /*Check length, first char is alpha and all the others are alphanumeric, and not assembly reserved identifier and string size is 30*/
    int i = 0;

    if (name[0] && strlen(name) <= 30 && isalpha(name[0]) && reservedWord(name)) {/*use loop to check isalnum if the word is alphanumeric*/
        while (name[i]) {
            if (isalnum(name[i])) {
                i++;
                continue;
            } else {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

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
    new_node -> name = NULL;
    new_node -> address = NULL;

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

