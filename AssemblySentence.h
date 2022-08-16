
#ifndef UNTITLED4_ASSEMBLYSENTENCE_H
#define UNTITLED4_ASSEMBLYSENTENCE_H

#include <stdio.h>
#include <string.h>
#include "SymbolTable.h"
#include "AddressingMode.h"
#include "Utility/GeneralFunctions.h"

#define ENTRY_INDEX 4
#define MAX_LINE_LENGTH 82

typedef struct flags {
    int error;
    int instructionError;
    int foundExtern;
    int foundEntry;
    int finalIC;
    int finalDC;
} flags;

void throwError(char* errorMsg, int numberOfLine);

int foundCommentSentence(char* file_name);

int foundEmptySentence(char* file_name);

int firstCharIsDot(char *line);

char* cutColonFromLabel(char *line, char *firstWord);
int checkValidOperand(char* operand,  int numberOfLine);
int handleCommandSentence(int operandNum , int* IC , int numberOfLine, char* firstOperand, char* secondOperand);

int isValidCommandSentence(int operandNum, char* restOfLine , int numberOfLine, char* firstOperand, char* secondOperand);
int doCommandSentence(char *subString, int *IC,int numberOfLine,symbolTable symbol);

int doData(symbolTable* table,char *line, int *DC,int numberOfLine,symbolTable symbol);

int doString(symbolTable* table,char *line, int *DC,int numberOfLine,symbolTable symbol);

int doStruct(symbolTable* table,char *line, int *DC,int numberOfLine,symbolTable symbol);

int doEntry(symbolTable* table,char *command, int *DC,int numberOfLine,symbolTable symbol);

int doExtern(symbolTable* table,char *command, int *DC,int numberOfLine, symbolTable symbol);


int validInstructions(symbolTable* table,char *instruction,int *DC, int numberOfLine,symbolTable symbol);

void iCCounter(addressingMode address,addressingMode prevAddress, int *IC);
symbolTable createSymbolTable(char* fileName, flags* status);


#endif
