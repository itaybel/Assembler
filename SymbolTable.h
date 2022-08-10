/* Implements a dynamically-allocated symbol table */
#ifndef _TABLE_H
#define _TABLE_H
#define MAX_LENGTH 30



int validLabelName(char *name);


/**
 * Allocates memory in the required size. Exits the program if failed.
 * @param size The size to allocate in bytes
 * @return A generic pointer to the allocated memory if succeeded
 */
void *checkMalloc(int size);


/** A symbol type */
enum symbolType {
    CODE_SYMBOL,/* opertion_names and ect*/
    DATA_SYMBOL,/*string */
    EXTERNAL_SYMBOL, /*when we have instruction on extern*/
    STRUCT_SYMBOL /*when we have instruction on struct*/
} symbolType;

/** pointer to table symbol is just a table. */
typedef struct symbol* symbolTable;


int isLabel(char *name);






int compareSymbol(symbolTable symbol, char *key);


void setAddress(symbolTable symbol, int address);

void InsertSymbolNode(symbolTable* head_ref, char *label, int new_data);

int getAddress(symbolTable symbol);



char *getSymbol(symbolTable symbol);

symbolTable createSymbol(char* key,int address);


/**
 * Deallocates all the memory required by the table.
 * @param table The table to deallocate
 */
void freeTable(symbolTable table);

symbolTable findInTable(symbolTable symbol, char *key);

#endif
