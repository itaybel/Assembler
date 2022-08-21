

OBJS = Assembler.o MacroTable.o  PreAssembler.o GeneralFunctions.o OperationTable.o RegisterTable.o AddressingMode.o AssemblySentence.o SymbolTable.o SecondPass.o

#OBJS = Assembler.o  GeneralFunctions.o OperationTable.o RegisterTable.o AddressingMode.o AssemblySentence.o SymbolTable.o SecondPass.o
ASSEMBLER_FILES = *.ob *.ext *.ent *.o
Assembler: $(OBJS)
	gcc -g -ansi -Wall -pedantic $(OBJS) -o Assembler


MacroTable.o: PreAssembler/MacroTable.c PreAssembler/MacroTable.h
	gcc -g -c -ansi -Wall -pedantic PreAssembler/MacroTable.c -o MacroTable.o

PreAssembler.o: PreAssembler/PreAssembler.c PreAssembler/PreAssembler.h 
	gcc -g -c -ansi -Wall -pedantic PreAssembler/PreAssembler.c -o PreAssembler.o
	

GeneralFunctions.o: Utility/GeneralFunctions.c Utility/GeneralFunctions.h 
	gcc -g -c -ansi -Wall -pedantic Utility/GeneralFunctions.c -o GeneralFunctions.o

	
OperationTable.o: OperationTable.c OperationTable.h
	gcc -g -c -ansi -Wall -pedantic OperationTable.c -o OperationTable.o
	
	
RegisterTable.o: RegisterTable.c RegisterTable.h
	gcc -g -c -ansi -Wall -pedantic RegisterTable.c -o RegisterTable.o
	
AddressingMode.o: AddressingMode.c AddressingMode.h
	gcc -g -c -ansi -Wall -pedantic AddressingMode.c -o AddressingMode.o	
	
AssemblySentence.o: AssemblySentence.c AssemblySentence.h
	gcc -g -c -ansi -Wall -pedantic AssemblySentence.c -o AssemblySentence.o
	
SymbolTable.o: SymbolTable.c SymbolTable.h
	gcc -g -c -ansi -Wall -pedantic SymbolTable.c -o SymbolTable.o
	

Assembler.o: Assembler.c 
	gcc -g -c -ansi -Wall -pedantic Assembler.c -o Assembler.o

SecondPass.o: SecondPass.c SecondPass.h
	gcc -g -c -ansi -Wall -pedantic SecondPass.c -o SecondPass.o	
clean:
	rm -f $(OBJS) $(ASSEMBLER_FILES) Assembler 		

	
