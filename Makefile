CFLAGS ?= -w -std=c99 -Ofast -pipe -march=native -fno-stack-check -fno-asynchronous-unwind-tables -fno-ident -fno-stack-protector -ftree-vectorize -ffast-math -funswitch-loops -fuse-linker-plugin -flto -fdevirtualize-at-ltrans -fno-plt -fno-semantic-interposition -falign-functions=64 -fgraphite-identity -floop-nest-optimize

all:
	gcc list.c ${CFLAGS} -o list

clean:
	rm list
