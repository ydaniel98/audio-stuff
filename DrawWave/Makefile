#Include Directories
IDIR =../Commun
# Compiler
CC = g++
# Compiler Flags
CFLAGS = -I $(IDIR) -std=c++11 -Wall
#Objects directory
ODIR = obj
#Libs directory
LDIR =
LIBS = -lm

#Dependencies
_DEPS =
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

#Objects
_OBJ = DrawWave.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

draw_wave: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
