#Include Directories
IDIR =
# Compiler
CC = g++
# Compiler Flags
CFLAGS = -std=c++11 -Wall
#Objects directory
ODIR = obj
#Libs directory
LDIR =
LIBS = -lm

#Dependencies
_DEPS =
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

#Objects
_OBJ = GraphData.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

graph_data: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
