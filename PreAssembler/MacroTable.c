#include "MacroTable.h"

/*
This function is used to compare macros with a specified name
it is used in the searchNode function, to determine how to search the node
@param macro - the macro to be compared
@param name - the name to compare with
@return wether the given macro has the given name
*/
int compareMacro(void* macro, void* name){
    return strcmp(((MacroNode*)macro)->name, (char*)name);
}

/*
This function is used to allocate memory and create a new macro node
@param name - the name of the macro
@return a pointer to the new empty macro
*/
MacroNode* createMacroNode(char* name){
    
    MacroNode* new_node = malloc(sizeof(struct MacroNode));
    if(new_node == NULL){
        printf("Error, couldn't allocate memory");
        return NULL;
    }
    new_node -> name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(new_node->name, name);
    new_node -> startIndex = 0;
    new_node -> length = 0;

    return new_node;

}


/*
This function is used to free a macro node
@param node - the macro to be freed
@return none
*/
void freeNode(Node* node){
    free(((MacroNode*)node)->name);
    free(((MacroNode*)node));

}
