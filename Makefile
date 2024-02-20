CFLAGS ?= -pedantic -Wall -Wextra -Werror -Ofast -pipe -march=native -fno-stack-check -fno-asynchronous-unwind-tables -fno-ident -fno-stack-protector -ftree-vectorize -ffast-math -funswitch-loops -fuse-linker-plugin -flto -fno-plt -fno-semantic-interposition -falign-functions=64 -fgraphite-identity -floop-nest-optimize

all:
	gcc list.c main.c ${CFLAGS} -o list

clean:
	rm list
