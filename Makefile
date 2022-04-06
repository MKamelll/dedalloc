FLAGS=-Wall -Wextra -pedantic

test: test.c
	mkdir -p build
	$(CC) ${FLAGS} -o build/$@ $^

