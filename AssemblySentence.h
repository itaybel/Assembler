#ifndef ASSEMBLYSENTENCE_H
#define ASSEMBLYSENTENCE_H

#include "SymbolTable.h"
#include "AddressingMode.h"

#define MAX_LINE_LENGTH 82
#define TRUE 1
#define FALSE 0



typedef struct flags {
    int error;
    int foundExtern;
    int foundEntry;
    int finalIC;
    int finalDC;
} flags;



/*
This function checks if a given line starts with a specific character
@param line - the line to be checked
@param c the character to check
@return weather the line starts with that character
*/
int checkFirstCharacter(char* line, char c);


/*
This function fix the data instruction by adding spaces after a "," to handle more errors with stroke.
@param line - the string to be fixed
@param parsedLine a pointer to the string which will contain the fixed line
*/
void fixDataInstruction(char *line, char parsedLine[MAX_LINE_LENGTH * 2]);


/*
This function handles a .data instruction, it handles errors,
and increases the DC accordingly to how many numbers specified
@param table the symbol list
@param line the current line
@param DC a pointer to the data counter
@param numberOfLine the number of the current line processed in the input file
@param symbol the created symbol of that instruction (it can be NULL)
@return 1 if an error occurred, 0 otherwise
*/
int doData(symbolTable* table,char *line, int *DC,int numberOfLine,symbolTable symbol);

/*
This function handles a .string instruction, it handles errors,
and increases the DC accordingly to how many numbers specified
@param table the symbol list
@param line the current line
@param DC a pointer to the data counter
@param numberOfLine the number of the current line processed in the input file
@param symbol the created symbol of that instruction (it can be NULL)
@return 1 if an error occurred, 0 otherwise
*/
int doString(symbolTable* table,char *line, int *DC,int numberOfLine,symbolTable symbol);

/*
This function handles a .struct instruction, it handles errors,
and increases the DC accordingly to how many numbers specified
@param table the symbol list
@param line the current line
@param DC a pointer to the data counter
@param numberOfLine the number of the current line processed in the input file
@param symbol the created symbol of that instruction (it can be NULL)
@return 1 if an error occurred, 0 otherwise
*/
int doStruct(symbolTable* table,char *line, int *DC,int numberOfLine,symbolTable symbol);

/*
This function handles a .entry instruction, by catching errors
@param table the symbol list
@param line the current line
@param DC a pointer to the data counter
@param numberOfLine the number of the current line processed in the input file
@param symbol the created symbol of that instruction (it needs to be NULL)
@return 1 if an error occurred, 0 otherwise
*/
int doEntry(symbolTable* table,char *command, int *DC,int numberOfLine,symbolTable symbol);

/*
This function handles a .extern instruction, by catching errors
@param table the symbol list
@param line the current line
@param DC a pointer to the data counter
@param numberOfLine the number of the current line processed in the input file
@param symbol the created symbol of that instruction (if it's not NULL, we just throw a warning)
@return 1 if an error occurred, 0 otherwise
*/
int doExtern(symbolTable* table,char *command, int *DC,int numberOfLine, symbolTable symbol);


/*
This function checks weather a given operand is valid
@param operand - the operand to check
@param numberOfLine - the current line processed in the input file
@return weather It's valid or not
*/
int checkValidOperand(char* operand,  int numberOfLine);



/*
This function handles the validation of a command sentence
first of all , it fills the strings firstOperand&secondOperand with the operands, and returns weather they are valid
@param operandNum - how much operands the command requires
@param restOfLine - a string represents all the reining line , without the command at the beginning
@param numberOfLine - the number of the current line processed in the input file
@param firstOperand - a pointer to an empty string that represents the first operand
@param secondOperand - a pointer to an empty string that represents the second operand
@return weather the line is valid or not
*/
int isValidCommandSentence(int operandNum, char* restOfLine , int numberOfLine, char* firstOperand, char* secondOperand);


/*
This function takes care of the IC, and updates it as needed
@param command - the command of the command sentence
@param operandNum - how much operands the command requires
@param IC - a pointer to the IC
@param numberOfLine - the number of the current line processed in the input file
@param firstOperand - a pointer to an empty string that represents the first operand
@param secondOperand - a pointer to an empty string that represents the second operand
@return weather it found any errors in the line
*/
int UpdateICforCommandSentence(char* command, int operandNum , int* IC , int numberOfLine, char* firstOperand, char* secondOperand);

/*
This function handles a command sentence, by checking its validation, and updates the IC, by calling the previous functions
@param command - the command of the command sentence (mov/sub...)
@param IC - a pointer to the IC
@param numberOfLine - the number current line processed in the input file
@param symbol - the symbol created in the line
@return weather it found any errors in the line
*/
int doCommandSentence(char *command, int *IC,int numberOfLine,symbolTable symbol);



/*
This function checks if a instruction sentence is valid, it checks for errors
and updates the DC as needed
@param table - a pointer to the symbol list
@param instruction - the instruction we got in the line (.data/.string etc)
@param DC - a pointer to the DC
@param numberOfLine - the number of the current line processed in the input file
@param symbol - the current built symbol table
@return 0 if any errors were found, 1 otherwise
*/
int validInstructions(symbolTable* table,char *instruction,int *DC, int numberOfLine,symbolTable symbol);

/*
This function updates the IC according to the addressing modes of the operands
@param address the of the second operand
@param prevAddress the address of the first operand
@param IC a pointer to the IC
@return none
*/
void iCCounter(addressingMode address,addressingMode prevAddress, int *IC);

/*
This function handles a label definition, and creates a new node in the symbol list
@param table a pointer to the symbol list
@param labelName the name of the label to be created
@param status a struct containing flags about the state of the program
@param IC a pointer to the IC
@param numberOfLine the number of the current line processed in the input file
@return the new created symbol node (will be empty at this point, until changed later)
*/
symbolTable handleLabelDefinition(symbolTable* table,  char* labelName, flags* status, int IC, int numberOfLine);

/*
This function is the main function in this file
this is the function which reads the am file, and calls all the other functions
at the end, it will create a symbol table, and return errors if found.
@param fileName the name of the file to be assembled
@param status a pointer to the flags struct
@return symbolTable the created symbol table, NULL if error occurred
*/
symbolTable createSymbolTable(char* fileName, flags* status);


#endif
