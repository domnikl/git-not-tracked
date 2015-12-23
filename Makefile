PROG=git-not-tracked
CC=gcc
CFLAGS=-Llibs/libgit2/build -Wall $(shell pkg-config --cflags libgit2) -Wl,-t
LDFLAGS=$(shell pkg-config --libs libgit2)
OBJS=
PREFIX=/usr/local/bin

default: build

build: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS) $(LDFLAGS) $(PROG).c

.c.o:
	$(CC) -c $(CFLAGS) $(LDFLAGS) $<

checkleaks: clean $(PROG)
	valgrind --leak-check=full ./$(PROG) $(ARGS)

clean:
	rm -f *.o $(PROG)

debug: clean $(OBJS)
	$(CC) $(CFLAGS) -g -o $(PROG) $(OBJS) $(PROG).c $(LDFLAGS)
	gdb ./$(PROG)

install: $(PROG)
	cp $(PROG) $(PREFIX)/$(PROG)
