#ifndef SECONDPASSH
#define SECONDPASSH
#define MAX_LINE_LENGTH 82


int encodeAssembly(char* fileName, symbolTable head);
void toBase32(int num, char *base);
int encodeData(symbolTable table, char* line , int* DC, int numberOfLine, FILE* obFile);
void writeToFile(char* content, FILE* file);
void handleInstructions(symbolTable table, char *instruction, int *DC, int numberOfLine, FILE* obFile);

#endif

