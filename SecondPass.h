#ifndef SECONDPASSH
#define SECONDPASSH
#define MAX_LINE_LENGTH 82

#include "AssemblySentence.h"

void toBase32(int num, char *base);
int encodeAssembly(char* fileName, symbolTable table, flags* status);
void writeToFile(char* content, FILE* file, int IC);

/* parsing instructions */
void encodeData(symbolTable table, char* line , int* IC, int numberOfLine, FILE* obFile);
void encodeString(symbolTable table, char* command , int* IC, int numberOfLine, FILE* obFile);
void encodeStruct(symbolTable table, char* command , int* IC, int numberOfLine, FILE* obFile);
int handleEntryAndExtern(char* firstWord, symbolTable table, int numberOfLine, FILE* entFile , flags* flags);

/* parsing commands by number of operands */
int parseNoneOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* obFile) ;
int parseOneOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* obFile, FILE* extFile) ;
int parseTwoOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* obFile, FILE* extFile);

/* handling access methods */
int handleImmediateAddress(char* operand, int* IC, int numberOfLine, FILE* obFile);
int handleDirectAddress(symbolTable table, char* operand, int* IC, int numberOfLine, FILE* obFile, FILE* extFile);
int handleAddressAccess(symbolTable table, char* operand, int* IC, int numberOfLine, FILE* obFile);
int handleAccesses(addressingMode operandMode, symbolTable table, int isDest , char* operand, int* IC, int numberOfLine, FILE* outFile, FILE* extFile);

void openFiles(char* fileName, FILE** inputFile, FILE** cmdFile, FILE** dataFile, FILE** entFile, FILE** extFile, flags* status);

void handleInstructions(symbolTable table, char *instruction, int *DC, int numberOfLine, FILE* obFile);
int parseCommandSentence(symbolTable table, char *command, int *IC,int numberOfLine, FILE* obFile, FILE* extFile);
void terminateSecondPhase(char* fileName, symbolTable table, FILE* inputFile,  FILE* entFIle,  FILE* extFile);
void handleFinalOutputFiles(char* fileName, FILE* cmdFile, FILE* dataFile,  flags* status);

#endif

