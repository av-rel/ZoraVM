CC = tcc
DIR = src
FILE = main
DISTDIR = bin
L = c
CFLAGS = -Wall -std=c99 -pedantic -g
DIST = exe
ARGS = 

.SILENT:
build:
	mkdir -p $(DISTDIR)
	$(CC) $(CFLAGS) $(DIR)/$(FILE).$(L) -o $(DISTDIR)/$(FILE).$(DIST)
	$(DISTDIR)/$(FILE).$(DIST) $(ARGS)
	
clean:
	rm -rf ./$(DISTDIR)/*
