CC=gcc
CXX=g++
CFLAGS=-pedantic -O2
CXXFLAGS=$(CFLAGS)
LFLAGS=
OBJS=objs/brainfuck.o objs/functions.o

all: objs ./brainfuck

./brainfuck: $(OBJS)
	@echo "	LINK brainfuck"
	@$(CXX) $(LFLAGS) $(OBJS) -o ./brainfuck
	@echo "	`tput setaf 2``tput bold`COMPILATION SUCCESSFUL`tput sgr0`"

objs/brainfuck.o: src/brainfuck.cpp src/functions.hpp
	@echo "	CXX src/brainfuck.cpp"
	@$(CXX) $(CXXFLAGS) -c src/brainfuck.cpp -o $@

objs/functions.o: src/functions.cpp src/functions.hpp
	@echo "	CXX src/functions.cpp"
	@$(CXX) $(CXXFLAGS) -c src/functions.cpp -o $@




d: debug
debug: CFLAGS += -DDEBUG -g -O0
debug: CC=g++
debug: CXX=g++
debug: all

objs:
	@mkdir objs
clean_objs:
	@if [ "objs" != "." -a -d "objs" ]; then rm -r "objs"; fi
clean_bin:
	@rm -f ./brainfuck
c: clean
clean: clean_objs clean_bin
	@echo "	CLEAN"
f: fresh
fresh: clean
	@make all
r: run
run: all
	@././brainfuck

