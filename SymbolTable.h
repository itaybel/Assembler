
#ifndef UNTITLED4_SYMBOLTABLE_H
#define UNTITLED4_SYMBOLTABLE_H
#include "LinkedList.h"
#define MAX_LENGTH 30

int validLabelName(char *name);

int compareSymbol(void* macro, void* name);
struct SymbolNode* createSymbolNode(char* name);
void freeNode(void* node);

#endif
