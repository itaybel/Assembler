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
typedef enum symbolType {
    CODE_SYMBOL,
    DATA_SYMBOL,
    EXTERNAL_SYMBOL,
    STRUCT_SYMBOL
} symbolType;

/** pointer to table symbol is just a table. */
typedef struct symbol* symbolTable;

/** A single table symbol*/
typedef struct symbol {
    /** Next symbol in table */
    symbolTable next;
    /** Address of the symbol */
    int address;
    /** Key (symbol name) is a string (aka char*) */
    char *key;
    /** Symbol type */
    symbolType type;
} singleSymbol;

/**
 * Adds an item to the table, keeping it sorted.
 * @param sym A pointer to the symbolTable
 * @param key The key of the symbol to insert
 * @param symbolAddress The address of the symbol to insert
 * @param type The type of the symbol to insert
 */
void crateTable(char *key, int symbolAddress, symbolType type);


/**
 * Adds symbol to head of the table.
 * @param sym The symbol
 * @param symbolAddress The address of the symbol
 */
void symbolHead(symbolTable *sym, int address);


/**
 * Deallocates all the memory required by the table.
 * @param table The table to deallocate
 */
void freeTable(symbolTable table);


/**
 * Adds the address of each symbol
 * @param tableAddress The table, containing the entries
 * @param addAddress The address to add
 * @param type The type of symbols to add the address to
 */
void addValueToType(symbolTable tableAddress, int addAddress, symbolType type);

/**
 * Returns all the symbols by their type in a new table
 * @param table The table
 * @param type The type to look for
 * @return A new table, which contains the symbols
 */
symbolTable filterTableByType(symbolTable table, symbolType type);

/**
 * Find symbol from the only specified types
 * @param table The table
 * @param key The key of the symbol
 * @param symbolCount The count of given types
 * @param ... The types to filter
 * @return The entry if found, NULL if not found
 */
singleSymbol *findByTypes(symbolTable table,char *key, int symbolCount, ...);

#endif

