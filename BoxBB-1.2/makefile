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
#------------------------------------------------------------------------------
LINK_TARGET = BoxBB-1.1
OBJS = \
	argshand.o \
	getmem.o \
	utils.o \
	iutils.o \
	Functions.o \
	Box.o \
	InputOutput.o \
	test.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)

default : $(LINK_TARGET)
all     : $(LINK_TARGET)

#------------------------------------------------------------------------------
$(LINK_TARGET) : %: %.cpp $(OBJS) makefile defines.h
	$(CC) $(DEBUG) $(FLAGS) $(INC) $(OBJS) $(RPATH) $(LIB) -o $@ $<

%.o : %.cpp %.hpp defines.h
	$(CC) $(DEBUG) $(FLAGS) $(INC) -o $@ -c $<

%.o : %.c %.h defines.h
	$(CC) $(DEBUG) $(FLAGS) $(INC) -o $@ -c $<

clean:
	@rm $(REBUILDABLES) *.o *~ *.bck 2>/dev/null || true
