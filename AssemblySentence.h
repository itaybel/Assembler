

#ifndef UNTITLED4_ASSEMBLYSENTENCE_H
#define UNTITLED4_ASSEMBLYSENTENCE_H

#include "SymbolTable.h"

#define MAX_LINE_LENGTH 80






int foundCommendSentence(char* file_name);

int foundEmptySentence(char* file_name);

int firstCharIsDot(char *line);

int doCommandSentence(char *line, int *IC);

char* cutColonFromLabel(char *line, char *firstWord);

int doData(symbolTable table,char *line, int *DC,int numberOfLine);

int doString(symbolTable table,char *line, int *DC,int numberOfLine);

int doStruct(symbolTable table,char *line, int *DC,int numberOfLine);

int doEntry(symbolTable table,char *line, int *DC,int numberOfLine);

int doExtern(symbolTable table,char *line, int *DC,int numberOfLine);

int crateSymbolTable(char* fileName);


#endif

