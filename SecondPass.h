#ifndef SECONDPASSH
#define SECONDPASSH
#define MAX_LINE_LENGTH 82

#include "AssemblySentence.h"

/*
This function is used to write the final base32 string to the output file
@param content - the base32 string to write
@param file - the output file to write into
@param IC - the current IC
*/
void writeToFile(char* content, FILE* file, int IC);

/*
This function is used to convert a given number to base32
@param num  the number to be converted
@param base  a pointer to the string to write the base32 into
*/
void toBase32(int num, char *base);
int encodeAssembly(char* fileName, symbolTable table, flags* status);


/* parsing instructions */

/*
This function is used to encode data instructions
@param table the symbol table
@param IC a pointer to the IC
@param numberOfLine the current number of line proccesed in the input file
@param outFile the output file to write into
*/
void encodeData(symbolTable table, int* IC, int numberOfLine, FILE* obFile);

/*
This function is used to encode string instructions
@param table the symbol table
@param IC a pointer to the IC
@param numberOfLine the current number of line proccesed in the input file
@param outFile the output file to write into
*/
void encodeString(symbolTable table, int* IC, int numberOfLine, FILE* obFile);


/*
This function is used to encode struct instructions
@param table the symbol table
@param IC a pointer to the IC
@param numberOfLine the current number of line proccesed in the input file
@param outFile the output file to write into
*/
void encodeStruct(symbolTable table, int* IC, int numberOfLine, FILE* obFile);

/*
This function is used to handle entry and extern instructions
@param firstWord the first word which is seperated by a space in the line
@param table the symbol table
@param numberOfLine the current number of line proccesed in the input file
@param entFile the .ent file that we right our entities to
@param status a pointer to a struct which contains flags about the program
@return wether it found an extern/entity instruction
*/
int handleEntryAndExtern(char* firstWord, symbolTable table, int numberOfLine, FILE* entFile , flags* status);


/*
This function is used to encode struct instructions
@param table the symbol table
@param instruction the instruction of the line (.data/.string/.entity/.extern)
@param IC a pointer to the IC
@param numberOfLine the current number of line proccesed in the input file
@param outFile the .data file that we right our instructions into
*/
void handleInstructions(symbolTable table, char *instruction, int *IC, int numberOfLine, FILE* outFile);

/* parsing commands by number of operands */


/*
This function is used to encode a none operands command
@param table the symbol table
@param command the command to be encoded
@param IC a pointer to the IC
@param numberOfLine the current number of line proccesed in the input file
@param outFile the .cmd file that we right our commands into
*/
int encodeNoneOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* outFile) ;

/*
This function is used to encode a one operands command
@param table the symbol table
@param command the command to be encoded
@param IC a pointer to the IC
@param numberOfLine the current number of line proccesed in the input file
@param outFile the .cmd file that we right our commands into
@param extFile the .ext file that we right our externals into
*/
int encodeOneOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* outFile, FILE* extFile);


/*
This function is used to encode a two operands command
@param table the symbol table
@param command the command to be encoded
@param IC a pointer to the IC
@param numberOfLine the current number of line proccesed in the input file
@param outFile the .cmd file that we right our commands into
@param extFile the .ext file that we right our externals into
*/
int encodeTwoOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* outFile, FILE* extFile);

/* handling access methods */
int handleImmediateAddress(char* operand, int* IC, int numberOfLine, FILE* obFile);
int handleDirectAddress(symbolTable table, char* operand, int* IC, int numberOfLine, FILE* obFile, FILE* extFile);
int handleAddressAccess(symbolTable table, char* operand, int* IC, int numberOfLine, FILE* obFile);
int handleAccesses(addressingMode operandMode, symbolTable table, int isDest , char* operand, int* IC, int numberOfLine, FILE* outFile, FILE* extFile);

void openFiles(char* fileName, FILE** inputFile, FILE** cmdFile, FILE** dataFile, FILE** entFile, FILE** extFile, flags* status);


int encodeCommandSentence(symbolTable table, char *command, int *IC,int numberOfLine, FILE* obFile, FILE* extFile);
void terminateSecondPhase(char* fileName, symbolTable table, FILE* inputFile,  FILE* entFIle,  FILE* extFile);
void handleFinalOutputFiles(char* fileName, FILE* cmdFile, FILE* dataFile,  flags* status);

#endif

