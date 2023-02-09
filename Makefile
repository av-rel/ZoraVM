CC = clang
DIR = src
FILE = vm
DISTDIR = bin
L = c
CFLAGS = -Wall -std=c99
DIST = out
ARGS = 

.SILENT:
build:
	mkdir -p $(DISTDIR)
	$(CC) $(CFLAGS) $(DIR)/$(FILE).$(L) -o $(DISTDIR)/$(FILE).$(DIST)
	
clean:
	rm -rf ./$(DISTDIR)/*
