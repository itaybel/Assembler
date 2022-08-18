#ifndef MACRO_H
#define MACRO_H

typedef struct MNode* macroNode;



macroNode createMacroNode(char* name);

void InsertMacroNode(struct MNode** head_ref, struct MNode* new_node);

macroNode SearchNode(macroNode head, char *name);
void freeMacroList(macroNode node);

char* getName(struct MNode* node);

int getStartIndex(struct MNode* node);
int getLength(struct MNode* node);
void setStartIndex(struct MNode* node, int startIndex);
void setLength(struct MNode* node, int length);

#endif