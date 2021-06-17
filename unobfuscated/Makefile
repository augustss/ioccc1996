CC=gcc
CFLAGS=-g
#CFLAGS=-Wall

all:	interp parse

interp:	interp.c dumpcode.c defs.h
	$(CC) $(CFLAGS) interp.c -o interp

parse: parse.c defs.h
	$(CC) $(CFLAGS) parse.c -o parse

# Run preprocessor on parse.c so it can compile itself.
parse.oc:	parse.c defs.h
	$(CC) -E -DSELF parse.c | sed -e '/^#/d' -e '/^$$/d' > parse.oc

test: parse interp parse.oc
	$(CC) fac.c -o fac
	# Run fac using cc
	./fac > fac.out.cc
	# Compile fac with OC compiler
	./parse < fac.c > fac.oo.1
	# Run bytecode for fac
	./interp < fac.oo.1 > fac.out.1
	# Compiler the compiler
	./parse < parse.oc > parse.oo
	# Run the compiler using the interpreter, compiling fac.c again
	cat parse.oo fac.c | ./interp > fac.oo.2
	# Run the bytecode for fac
	./interp < fac.oo.2 > fac.out.2
	# Check that the results match
	cmp fac.out.cc fac.out.1
	cmp fac.out.cc fac.out.2
	# Compile the compiler, using the bytecode version of the compiler.
	cat parse.oo parse.oc | ./interp > parse.oo.1
	# Check that the results match
	cmp parse.oo parse.oo.1

clean:
	rm -f parse interp parse.oc *.oo fac *.[12] fac.out.cc
