# Makefile for locality (Comp 40 Assignment 3)
#
# Includes build rules for a2test and ppmtrans.
#
# This Makefile is more verbose than necessary.  In each assignment
# we will simplify the Makefile using more powerful syntax and implicit rules.
#
# Last updated: February 16, 2016

# Authors: Liam Strand && Roger Burtonpatel
# Date: 2.24.2022
# Assignment: Arith

############## Variables ###############

CC = gcc # The compiler being used

# Updating include path to use Comp 40 .h files and CII interfaces
IFLAGS = -I/comp/40/build/include -I/usr/sup/cii40/include/cii

# Compile flags
# Set debugging information, allow the c99 standard,
# max out warnings, and use the updated include path
# CFLAGS = -g -std=c99 -Wall -Wextra -Werror -Wfatal-errors -pedantic $(IFLAGS)
#
# For this assignment, we have to change things a little.  We need
# to use the GNU 99 standard to get the right items in time.h for the
# the timing support to compile.
#
CFLAGS = -g -std=c99 -Wall -Wextra -pedantic $(IFLAGS)

# Linking flags
# Set debugging information and update linking path
# to include course binaries and CII implementations
LDFLAGS = -g -L/comp/40/build/lib -L/usr/sup/cii40/lib64

# Libraries needed for linking
# All programs cii40 (Hanson binaries) and *may* need -lm (math)
# arith40 is a catch-all for this assignment, netpbm is needed for pnm
# rt is for the "real time" timing library, which contains the clock support
LDLIBS = -larith40 -lbitpack -lpnm -lnetpbm -lcii40 -lm

# Collect all .h files in your directory.
# This way, you can never forget to add
# a local .h file in your dependencies.
#
# This bugs Mark, who dislikes false dependencies, but
# he agrees with Noah that you'll probably spend hours
# debugging if you forget to put .h files in your
# dependency list.
INCLUDES = $(shell echo *.h)

############### Rules ###############

all: 40image-6 ppmdiff


## Compile step (.c files -> .o files)

# To get *any* .o file, compile its .c file with the following rule.
%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@


## Making shared object files

# To get *any* .so file from a .c then to .so
%.so: %.c $(INCLUDES)
	$(CC) $(LDFLAGS) $(CFLAGS) -fPIC -shared -o $@ $^ $(LDLIBS)

## Linking step (.o -> executable program)

40image-6: compress40.o 40image.o a2plain.o uarray2.o colorspace.o pnmextend.o \
         chroma.o cosine.o quantize.o compIO.o codeword.o bitpack.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

ppmdiff: ppmdiff.o a2plain.o uarray2.o files.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# CXX = clang++

# ctests: my_c_file.o uarray2b.o uarray2.o
# 	$(CC) $(LDFLAGS) $^ $(LDLIBS)

# unit_test: unit_test_driver.o my_c_file.o uarray2b.o uarray2.o
# 	$(CXX) $(LDFLAGS) $^ $(LDLIBS)

### TESTING

# Test mains
testmain: testmain.o chroma.o cosine.o bitpack.o codeword.o a2plain.o \
		  uarray2.o compIO.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

shift-test: bitpack.o shift-test.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# Unit testing with python
test: bitpack.so all
	@echo -e "\n\n* * * * * * * * *\n* Begin " \
	"Testing *\n* * * * * * * * *\n\n"
	python test_arith.py
	python test_bitpack.py

check:
	wc -L *.h *.c README Makefile

clean:
	rm -f 40image-6 ppmdiff testmain shift-test *.o *.so
