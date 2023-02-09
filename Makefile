CC = gcc
DIR = src
FILE = vm
DISTDIR = bin
L = c
CFLAGS = -Wall -std=c99 -Wno-sequence-point	 -Wno-unused-variable -Wno-unused-result -Wno-missing-field-initializers
DIST = out
ARGS = 

.SILENT:
build:
	mkdir -p $(DISTDIR)
	$(CC) $(CFLAGS) $(DIR)/$(FILE).$(L) -o $(DISTDIR)/$(FILE).$(DIST)
	$(DISTDIR)/$(FILE).$(DIST) $(ARGS)
	
clean:
	rm -rf ./$(DISTDIR)/*
