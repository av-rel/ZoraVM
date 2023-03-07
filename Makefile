CC = tcc
DIR = src
FILE = main
DISTDIR = bin
L = c
CFLAGS = -Wall -Wextra -Wpedantic -Werror
DIST = exe
ARGS = examples/hw.zsm

.SILENT:
build:
	mkdir -p $(DISTDIR)
	$(CC) $(CFLAGS) $(DIR)/$(FILE).$(L) -o $(DISTDIR)/$(FILE).$(DIST)
	$(DISTDIR)/$(FILE).$(DIST) $(ARGS)
	
clean:
	rm -rf ./$(DISTDIR)/*
