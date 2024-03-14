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
	iutils.o Functions.o \
	InputOutput.o Box.o test.o defines.h
	$(CC) $(DEBUG) $(FLAGS) $(INC) \
	argshand.o getmem.o utils.o iutils.o Functions.o \
	 Box.o InputOutput.o  \
	$(RPATH) $(LIB) \
	-o $(PROGRAM) $(PROGRAM).cpp
  

InputOutput.o: InputOutput.cpp InputOutput.hpp
	$(CC) $(DEBUG) $(FLAGS) $(INC) -c -o InputOutput.o  InputOutput.cpp  	

Box.o: Box.cpp Box.hpp
	$(CC) $(DEBUG) $(FLAGS) $(INC) -c -o Box.o  Box.cpp

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
