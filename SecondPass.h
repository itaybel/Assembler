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


/* parsing instructions */

/*
This function is used to encode data instructions
@param table the symbol table
@param IC a pointer to the IC
@param numberOfLine the current number of line processed in the input file
@param outFile the output file to write into
*/
void encodeData(symbolTable table, int* IC, int numberOfLine, FILE* obFile);

/*
This function is used to encode string instructions
@param table the symbol table
@param IC a pointer to the IC
@param numberOfLine the current number of line processed in the input file
@param outFile the output file to write into
*/
void encodeString(symbolTable table, int* IC, int numberOfLine, FILE* obFile);


/*
This function is used to encode struct instructions
@param table the symbol table
@param IC a pointer to the IC
@param numberOfLine the current number of line processed in the input file
@param outFile the output file to write into
*/
void encodeStruct(symbolTable table, int* IC, int numberOfLine, FILE* obFile);

/*
This function is used to handle entry and extern instructions
@param firstWord the first word which is seperated by a space in the line
@param table the symbol table
@param numberOfLine the current number of line processed in the input file
@param entFile the .ent file that we write our entities to
@param status a pointer to a struct which contains flags about the program
@return weather it found an extern/entity instruction
*/
int handleEntryAndExtern(char* firstWord, symbolTable table, int numberOfLine, FILE* entFile , flags* status);


/*
This function is used to encode struct instructions
@param table the symbol table
@param instruction the instruction of the line (.data/.string/.entity/.extern)
@param IC a pointer to the IC
@param numberOfLine the current number of line processed in the input file
@param outFile the .data file that we write our instructions into
*/
void handleInstructions(symbolTable table, char *instruction, int *IC, int numberOfLine, FILE* outFile);

/* parsing commands by number of operands */


/*
This function is used to encode a none operands command
@param table the symbol table
@param command the command to be encoded
@param IC a pointer to the IC
@param numberOfLine the current number of line processed in the input file
@param outFile the .cmd file that we write our commands into
*/
int encodeNoneOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* outFile) ;

/*
This function is used to encode a one operand command
@param table the symbol table
@param command the command to be encoded
@param IC a pointer to the IC
@param numberOfLine the current number of line processed in the input file
@param outFile the .cmd file that we write our commands into
@param extFile the .ext file that we write our externals into
*/
int encodeOneOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* outFile, FILE* extFile);


/*
This function is used to encode a two operands command
@param table the symbol table
@param command the command to be encoded
@param IC a pointer to the IC
@param numberOfLine the current number of line processed in the input file
@param outFile the .cmd file that we write our commands into
@param extFile the .ext file that we write our externals into
*/
int encodeTwoOperandsCommand(symbolTable table, char *command, int *IC,int numberOfLine, FILE* outFile, FILE* extFile);

/* handling access methods */


/*
This function is used to encode an operand with an immediate address
@param operand the operand to encode
@param IC a pointer to the IC
@param numberOfLine the current number of line processed in the input file
@param outFile the .cmd file that we write our commands into
*/
int handleImmediateAddress(char* operand, int* IC, int numberOfLine, FILE* outFile);


/*
This function is used to encode an operand with a direct address
@param table the symbol list
@param operand the operand to encode
@param IC a pointer to the IC
@param numberOfLine the current number of line processed in the input file
@param outFile the .cmd file that we write our commands into
@param extFile the .ext file that we write our externals into
*/
int handleDirectAddress(symbolTable table, char* operand, int* IC, int numberOfLine, FILE* outFile, FILE* extFile);

/*
This function is used to encode an operand with an address 
@param table the symbol list
@param operand the operand to encode
@param IC a pointer to the IC
@param numberOfLine the current number of line processed in the input file
@param outFile the .cmd file that we write our commands into
@param extFile the .ext file that we write our externals into
*/
int handleAddressAccess(symbolTable table, char* operand, int* IC, int numberOfLine, FILE* outFile ,FILE* extFile);

/*
This function is used to handle all the addressing accesses, and it calls the corresponding function
@param operandMode the addressing mode of the operand
@param table the symbol list
@param isDest weather the operand is a destination operand
@param IC a pointer to the IC
@param numberOfLine the current number of line processed in the input file
@param outFile the .cmd file that we write our commands into
@param extFile the .ext file that we write our externals into
*/
int handleAddressingAccesses(addressingMode operandMode, symbolTable table, int isDest , char* operand, int* IC, int numberOfLine, FILE* outFile, FILE* extFile);

/*
This function is the general function that handles command sentences
by calling the corresponding function to how many operands the command takes
@param table the symbol list
@param command the command we are encoding
@param IC a pointer to the IC
@param numberOfLine the current number of line processed in the input file
@param outFile the .cmd file that we write our commands into
@param extFile the .ext file that we write our externals into
*/
int encodeCommandSentence(symbolTable table, char *command, int *IC,int numberOfLine, FILE* obFile, FILE* extFile);

/*
This function terminates the second phase
it closes files, frees memory, and delete files
@param fileName the name of the file
@param table the symbol list
@param inputFile the am file we read and encode
@param entFile the .ent file we created to store our entities
@param extFile the .ext file we created to store out externals calls
@param cmdFile the .cmd file we created to store our commands encoding
@param dataFile the .data file we created to store out data encoding
*/
void terminateSecondPhase(char* fileName,symbolTable table, FILE* inputFile,  FILE* entFile,  FILE* extFile, FILE* cmdFile, FILE* dataFile);

/*
This function handles the final output files, by combining them into the .ob file
@param fileName the name of the file
@param cmdFile the .cmd file that stores all the commands
@param dataFile the .data file that stores all the data instructions
@param status a struct contains our flags
*/
void handleFinalOutputFiles(char* fileName, FILE* cmdFile, FILE* dataFile,  flags* status);


/*
This function opens all the files needed for the second phase
@param fileName the name of the file
@param inputFile a pointer to the input file
@param cmdFile a pointer to the .cmd file, which stores all the encoding for commands
@param dataFile a pointer to the .data file that stores all the data instructions
@param entFile a pointer to the .ent file, which stores all the entities 
@param extFile a pointer to the .ext file, which stores all the external calls
@param status a struct contains our flags
*/
void openFiles(char* fileName, FILE** inputFile, FILE** cmdFile, FILE** dataFile, FILE** entFile, FILE** extFile, flags* status);


/*
This function handles the encoding of the assembler
@param fileName the name of the input file
@param table the symbol list of the first iteration
@param status a struct contains our flags
*/
int encodeAssembly(char* fileName, symbolTable table, flags* status);

#endif
