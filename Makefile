CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -std=c11 -lreadline
TARGETS = tosh siesta

# add to this list if you create new .c source files
TOSH_SRC = tosh.c parseargs.h

all: $(TARGETS)

ttsh: $(TOSH_SRC) parseargs.h
	$(CC) $(CFLAGS) -o $@ $(TOSH_SRC)

siesta: siesta.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(TARGETS)
