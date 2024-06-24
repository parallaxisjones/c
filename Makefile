# the compiler to use
CC = clang

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall
  
# files to link:
LFLAGS = #-lcs50
  
# the names to use for both the target source files, and the output files:
TARGETS = donut
  
all: $(TARGETS)
  
donut: donut.c
	$(CC) $(CFLAGS) -o donut donut.c $(LFLAGS)

# ch3: ch3.c
# 	$(CC) $(CFLAGS) -o ch3 ch3.c $(LFLAGS)

clean:
	rm -f $(TARGETS)

