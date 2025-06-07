.PHONY: all test clean

SRCS = pool_allocator linear_allocator hash_table array_list
TESTS = $(SRCS:%=%_test)

all: $(TESTS)

hash_table.a: pool_allocator.a
array_list.a: linear_allocator.a

%.o: %.c %.h
	gcc -g -c $< -o $@

%.a: %.o
	ar rc $@ $^

%_test.o: %_test.c
	gcc -g -c $< -o $@

pool_allocator_test: pool_allocator_test.o pool_allocator.a
	gcc -g -o $@ $^ -lm

linear_allocator_test: linear_allocator_test.o linear_allocator.a
	gcc -g -o $@ $^ -lm

hash_table_test: hash_table_test.o hash_table.a pool_allocator.a
	gcc -g -o $@ $^ -lm

array_list_test: array_list_test.o array_list.a linear_allocator.a
	gcc -g -o $@ $^ -lm

test: all
	@for t in $(TESTS); do echo "Running $$t"; valgrind --leak-check=full ./$$t || exit 1; echo ""; done

clean:
	rm -f *.o *.a *_test

.PRECIOUS: %.o
