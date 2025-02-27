clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

fmt_mac:
	find . -type f \( -name "*.c" -o -name "*.h" \) -print0 | xargs -0 clang-format -style=LLVM -i

#--- task7 stack
stack.o: stack.c stack.h
	gcc -g -c stack.c -o stack.o

stack.a: stack.o
	ar rc stack.a stack.o

stack_test.o: stack_test.c
	gcc -g -c stack_test.c -o stack_test.o

stack_test: stack_test.o stack.a
	gcc -g -o stack_test stack_test.o stack.a -lm
#---

test: stack_test
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "Running $$test"; \
		./$$test || exit 1; \
	done
	