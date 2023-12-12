OBJS = \
	bin/syscall.o\
	bin/output.o\
	bin/memory.o

bin/syscall.o: src/syscall.s
	gcc -c src/syscall.s -o bin/syscall.o

bin/%.o: src/%.c
	gcc -c $< -I include/ -o $@

test/_test: test/test.c $(OBJS)
	gcc test/test.c $(OBJS) -I include/ -o test/_test

test: test/_test
	test/_test

clean:
	rm bin/*
	rm _*
