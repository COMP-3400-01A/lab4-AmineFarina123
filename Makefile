CFLAGS += -Wall -Wextra -Wfatal-errors -g3
CFLAGS += -Werror=vla -Werror=shadow -Wno-unused -Wno-unused-parameter
CFLAGS += -fsanitize=address -fsanitize=undefined

all: parta partb partc build

parta: parta.c
	$(CC) $(CFLAGS) -o parta parta.c

partb: partb.c
	$(CC) $(CFLAGS) -o partb partb.c

partc: partc.c
	$(CC) $(CFLAGS) -o partc partc.c

# the bats tests look for the binaries in ./build, so copy them there too
build: parta partb partc
	mkdir -p build
	cp parta partb partc build/

.PHONY: clean
clean:
	rm -rf parta partb partc build

