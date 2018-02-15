CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -std=c11 -lreadline -D_GNU_SOURCE
TARGETS = tosh siesta

# add to this list if you create new .c source files
TOSH_SRC = history_queue.c parse_args.c tosh.c wrappers.c

all: $(TARGETS)

tosh: $(TOSH_SRC) history_queue.h parse_args.h
	$(CC) $(CFLAGS) -o $@ $(TOSH_SRC)   

siesta: siesta.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(TARGETS)
