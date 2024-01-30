PREFIX = /home/$(shell whoami)
DEBUG  =  
#DEBUG  =  -g
#FLAGS  = -Wall 
FLAGS  = -Wall -O3 -DNDEBUG -DKV_FASTROUND 
INC    = -I. -I$(PREFIX)/kv/ 
RPATH  = -Wl,-R$(PREFIX)/pnl/lib
LIB    = -L/usr/lib64 -lm -lc
CC     = g++

#------------------------------------------------------------------------------
PROGRAM = BoxBB-1.1
default : $(PROGRAM)

#------------------------------------------------------------------------------
$(PROGRAM): $(PROGRAM).cpp makefile defines.h argshand.o getmem.o utils.o \
	iutils.o Functions.o box.o listbox.o btbox.o \
	InputOutput.o test.o defines.h
	$(CC) $(DEBUG) $(FLAGS) $(INC) \
	argshand.o getmem.o utils.o iutils.o Functions.o \
	box.o listbox.o btbox.o InputOutput.o test.o \
	$(RPATH) $(LIB) \
	-o $(PROGRAM) $(PROGRAM).cpp

test.o: test.cpp test.hpp
	$(CC) $(DEBUG) $(FLAGS) $(INC) -c -o test.o test.cpp    

InputOutput.o: InputOutput.cpp InputOutput.hpp
	$(CC) $(DEBUG) $(FLAGS) $(INC) -c -o InputOutput.o  InputOutput.cpp  
	
btbox.o : btbox.c btbox.h box.o
	$(CC) $(DEBUG) $(FLAGS) $(INC) -c -o btbox.o btbox.c	

listbox.o : listbox.c listbox.h box.o
	$(CC) $(DEBUG) $(FLAGS) $(INC) -c -o listbox.o listbox.c

box.o : box.cpp box.hpp
	$(CC) $(DEBUG) $(FLAGS) $(INC) -c -o box.o box.cpp

Functions.o: Functions.cpp Functions.hpp
	$(CC) $(DEBUG) $(FLAGS) $(INC) -c -o Functions.o  Functions.cpp  
	
iutils.o : iutils.cpp iutils.hpp 
	$(CC) $(DEBUG) $(FLAGS) $(INC) -c -o iutils.o iutils.cpp
		
utils.o : utils.c utils.h 
	$(CC) $(DEBUG) $(FLAGS) $(INC) -c -o utils.o utils.c

getmem.o : getmem.c getmem.h 
	$(CC) $(DEBUG) $(FLAGS) -c -o getmem.o getmem.c

argshand.o : argshand.c argshand.h 
	$(CC) $(DEBUG) $(FLAGS) -c -o argshand.o argshand.c
clean:
	@rm $(PROGRAM) *.o *.~ *.bck 2>/dev/null || true
