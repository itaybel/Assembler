
#ifndef UNTITLED4_ASSEMBLYSENTENCE_H
#define UNTITLED4_ASSEMBLYSENTENCE_H

#include <stdio.h>
#include <string.h>
#include "SymbolTable.h"
#include "AddressingMode.h"
#include "Utility/GeneralFunctions.h"

#define ENTRY_INDEX 4
#define MAX_LINE_LENGTH 82
void throwError(char* errorMsg, int numberOfLine);

int foundCommendSentence(char* file_name);

int foundCommendSentence(char* file_name);

int foundEmptySentence(char* file_name);

int firstCharIsDot(char *line);

char* cutColonFromLabel(char *line, char *firstWord);

int doCommandSentence(char *subString, int *IC,int numberOfLine,symbolTable symbol);

int isNumber(char *number);

int doData(symbolTable table,char *line, int *DC,int numberOfLine,symbolTable symbol);

int doString(symbolTable table, char *command, int *DC, int numberOfLine, symbolTable symbol);

int doStruct(symbolTable table, char *command, int *DC, int numberOfLine, symbolTable symbol);

int doEntry(symbolTable table,char *label, int *DC,int numberOfLine,symbolTable symbol);

int doExtern(symbolTable table,char *label, int *DC,int numberOfLine, symbolTable symbol);


int getSpacesAtBegining(char* substring);

void throwError(char* errorMsg, int numberOfLine);

void validInstructions(symbolTable table,char *instruction,int *DC, int numberOfLine,symbolTable symbol);

void iCCounter(addressingMode address,addressingMode prevAddress, int *IC);
symbolTable createSymbolTable(char* fileName);
int encodeAssembly(char* fileName, symbolTable head);

#endif
