

#ifndef UNTITLED4_ASSEMBLYSENTENCE_H
#define UNTITLED4_ASSEMBLYSENTENCE_H
#define MAX_LINE_LENGTH 80

 /*moves the index to the next place in string where the char isn't white */

#define NOT_WHITE_SPACES(string,index) \
for(;string[(index)] && (string[(index)] == "\t" || string[(index)] == ' '); (++(index)));



int foundCommandSentence(char* file_name);
int foundEmptySentence(char* file_name);

#endif

