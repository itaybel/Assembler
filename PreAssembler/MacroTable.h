#ifndef MACRO_H
#define MACRO_H

typedef struct MNode* macroNode;


int compareMacro(void* macro, void* name);

macroNode createMacroNode(char* name);

void InsertMacroNode(struct MNode** head_ref, struct MNode* new_node);

macroNode SearchNode(macroNode head, char *name);
void freeMacroList(macroNode node);

#endif