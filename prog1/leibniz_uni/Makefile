CC = gcc
LINKER = gcc
CFLAGS = -std=c99 -Wall -Werror -Wpointer-arith -Wfatal-errors
DEBUG = -g
PROG1LIBNAME = prog1
PROG1LIBDIR = ../prog1lib/lib

# disable default suffixes
.SUFFIXES:

# library
prog1lib:
	cd $(PROG1LIBDIR) && make

characters_test: characters_test.c fighter.c fighter.h wizard.c wizard.h character.h object_list.c object_list.h object.h
	$(CC) $(CFLAGS) $(DEBUG) -o characters_test characters_test.c fighter.c wizard.c object_list.c -L$(PROG1LIBDIR) -l$(PROG1LIBNAME) -lm -iquote$(PROG1LIBDIR)

integer_tree_test: integer_tree_test.c integer_tree.c integer_tree.h integer_list.c integer_list.h
	$(LINKER) $(CFLAGS) $(DEBUG) -o integer_tree_test integer_tree_test.c integer_tree.c integer_list.c -L$(PROG1LIBDIR) -l$(PROG1LIBNAME) -lm -iquote$(PROG1LIBDIR)
	
TOC: TOC.c TOC.h
	$(LINKER) $(CFLAGS) $(DEBUG) -o TOC TOC.c -L$(PROG1LIBDIR) -l$(PROG1LIBNAME) -lm -iquote$(PROG1LIBDIR)

# delete intermediary files
.PHONY: clean		# do not treat "clean" as a file name
clean:				# special target to remove files: make clean
	rm -f shapes_test integer_tree_test *.o
