CC = gcc
LINKER = gcc
CFLAGS = -std=c99 -Wall -Wpointer-arith -Wfatal-errors #-Werror
DEBUG = -g
PROG1LIBNAME = prog1
PROG1LIBDIR = ../prog1lib/lib
# disable default suffixes
.SUFFIXES:


# pattern rule for compiling .c-file to executable
#%.: %.c %.h
#	$(CC) $(CFLAGS) $(DEBUG)  $< -Lprog1lib/lib -lprog1 -iquoteprog1lib/lib -o $@ 

# pattern rule for compiling the library
prog1lib:
	cd $(PROG1LIBDIR) && make

%: %.c prog1lib
	$(CC) $(CFLAGS) $(DEBUG) $< -L$(PROG1LIBDIR) -l$(PROG1LIBNAME) -iquote$(PROG1LIBDIR) -o $@