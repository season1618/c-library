bin/syscall.o: src/syscall.s
	gcc -c src/syscall.s -o bin/syscall.o

test/_test: test/test.c
	gcc test/test.c -I include/ -o test/_test

test: test/_test
	test/_test

clean:
	rm bin/*
	rm _*
