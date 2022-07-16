#ifndef UNTITLED4_OPERATIONTABLE_H
#define UNTITLED4_OPERATIONTABLE_H
#define NUM_OF_OPERATIONS 16
#define FIRST_ADDRESS 1
#define SECOND_ADDRESS 2
#define THIRD_ADDRESS 4
#define FOURTH_ADDRESS 8

/*
This function is checking if the received name of the operationTable is valid or not.
@param name - tha name of the operationTable
@return char name
*/
char* getOperationName(char *name);



/*
This function receives the operationName and if the name is valid it returns the Opcode of the valid name.
@param name - tha name of the operationTable
@return int of the Opcode
*/
int getOperationOpcode(char *name);



/*
This function receives the operationName and if the name is valid it returns the OperandNumber of the valid name.
@param name - tha name of the operationTable
@return int of the OperandNumber
*/
int getOperandNum(char *name);



/*
This function receives the operationName and if the name is valid it returns the sourceOperand of the valid name.
@param name - tha name of the operationTable
@param sourceOperand - the sourceOperand of the operationTable
@return int of the sourceOperand
*/
int getSourceOperand(char *name, int sourceOperand);



/*
This function receives the operationName and if the name is valid it returns the destinationOperand of the valid name.
@param name - tha name of the operationTable
@param destinationOperand - the destinationOperand of the operationTable
@return int of the destinationOperand
*/
int getDestinationOperand(char *name, int destinationOperand);


#endif
