# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c -std=c++11
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
OPTFLAGS = -O3


all	: bin/cb
	@echo -n ""

# optimized version
bin/cb	: cb_ps.o main_opt.o
			$(CC) $(OPTFLAGS) cb_ps.o main_opt.o -o bin/cb
main_opt.o 	   	: src/main.cpp src/cyclebreak.h
			$(CC) $(CFLAGS) $< -o $@
cb_ps.o	: src/cyclebreak.cpp src/cyclebreak.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

clean:
		rm -rf *.o bin/*