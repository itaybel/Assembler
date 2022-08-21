#ifndef REGISTERTABLE_H
#define REGISTERTABLE_H
#define NUM_OF_REGISTERS 7

/*
This function is checking if the received name of the registerTable is valid or not.
@param name - tha name of the registerTable
@return int - weather it found a register with that name
*/
int isRegisterName(char *name);



/*
This function receives the RegisterNumber and if the name of the register is valid it returns the registerNumber of the valid name.
@param name - tha name of the registerTable
@return int of the registerTable
*/
int getRegisterNum(char *name);

#endif
