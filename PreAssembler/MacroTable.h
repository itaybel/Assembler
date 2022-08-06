#ifndef MACRO_H
#define MACRO_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "../Utility/LinkedList.h"


typedef struct MacroNode
{
    char* name;
    int startIndex;
    int length;
} MacroNode;

int compareMacro(void* macro, void* name);
MacroNode* createMacroNode(char* name);
void freeNode(Node* node);
#endif
