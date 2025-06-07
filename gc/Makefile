.PHONY: all test clean

SRC = gc
TESTS = gc_test gc_ctor_dtor_test gc_cyclic_links_test

all: $(TESTS)

%.a: %.o
	ar rc $@ $^

%.o: %.c %.h
	gcc -g -I../allocators -c $< -o $@

%_test.o: %_test.c
	gcc -g -I../allocators -c $< -o $@

gc_test: gc_test.o gc.a ../allocators/pool_allocator.a
	gcc -g -o $@ $^ -lm

gc_ctor_dtor_test: gc_ctor_dtor_test.o gc.a ../allocators/pool_allocator.a
	gcc -g -o $@ $^ -lm

gc_cyclic_links_test: gc_cyclic_links_test.o gc.a ../allocators/pool_allocator.a
	gcc -g -o $@ $^ -lm

test: all
	@for t in $(TESTS); do echo "Running $$t"; valgrind --leak-check=full ./$$t || exit 1; echo ""; done

clean:
	rm -f *.o *.a *_test

.PRECIOUS: %.o
