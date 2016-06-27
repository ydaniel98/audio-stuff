#Include Directories
IDIR = ./include
# Compiler
CC = g++
# Compiler Flags
CFLAGS = -I $(IDIR) -std=c++11 -Wall
#Objects directory
ODIR = ./obj
#Libs directory
LDIR =
LIBS = -lm

#Dependencies
_DEPS = Wave.hpp Wave.inl
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

#Objects
_OBJ = WaveGraph.o Wave.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

wave_graph: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
