all: structs source

CC=clang

structs: lsp_model.metadesk
	../../bin/better_structs lsp_model.metadesk

source: list_symbols.c
	mkdir -p bin
	$(CC) -I../../src/ -I../../thirdparty list_symbols.c -o bin/list_symbols

