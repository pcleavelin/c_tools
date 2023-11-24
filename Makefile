better_structs = bin/better_structs

CC=clang
CFLAGS=
LIB_FLAGS=

$(better_structs): src/better_structs/*.c src/better_structs/*.h
	$(CC) $(CFLAGS) -Ithirdparty/metadesk/source src/better_structs/*.c -o $(better_structs) $(LIB_FLAGS)

all: $(better_structs)
