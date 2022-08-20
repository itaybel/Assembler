/* Implements a dynamically-allocated symbol table */
#ifndef _TABLE_H
#define _TABLE_H
#define MAX_LENGTH 30



int validLabelName(char *name);


/** A symbol type */
typedef enum symbolType {
    CODE_SYMBOL,/* opertion_names and ect*/
    DATA_SYMBOL,/*string */
    EXTERNAL_SYMBOL, /*when we have instruction on extern*/
    STRUCT_SYMBOL /*when we have instruction on struct*/
} symbolType;

/** pointer to table symbol is just a table. */
typedef struct symbol* symbolTable;


int isLabel(char *name);






void setType(symbolTable symbol,symbolType type);

int compareSymbol(symbolTable symbol, char *name);
void freeNode(symbolTable node);

void setAddress(symbolTable symbol, int address);
symbolTable createSymbol(char* name,int address);
void InsertSymbolNode(symbolTable* head_ref, char *label, int new_data);

int getAddress(symbolTable symbol);

symbolType getType(symbolTable symbol);

char *getSymbol(symbolTable symbol);


void updateDataSymbols(symbolTable table, int IC);
/**
 * Deallocates all the memory required by the table.
 * @param table The table to deallocate
 */
void freeTable(symbolTable table);
void shiftHead(symbolTable* head);
symbolTable findInTable(symbolTable symbol, char *name);

#endif
