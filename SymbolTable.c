#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "SymbolTable.h"
#include "AddressingMode.h"


/** A single table symbol*/
struct symbol {
    /** Next symbol in table */
    symbolTable next;
    /** Address of the symbol */
    int address;
    /** Key (symbol name) is a string (aka char*) */
    char *key;
    /** Symbol type */
    symbolType type;
};


int isLabel(char *name){
    if(validLabelName(name) && name[strlen(name) -1] == ':'){
        return 1;
    }
    return 0;
}


/*Check length, first char is alpha and all the others are alphanumeric, and not assembly reserved identifier and string size is 30*/
int validLabelName(char *name) {

    int i = 0;

    if (name[0] && strlen(name) <= MAX_LENGTH && !(reservedWord(name))){
        for (i = 0; i < strlen(name) && name[i] != ':'; i++) {/*use loop to check isalnum if the word is alphanumeric*/
            if (!isalnum(name[i])) {
                return 0;
            }
        }

        return 1;
    }
    return 0;
}


void *checkMalloc(int size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        printf("Error: Fatal: Memory allocation failed.");
        exit(1);
    }
    return ptr;
}





void setType(symbolTable symbol,symbolType type){

    symbol->type = type;
}


void setAddress(symbolTable symbol, int address){

    symbol->address = address;
}



int compareSymbol(symbolTable symbol, char *key){
    return strcmp((symbol)->key, key);
}

int isIsSymbolTable(symbolTable symbol, char *key){
    if(symbol != NULL){
        return compareSymbol(symbol, key) || isIsSymbolTable(symbol->next, key);
    }
    return 0;
}



symbolTable createSymbol(char* key,int address){

    symbolTable new_node = checkMalloc(sizeof(struct symbol));
    /*if(new_node == NULL){
        checkMalloc()
        printf("Error, couldn't allocate memory");
        return  NULL;
    }*/
    new_node -> key = (char*)malloc((strlen(key) + 1) * sizeof(char));
    strcpy(new_node->key, key);
    new_node -> address = address;

    return new_node;

}


void InsertSymbolNode(symbolTable* head_ref, char *label, int new_data)
{

/* Allocate node*/

    symbolTable new_node = createSymbol(label,new_data);

    if (!(*head_ref))

/* if the list is empty */

    {
        *head_ref = new_node;

    }else{

/*Make next of new node as head*/

        new_node->next = (*head_ref);


/*move the head to point to the new node*/

        (*head_ref)  = new_node;
    }
}


int getAddress(symbolTable symbol){
    return symbol->address;
}


symbolType getType(symbolTable symbol){
    return symbol->type;
}


char *getSymbol(symbolTable symbol){
    return symbol->key;
}


void printSymbol(symbolTable table){

    while(table != NULL){
        printf("%s\n",table->key);
        /*printf("%d",table->type);*/
        table = table->next;
    }
}

void updateTable(symbolTable table, int IC){

    while(table != NULL) {
        if (table->type == DATA_SYMBOL || table->type == STRUCT_SYMBOL) {
            table->address += IC;
        }
    table = table->next;
    }
}




void freeTable(symbolTable table) {
    symbolTable prevSymbol, currSymbol = table;
    while (currSymbol != NULL) {
        prevSymbol = currSymbol;
        currSymbol = currSymbol->next;
        free(prevSymbol->key);
        free(prevSymbol);
    }
}
