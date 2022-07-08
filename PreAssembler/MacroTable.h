#ifndef MACRO_H
#define MACRO_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "../Utility/LinkedList.h"
#define MAX_LINE_LENGTH 80

typedef struct MacroNode
{
    char* name;
    char* content;
    int contentLength;
} MacroNode;

int compareMacro(void* macro, void* name);
MacroNode* createMacroNode();
#endif
