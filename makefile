OBJS = Assembler.o macro_table.o preassembler.o input_handler.o file_handler.o


Assembler: $(OBJS)
	gcc -g -ansi -Wall -pedantic $(OBJS) -o Assembler

macro_table.o: Utility/macro_table.c Utility/macro_table.h
	gcc -c -ansi -Wall -pedantic Utility/macro_table.c -o macro_table.o

preassembler.o: PreAssembler/preassembler.c PreAssembler/preassembler.h 
	gcc -c -ansi -Wall -pedantic PreAssembler/preassembler.c -o preassembler.o
	
input_handler.o: Utility/input_handler.c Utility/input_handler.h 
	gcc -c -ansi -Wall -pedantic Utility/input_handler.c -o input_handler.o

file_handler.o: Utility/file_handler.c Utility/file_handler.h 
	gcc -c -ansi -Wall -pedantic Utility/file_handler.c -o file_handler.o
Assembler.o: Assembler.c Assembler.h
	gcc -c -ansi -Wall -pedantic Assembler.c -o Assembler.o

clean:
	rm -f $(OBJS) *.am *.testam Assembler
