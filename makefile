# directories
 
SDIR =
 
DDIR =
 
ODIR =
 
 
# other variables
 
EXE = $(shell basename `pwd`)
 
DEPS = $(wildcard $(DDIR)%*.h)
 
OBJS = $(patsubst $(SDIR)%.cpp,%.o,$(wildcard *.cpp))
 
 
CC = g++
 
CFLAGS =
 
LIBS =
 
RM = rm -rf
 
 
# make rules
 
$(EXE) : $(OBJS)
 
	g++ -o $@ $^ $(LIBS)
 
 
$(ODIR)%.o : $(SDIR)%.cpp
 
	$(CC) -c -o $@ $< $(CFLAGS)
 
 
$(OBJS) : $(DEPS)
 
 
.PHONY: clean
 
 
clean:
 
	$(RM) $(OBJS) $(EXE)
 
