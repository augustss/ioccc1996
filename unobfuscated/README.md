This is an implementation of a small subset of C.

Do `make test' to compile and test everything.

parse.c contains a compiler that emits byte code for
the C code it reads on stdin.

interp.c contains the interpreter for the byte code.

parse.c is written in the same subset of C that it can
compile.  interp.c is not, but with some minimal tweaking
it can be.

Share and enjoy
-- Lennart Augustsson
lennart@augustsson.net
