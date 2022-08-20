#ifndef UNTITLED4_ASSEMBLYSENTENCE_H
#define UNTITLED4_ASSEMBLYSENTENCE_H

#include "SymbolTable.h"
#include "AddressingMode.h"

#define ENTRY_INDEX 4
#define MAX_LINE_LENGTH 82
#define TRUE 1
#define FALSE 0

typedef struct flags {
    int error;
    int instructionError;
    int foundExtern;
    int foundEntry;
    int finalIC;
    int finalDC;
} flags;




int foundCommentSentence(char* file_name);



/*
This function checks wether a given operand is valid
@param operand - the operand to check
@param numberOfLine - the current line proccesed in the input file
@return wether its valid or not
*/
int checkValidOperand(char* operand,  int numberOfLine);



/*
This function handles the validation of a command sentence
first of all , it fills the strings firstOperand&secondOperand with the operands, and returnes wether they are valid

@param operandNum - how much operands the command requires
@param restOfLine - a string represents all the remining line , without the command at the beginning
@param numberOfLine - the current line proccesed in the input file
@param firstOperand - a pointer to an empty string that represents the first operand
@param secondOperand - a pointer to an empty string that represents the second operand
@return wether the line is valid or not
*/
int isValidCommandSentence(int operandNum, char* restOfLine , int numberOfLine, char* firstOperand, char* secondOperand);


/*
This function takes care of the IC, and updates it as needed
@param command - the command of the command sentence
@param operandNum - how much operands the command requires
@param IC - a pointer to the IC
@param numberOfLine - the current line proccesed in the input file
@param firstOperand - a pointer to an empty string that represents the first operand
@param secondOperand - a pointer to an empty string that represents the second operand
@return wether it found any errors in the line
*/
int UpdateICforCommandSentence(char* command, int operandNum , int* IC , int numberOfLine, char* firstOperand, char* secondOperand);

/*
This function handles a command sentence, by checking its validation, and updates the IC, by calling the previous functions

@param command - the command of the command sentence (mov/sub...)
@param IC - a pointer to the IC
@param numberOfLine - the current line proccesed in the input file
@param symbol - the current built symbol table
@return wether it found any errors in the line
*/
int doCommandSentence(char *command, int *IC,int numberOfLine,symbolTable symbol);

int doData(symbolTable* table,char *line, int *DC,int numberOfLine,symbolTable symbol);

int doString(symbolTable* table,char *line, int *DC,int numberOfLine,symbolTable symbol);

int doStruct(symbolTable* table,char *line, int *DC,int numberOfLine,symbolTable symbol);

int doEntry(symbolTable* table,char *command, int *DC,int numberOfLine,symbolTable symbol);

int doExtern(symbolTable* table,char *command, int *DC,int numberOfLine, symbolTable symbol);


int validInstructions(symbolTable* table,char *instruction,int *DC, int numberOfLine,symbolTable symbol);

void iCCounter(addressingMode address,addressingMode prevAddress, int *IC);

/*
This function handles a label definition, and creates a new node in the symbol list

@param table a pointer to the symbol list
@param labelName the name of the label to be created
@param status a struct containing flags about the state of the program
@param IC a pointer to the IC
@param numberOfLine the current line proccesed in the input file
@return the new created symbol node (will be empty at this point, until changed later)
*/
symbolTable handleLabelDefinition(symbolTable* table,  char* labelName, flags* status, int IC, int numberOfLine);


symbolTable createSymbolTable(char* fileName, flags* status);


#endif
