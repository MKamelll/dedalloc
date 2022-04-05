FLAGS=-Wall -Wextra -pedantic

dedalloc: dedalloc.c
	mkdir -p build
	$(CC) ${FLAGS} -o build/$@ $^

