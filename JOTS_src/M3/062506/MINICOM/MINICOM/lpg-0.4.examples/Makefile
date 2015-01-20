CC=gcc
LINK = $(CC)
CFLAGS = -O2 -pipe -m386 #-Wall 
LDFLAGS = -s

SRC = splay.c translate.c checklp.c miniterm.c type.c input.c calc.c \
	screen.c 

USEFUL_TARGETS = splay checklp miniterm
TARGETS = $(USEFUL_TARGETS) type input screen calc

all: $(TARGETS)
	@echo make done.

splay: splay.o translate.o
	$(LINK) splay.o translate.o $(LDFLAGS) -o $@

input: input.o
	$(LINK) input.o -lncurses $(LDFLAGS) -o $@

type: type.o
	$(LINK) type.o -lncurses $(LDFLAGS) -o $@

screen: screen.o
	$(LINK) screen.o -lncurses $(LDFLAGS) -o $@

calc: calc.o
	$(LINK) calc.o -lncurses $(LDFLAGS) -o $@

install:
	@echo usage: make install.all or install.bin or install.man

install.all: $(USEFUL_TARGETS) install.man install.bin

install.bin: $(USEFUL_TARGETS)
	install -m 555 $(USEFUL_TARGETS) /usr/local/bin

install.man:
	install -m 444 *.1 /usr/local/man/man1
	install -m 444 *.8 /usr/man/man8

clean:
	rm -f *.o core $(TARGETS)

depend:
	makedepend $(SRC)

ci:
	ci -m"I hate log messages!" -t-"I hate description prompts!" -l $(SRC) Makefile

co:
	co $(SRC) Makefile

.c.o: 
	$(CC) $(CFLAGS) -c $<

