#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include "SymbolTable.h"
#include "AddressingMode.h"



/*typedef struct symbolNode
{
    char* name;
    int address;
    char* def;


*//* symbol can be external,can be entry, .data, or command*//*
} SymbolNode;*/


static int IC,DC,L;


int validLabelName(char *name) {
    /*Check length, first char is alpha and all the others are alphanumeric, and not assembly reserved identifier and string size is 30*/
    int i = 0;

    if (name[0] && strlen(name) <= MAX_LENGTH && isalpha(name[0]) && reservedWord(name)) {
        while (name[i]) {/*use loop to check isalnum if the word is alphanumeric*/
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


void *checkMalloc(int size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        printf("Error: Fatal: Memory allocation failed.");
        exit(1);
    }
    return ptr;
}



void crateTable(char *key, int symbolAddress, symbolType type) {
    char *tempKey;
    symbolTable newSymbol;
    /* allocate memory for new symbol */
    newSymbol = (symbolTable) checkMalloc(sizeof(singleSymbol));
    /* Prevent "Aliasing" of pointers. when we free the list, we also free these allocated char ptrs */
    tempKey = (char *) checkMalloc(strlen(key) + 1);
    strcpy(tempKey, key);
    newSymbol->key = tempKey;
    newSymbol->address = symbolAddress;
    newSymbol->type = type;
}

void symbolHead(symbolTable *sym, int address){

    symbolTable prevSymbol, currSymbol, newSymbol = NULL;
    /* if the table's null, set the new symbol as the head. */
    if ((*sym) == NULL || (*sym)->address > address) {
        newSymbol->next = (*sym);
        (*sym) = newSymbol;
        return;
    }

    /* Insert the new symbol table, keeping it sorted */
    currSymbol = (*sym)->next;
    prevSymbol = *sym;
    while (currSymbol != NULL && currSymbol->address < address) {
        prevSymbol = currSymbol;
        currSymbol = currSymbol->next;
    }

    newSymbol->next = currSymbol;
    prevSymbol->next = newSymbol;
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

void addValueToType(symbolTable tab, int addAddress, symbolType type) {
    symbolTable currSymbol;
    /* for each entry, add address to_add if same type */
    for (currSymbol = tab; currSymbol != NULL; currSymbol = currSymbol->next) {
        if (currSymbol->type == type) {
            currSymbol->address += addAddress;
        }
    }
}

symbolTable filterTableByType(symbolTable table, symbolType type) {
    symbolTable newTable = NULL;
    /* For each symbol, check if he has the type. if so, insert to the new table. */
    do {
        if (table->type == type) {
            symbolHead(&newTable, table->address);
        }
    } while ((table = table->next) != NULL);
    return newTable; /* It holds a pointer to the first symbol, dynamically-allocated, so it's fine (not in stack) */
}

singleSymbol *findByTypes(symbolTable table, char *key, int symbolCount, ...) {
    int i;
    symbolType *validSymbolTypes = checkMalloc((symbolCount) * sizeof(int));
    /* Build a list of the valid types */
    va_list arglist;
    va_start(arglist, symbolCount);
    for (i = 0; i < symbolCount; i++) {
        validSymbolTypes[i] = va_arg(arglist, symbolType);
    }
    va_end(arglist);
    /* table null => nothing to dos */
    if (table == NULL) {
        free(validSymbolTypes);
        return NULL;
    }
    /* iterate over table and then over array of valid. if type is valid and same key, return the symbol. */
    do {
        for (i = 0; i < symbolCount; i++) {
            if (validSymbolTypes[i] == table->type && strcmp(key, table->key) == 0) {
                free(validSymbolTypes);
                return table;
            }
        }
    } while ((table = table->next) != NULL);
    /* not found, return NULL */
    free(validSymbolTypes);
    return NULL;
}
