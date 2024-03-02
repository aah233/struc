PREFIX=/home/$(shell whoami)
DEBUG  =  
FLAGS  = -Wall -DNDEBUG -DKV_FASTROUND 
INC    = -I. -I$(PREFIX)/kv
RPATH  = -Wl,-R$(PREFIX)/lib
LIB    = -L/usr/lib64 -L$(PREFIX)/lib -lm -lc
CC     = g++

#--------------------------------------------------------------------
LINK_TARGET =  Example-1.0
OBJS = \
	Box.o 

REBUILDABLES = $(OBJS) $(LINK_TARGET)

default : $(LINK_TARGET)
all     : $(LINK_TARGET)

#------------------------------------------------------------------------------
$(LINK_TARGET) : %: %.cpp $(OBJS) makefile 
	$(CC) $(DEBUG) $(FLAGS) $(INC) $(OBJS) $(RPATH) $(LIB) -o $@ $<

%.o : %.cpp %.hpp 
	$(CC) $(DEBUG) $(FLAGS) $(INC) -o $@ -c $<

clean:
	@rm $(REBUILDABLES) *~ *.bck 2>/dev/null || true
