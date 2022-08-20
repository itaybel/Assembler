#ifndef MACRO_H
#define MACRO_H

typedef struct MNode* macroNode;
#define MAX_LENGTH 30

/*
This function is used to allocate memory and create a new macro node
@param name - the name of the macro
@return a pointer to the new empty macro
*/
macroNode createMacroNode(char* name);


/*
This function is used insert a new macro to the macro list
@param head the current head of the linked list
@param newNode the new node to be inserted 
*/
void InsertMacroNode(struct MNode** head, struct MNode* newNode);

/*
This function is used to search for a specific macro in a linked list
@param head the current head of the linked list
@param name the name to search
@return the found node, NULL if it couldn't be found
*/
macroNode SearchNode(macroNode head, char *name);


/*
This function is used to free the macro list
@param head the current node in the linked list
@return none
*/
void freeMacroList(macroNode node);

/*
This function checks if a macro name is valid
@param name the name of the macro
@return wether its valid or not
*/
int isValidMacroName(char* name);

/*
This function is used to get the name of a macro node
@param node the node to return its name
@return the name of the macro
*/
char* getName(struct MNode* node);

/*
This function is used to get the start index of a macro 
@param node the node to return its start index
@return the start index of the macro
*/
int getStartIndex(struct MNode* node);

/*
This function is used to get the length of a macro 
@param node the node to return its length
@return the length of the macro
*/
int getLength(struct MNode* node);

/*
This function is used to set the length of a macro 
@param node the node to set its length
@param startIndex the new start index of the macro
*/
void setStartIndex(struct MNode* node, int startIndex);

/*
This function is used to set the length of a macro 
@param node the node to set its length
@param length the new length of the macro
*/
void setLength(struct MNode* node, int length);

#endif