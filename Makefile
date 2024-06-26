.PHONY: all clean
MAKEFLAGS+=-j

CC=gcc
CFLAGS=-std=c23 -g -Wall -Wextra
LDFLAGS=-L./lib
LDLIBS=-lm -lraylib

INCDIR=./include
SRCDIR=./src
OBJDIR=./obj
BINDIR=.

INC=$(wildcard $(INCDIR)/*.h) $(wildcard $(INCDIR)/*.h)
SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
BIN=$(BINDIR)/flip

all: $(BIN)

$(BIN): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ -c $<

clean:
	rm -f $(OBJ) $(BIN)
