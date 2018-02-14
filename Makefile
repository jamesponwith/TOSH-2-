CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -std=c11 -lreadline
TARGETS = tosh siesta

# add to this list if you create new .c source files
TOSH_SRC = tosh.c parse_args.c

all: $(TARGETS)

ttsh: $(TOSH_SRC) parse_args.o
	$(CC) $(CFLAGS) -o $@ $(TOSH_SRC) parse_args.o

siesta: siesta.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(TARGETS)
