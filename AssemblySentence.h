

#ifndef UNTITLED4_ASSEMBLYSENTENCE_H
#define UNTITLED4_ASSEMBLYSENTENCE_H

#include "SymbolTable.h"
#include "AddressingMode.h"

void throwError(char* errorMsg, int numberOfLine);

int foundCommendSentence(char* file_name);

int foundEmptySentence(char* file_name);

int firstCharIsDot(char *line);

char* cutColonFromLabel(char *line, char *firstWord);

int doCommandSentence(char *subString, int *IC,int numberOfLine,symbolTable symbol);

int doData(symbolTable table,char *line, int *DC,int numberOfLine,symbolTable symbol);

int doString(symbolTable table,char *line, int *DC,int numberOfLine,symbolTable symbol);

int doStruct(symbolTable table,char *line, int *DC,int numberOfLine,symbolTable symbol);

int doEntry(symbolTable table,char *label, int *DC,int numberOfLine,symbolTable symbol);

int doExtern(symbolTable table,char *label, int *DC,int numberOfLine, symbolTable symbol);

void iCCounter(addressingMode address,addressingMode prevAddress, int *IC);

void validInstructions(symbolTable table,char *instruction,int *DC, int numberOfLine,symbolTable symbol);

int crateSymbolTable(char* fileName);


#endif

