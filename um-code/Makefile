# Makefile
#
# Authors: Liam Strand and Matt Ung
# Date: April, 2022
# Assignment: um
#
# Includes build rules for um and tests

############## Variables ###############

CC = gcc # The compiler being used

# Updating include path to use Comp 40 .h files and CII interfaces
IFLAGS = -I/comp/40/build/include -I/usr/sup/cii40/include/cii

# Compile flags
# Set debugging information, allow the c99 standard,
# max out warnings, and use the updated include path
CFLAGS = -g3 -std=c99 -Wall -Wextra -Werror -Wfatal-errors -pedantic $(IFLAGS)

# Linking flags
# Set debugging information and update linking path
# to include course binaries and CII implementations
LDFLAGS = -g3 -L/comp/40/build/lib -L/usr/sup/cii40/lib64

# Libraries needed for linking
LDLIBS = -lbitpack -lcii40 -lm

# Collect all .h files in your directory.
# This way, you can never forget to add
# a local .h file in your dependencies.
#
# This bugs Mark, who dislikes false dependencies, but
# he agrees with Noah that you'll probably spend hours
# debugging if you forget to put .h files in your
# dependency list.
INCLUDES = $(shell echo *.h) 

############### Build ###############

all: um


## Compile step (.c files -> .o files)
# To get *any* .o file, compile its .c file with the following rule.
%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@


## Linking step (.o -> executable program)

um: main.o prepare.o um_state.o instructions.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)


############### Testing ###############

test: all
	@echo -e "\n* * * * * * * * *\n* Begin" \
	"Testing *\n* * * * * * * * *\n"
	@python testing/test_um.py

############### Utility ###############

test-clean:
	-rm -rf testing/output
	mkdir testing/output

check:
	-@grep -n --color=auto '.\{80\}' *.h *.c Makefile README

clean: test-clean
	-rm -f um *.o
