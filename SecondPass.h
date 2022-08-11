#ifndef SECONDPASSH
#define SECONDPASSH
#define MAX_LINE_LENGTH 82

void toBase32(unsigned int num, char *base);
int encodeAssembly(char* fileName, symbolTable head);
void encodeData(symbolTable table, char* line , int* IC, int numberOfLine, FILE* obFile);
void writeToFile(char* content, FILE* file, int IC);
void handleInstructions(symbolTable table, char *instruction, int *DC, int numberOfLine, FILE* obFile);
int parseCommandSentence(symbolTable table, char *command, int *IC,int numberOfLine, FILE* obFile);
void terminateSecondPhase(symbolTable table, FILE* inputFile, FILE* obFile);
int parseNoneOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* obFile) ;
int parseOneOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* obFile) ;
int parseTwoOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* obFile);
#endif

