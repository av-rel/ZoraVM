CC = gcc
ZVM-FL = main
DISTDIR = out
L = c
CFLAGS = -Wall -std=c99 -g -O0
DIST = o
ARGS = examples/basic.zasm

vm:
	$(CC) $(ZVM-FL).$(L) -o ./$(DISTDIR)/$(ZVM-FL).$(DIST) $(CFLAGS)
	./$(DISTDIR)/$(ZVM-FL).$(DIST) $(ARGS)

d:
	$(CC) $(ZVM-FL).$(L) -o ./$(DISTDIR)/$(ZVM-FL).$(DIST)

build:
	$(CC) $(ZVM-FL).$(L) -o ./$(DISTDIR)/$(ZVM-FL).$(DIST) $(CFLAGS)

run:
	./$(DISTDIR)/$(ZVM-FL).$(DIST)
	
clean:
	rm -rf ./$(DISTDIR)/*