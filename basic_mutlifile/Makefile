# the compiler to use
CC = clang

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall
  
# files to link:
LFLAGS = #-lcs50
  
# the name to use for the output file:
TARGET = basic_pj
  
# the list of source files
SRCS = main.c file1.c file2.c
  
# the list of object files (derived from the source files)
OBJS = $(SRCS:.c=.o)
  
# installation directories
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

all: $(TARGET)
  
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LFLAGS)
  
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
  
install: $(TARGET)
	install -d $(BINDIR)
	install -m 755 $(TARGET) $(BINDIR)
  
clean:
	rm -f $(OBJS) $(TARGET)

uninstall:
	rm -f $(BINDIR)/$(TARGET)
