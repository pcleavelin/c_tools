all: source

CC=clang

source: list_symbols.c ../../src/file_io/file_io.c
	mkdir -p bin
	$(CC) -I../../src/ -I../../thirdparty ../../src/file_io/file_io.c list_symbols.c -o bin/list_symbols

