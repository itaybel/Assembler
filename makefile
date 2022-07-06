OBJS = Assembler.o MacroTable.o PreAssembler.o InputHandler.o FileHandler.o


Assembler: $(OBJS)
	gcc -g -ansi -Wall -pedantic $(OBJS) -o Assembler

MacroTable.o: Utility/MacroTable.c Utility/MacroTable.h
	gcc -c -ansi -Wall -pedantic Utility/MacroTable.c -o MacroTable.o

PreAssembler.o: PreAssembler/PreAssembler.c PreAssembler/PreAssembler.h 
	gcc -c -ansi -Wall -pedantic PreAssembler/PreAssembler.c -o PreAssembler.o
	
InputHandler.o: Utility/InputHandler.c Utility/InputHandler.h 
	gcc -c -ansi -Wall -pedantic Utility/InputHandler.c -o InputHandler.o

FileHandler.o: Utility/FileHandler.c Utility/FileHandler.h 
	gcc -c -ansi -Wall -pedantic Utility/FileHandler.c -o FileHandler.o
Assembler.o: Assembler.c Assembler.h
	gcc -c -ansi -Wall -pedantic Assembler.c -o Assembler.o

clean:
	rm -f $(OBJS) *.am *.testam Assembler
