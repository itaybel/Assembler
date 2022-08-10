#ifndef SECONDPASSH
#define SECONDPASSH
#define MAX_LINE_LENGTH 82

void toBase32(int num, char *base);
int encodeAssembly(char* fileName, symbolTable head);
void encodeData(symbolTable table, char* line , int* IC, int numberOfLine, FILE* obFile);
void writeToFile(char* content, FILE* file, int IC);
void handleInstructions(symbolTable table, char *instruction, int *DC, int numberOfLine, FILE* obFile);
void parseCommandSentence(symbolTable table, char *command, int *IC,int numberOfLine);
#endif

