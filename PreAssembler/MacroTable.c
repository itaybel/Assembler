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

MacroNode* createMacroNode(){
    
    MacroNode* new_node = malloc(sizeof(struct MacroNode));
    if(new_node == NULL){
        printf("Error, couldn't allocate memory");
        return NULL;
    }

    new_node -> name = NULL;
    new_node -> content = (char*)malloc(sizeof(char) * MAX_LINE_LENGTH); /* we need to allocate the first line, since we use realloc when adding more lines */
    new_node -> contentLength = 0;

    return new_node;

}
