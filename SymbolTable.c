#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "SymbolTable.h"
#include "Utility/GeneralFunctions.h"


/** A single table symbol*/
struct symbol {
    /** Next symbol in table */
    symbolTable next;
    /** Address of the symbol */
    int address;
    /** name (symbol name) is a string (aka char*) */
    char *name;
    /** Symbol type */
    symbolType type;
};


int isLabel(char *name){
    if(name[strlen(name) -1] == ':'){
        return 1;
    }
    return 0;
}


/*Check length, first char is alpha and all the others are alphanumeric, and not assembly reserved identifier and string size is 30*/
int validLabelName(char *name) {

    int i = 0;

    if (isalpha(name[0]) && strlen(name) <= MAX_LENGTH && !(reservedWord(name))){
        for (i = 0; i < strlen(name) && name[i] != ':'; i++) {/*use loop to check isalnum if the word is alphanumeric*/
            if (!isalnum(name[i])) {
                return 0;
            }
        }

        return 1;
    }
    return 0;
}


void setType(symbolTable symbol,symbolType type){

    symbol->type = type;
}


void setAddress(symbolTable symbol, int address){

    symbol->address = address;
}


symbolTable findInTable(symbolTable symbol, char *name){
    if(symbol != NULL){
        if(strcmp(symbol->name, name) == 0){
            return symbol;
        }
        return findInTable(symbol->next, name);
    }
    return NULL;
}

symbolTable createSymbol(char* name,int address){

    symbolTable new_node = malloc(sizeof(struct symbol));

    new_node -> name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(new_node->name, name);
    new_node -> address = address;
    new_node -> next = NULL;
    new_node->type = 0;
    return new_node;

}

void shiftHead(symbolTable* head){
    symbolTable temp = *head;
    *head = (*head)->next;
    freeNode(temp);
}


void InsertSymbolNode(symbolTable* head, char *label, int address)
{

/* Allocate node*/

    symbolTable newNode = createSymbol(label,address);

    if (!(*head))

/* if the list is empty */

    {
        *head = newNode;

    }else{

/*Make next of new node as head*/

        newNode->next = (*head);

/*move the head to point to the new node*/

        (*head)  = newNode;
    }
}


int getAddress(symbolTable symbol){
    return symbol->address;
}

symbolType getType(symbolTable symbol){
    return symbol->type;
}


char *getSymbolName(symbolTable symbol){
    return symbol->name;
}


void updateDataSymbols(symbolTable table, int IC){

    while(table != NULL) {
        if (table->type == DATA_SYMBOL || table->type == STRUCT_SYMBOL) { /* if its a data instruction */
            table->address += IC;
        }
        table = table->next;
    }
}


void freeNode(symbolTable node){
    free(node->name);
    free(node);
}

void freeTable(symbolTable table) {
    symbolTable prevSymbol, currSymbol = table;
    while (currSymbol != NULL) {
        prevSymbol = currSymbol;
        currSymbol = currSymbol->next;
        freeNode(prevSymbol);
    }
}
