# Makefile for MariaDB UDF with static linking to libxxhash

# Compiler and compiler flags
CC := gcc
CFLAGS := -Wall -O3 -shared -fPIC -Wl,--exclude-libs,ALL
INCLUDES := `mysql_config --cflags` `mysql_config --libs`
LDFLAGS := -l:libxxhash.a

# UDF source file
SOURCE := mariadb-xxhash.cc

# UDF shared library output file
OUTPUT := mariadb-xxhash.so

.DEFAULT_GOAL := $(OUTPUT)

LIB := $(OUTPUT)
TARGETDIR := /usr/lib/mysql/plugin

# Target to build the UDF
all: $(OUTPUT)

$(OUTPUT): $(SOURCE)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

install: $(OUTPUT)
	mkdir -p $(TARGETDIR)
	install -m644 $(LIB) $(TARGETDIR)

# Target to clean up generated files
clean:
	rm -f $(OUTPUT)

.PHONY: all clean
