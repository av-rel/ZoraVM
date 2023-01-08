CC = gcc
ZVM-FL = zvm
DISTDIR = out
L = c
CFLAGS = -Wall
DIST = o

vm:
	$(CC) $(ZVM-FL).$(L) -o ./$(DISTDIR)/$(ZVM-FL).$(DIST) $(CFLAGS)
	./$(DISTDIR)/$(ZVM-FL).$(DIST)

d:
	$(CC) $(ZVM-FL).$(L) -o ./$(DISTDIR)/$(ZVM-FL).$(DIST)

build:
	$(CC) $(ZVM-FL).$(L) -o ./$(DISTDIR)/$(ZVM-FL).$(DIST) $(CFLAGS)

run:
	./$(DISTDIR)/$(ZVM-FL).$(DIST)
	
clean:
	rm -rf ./$(DISTDIR)/*