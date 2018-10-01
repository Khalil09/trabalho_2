IDIR = ../include
CC=gcc
CFLAGS=-I$(IDIR) -g -Wall


ODIR= obj
LDIR = ../lib


LIBS= -lm
_DEPS = minmax.h mancalaRules.h mancalaUI.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o minmax.o mancalaRules.o mancalaUI.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
