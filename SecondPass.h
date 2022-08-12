#ifndef SECONDPASSH
#define SECONDPASSH
#define MAX_LINE_LENGTH 82

void toBase32(unsigned int num, char *base);
int encodeAssembly(char* fileName, symbolTable head);
void writeToFile(char* content, FILE* file, int IC);

/* parsing instructions */
void encodeData(symbolTable table, char* line , int* IC, int numberOfLine, FILE* obFile);
void encodeString(symbolTable table, char* command , int* IC, int numberOfLine, FILE* obFile);
void encodeStruct(symbolTable table, char* command , int* IC, int numberOfLine, FILE* obFile);
int handleEntryAndExtern(char* firstWord, symbolTable table, int numberOfLine, FILE* entFile, FILE* extFile , int* isError);

/* parsing commands by number of operands */
int parseNoneOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* obFile) ;
int parseOneOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* obFile) ;
int parseTwoOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* obFile);

/* handling access methods */
int handleImmediateAddress(char* operand, int* IC, int numberOfLine, FILE* obFile);
int handleDirectAddress(symbolTable table, char* operand, int* IC, int numberOfLine, FILE* obFile);
int handleAddressAccess(symbolTable table, char* operand, int* IC, int numberOfLine, FILE* obFile);
int handleAccesses(addressingMode operandMode, symbolTable table, char* operand, int* IC, int numberOfLine, FILE* obFile);


void handleInstructions(symbolTable table, char *instruction, int *DC, int numberOfLine, FILE* obFile);
int parseCommandSentence(symbolTable table, char *command, int *IC,int numberOfLine, FILE* obFile);
void terminateSecondPhase(symbolTable table, FILE* inputFile, FILE* obFile,  FILE* entFIle,  FILE* extFile);


#endif

