/* Implements a dynamically-allocated symbol table */
#ifndef TABLE_H
#define TABLE_H
#define MAX_LENGTH 30


/** A symbol type */
typedef enum symbolType {
    CODE_SYMBOL,/* operation_names and ect*/
    DATA_SYMBOL,/*string */
    EXTERNAL_SYMBOL, /*when we have instruction on extern*/
    STRUCT_SYMBOL /*when we have instruction on struct*/
} symbolType;

/** pointer to table symbol is just a table. */
typedef struct symbol* symbolTable;

/*
This function checks if a given name ends with a ':'
@param name - the name of the symbol
@return 1 if there is  ":" at the end of the string, otherwise 0
*/
int isLabel(char *name);


/*
This function checks if a given symbol name is a valid one
it checks it according to what stated in the course booklet
@param name - the name of the symbol
@return 1 if the name is valid, otherwise 0
*/
int validLabelName(char *name);

/*
This function sets the type of given symbol
@param symbol - the symbol to change its type
@param type - the new type of the symbol
@return none
*/
void setType(symbolTable symbol,symbolType type);

/*
This function sets the address of a given symbol
@param symbol - the symbol to change its address
@param address - the new address of the symbol
@return none
*/
void setAddress(symbolTable symbol, int address);

/*
This function searches for a symbol with a specific name
@param symbol - the current symbol we check its name
@param name - the name we search
@return the found symbol with that name, or NULL if it wasn't found
*/
symbolTable findInTable(symbolTable symbol, char *name);

/*
This function creates a new symbol in the symbol list
@param name - the name of the new symbol
@param address - the address of the new symbol
@return the created symbol
*/
symbolTable createSymbol(char* name,int address);

/*
This function deletes the head of the linked list and changes its head
to be the next of the current head
@param head - a pointer to the head of the symbol table
@return none
*/
void shiftHead(symbolTable* head);

/*
This function inserts a new symbol to the beginning of the symbol table
@param head - a pointer to the head of the symbol table
@param label - the name of the symbol to be created
@param address - the address of the label to be created
@return none
*/
void InsertSymbolNode(symbolTable* head, char *label, int address);

/*
This function returns the address of a given symbol
@param symbol - the symbol to get its address
@return the address of the given symbol
*/
int getAddress(symbolTable symbol);

/*
This function returns the type of a given symbol
@param symbol - the symbol to get its type
@return the type of the given symbol
*/
symbolType getType(symbolTable symbol);

/*
This function returns the name of a given symbol
@param symbol - the symbol to get its name
@return the name of the given symbol
*/
char *getSymbolName(symbolTable symbol);

/*
This function updates the address to all the data symbols,
according to the given IC
@param table - the head of the symbolTable
@param IC - the instruction counter
@return none
*/
void updateDataSymbols(symbolTable table, int IC);

/**
This function frees a given node from the heap memory.
@param node a symbol node to be freed
@return none
*/
void freeNode(symbolTable node);


/**
 * Deallocates all the memory required by the table.
 * @param table The table to deallocate
 */
void freeTable(symbolTable table);


#endif
