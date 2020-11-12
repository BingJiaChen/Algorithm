# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
OPTFLAGS = -O3


all	: bin/mps
	@echo -n ""

# optimized version
bin/mps	: max_ps.o main_opt.o
			$(CC) $(OPTFLAGS) max_ps.o main_opt.o -o bin/mps
main_opt.o 	   	: src/main.cpp src/maxPlanarSubset.h
			$(CC) $(CFLAGS) $< -o $@
max_ps.o	: src/maxPlanarSubset.cpp src/maxPlanarSubset.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

clean:
		rm -rf *.o bin/*