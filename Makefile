CC=gcc
CXX=g++
CFLAGS=-pedantic -O2
CXXFLAGS=$(CFLAGS)
LFLAGS=
OBJS=objs/brainfuck.o 

all: objs ./brainfuck

debug: CFLAGS += -DDEBUG -g
debug: all

./brainfuck: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o ./brainfuck

objs/brainfuck.o: src/brainfuck.c
	$(CC) $(CFLAGS) -c src/brainfuck.c -o objs/brainfuck.o

objs:
	@mkdir objs
clean_objs:
	@if [ "objs" != "." -a -d "objs" ]; then rm -r "objs"; fi
clean_bin:
	@rm -f ./brainfuck
clean: clean_objs clean_bin
	@echo "\tCLEAN"
fresh: clean
	@make all
run: all
	@././brainfuck

