better_structs = bin/better_structs

CC=clang
CFLAGS=
LIB_FLAGS=

all: $(better_structs) lsp_client

$(better_structs): src/better_structs/*.c src/better_structs/*.h
	$(CC) $(CFLAGS) -Ithirdparty/metadesk/source src/better_structs/*.c -o $(better_structs) $(LIB_FLAGS)

lsp_client: $(better_structs) src/lsp_client/*.h src/lsp_client/*.metadesk
	$(better_structs) src/lsp_client/lsp_model.metadesk
