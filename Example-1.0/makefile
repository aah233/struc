PREFIX=/home/$(shell whoami)/cxsc
DEBUG  =  
FLAGS  = -Wall -march=x86-64 -mfpmath=sse -msse2 
#Para evitar warnnings de deprecated in C++11
INC    = -I. -isystem$(PREFIX)/include
RPATH  = -Wl,-R$(PREFIX)/lib
LIB    = -L/usr/lib64 -L$(PREFIX)/lib -lcxsc -lm
CC     = g++

#--------------------------------------------------------------------
PROGRAM = Example-1.0
default : $(PROGRAM)

#--------------------------------------------------------------------
Example-1.0: $(PROGRAM).cpp makefile Problems.o Box.o
	$(CC) $(PROGRAM).cpp -o $(PROGRAM) $(DEBUG) $(FLAGS) $(INC) \
	Problems.o Box.o $(RPATH) $(LIB)
	
Problems.o: Problems.cpp Problems.hpp 
	$(CC) Problems.cpp -c -o Problems.o  $(DEBUG) $(FLAGS) $(INC) 
		
Box.o: Box.cpp Box.hpp 
	$(CC) Box.cpp -c -o Box.o  $(DEBUG) $(FLAGS) $(INC)

clean:
	@rm $(PROGRAM) *.o *.~ *.bck 2>/dev/null || true
