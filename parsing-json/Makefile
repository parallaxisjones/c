# the compiler to use
CC = clang

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

# files to link:
LFLAGS = -ljansson

# the names to use for both the target source files, and the output files:
TARGETS = donut

# jansson details
JANSSON_VERSION = 2.13.1
JANSSON_TAR = jansson-$(JANSSON_VERSION).tar.gz
JANSSON_DIR = jansson-$(JANSSON_VERSION)
JANSSON_URL = https://digip.org/jansson/releases/$(JANSSON_TAR)

all: $(TARGETS)

# Download and build jansson
jansson:
	@if [ ! -d "$(JANSSON_DIR)" ]; then \
		curl -LO $(JANSSON_URL); \
		tar -xzf $(JANSSON_TAR); \
		cd $(JANSSON_DIR); \
		./configure; \
		make; \
		sudo make install; \
	fi

donut: donut.c jansson
	$(CC) $(CFLAGS) -o donut donut.c $(LFLAGS)

clean:
	rm -f $(TARGETS)
