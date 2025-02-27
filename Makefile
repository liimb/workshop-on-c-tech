clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

fmt_mac:
	find . -type f \( -name "*.c" -o -name "*.h" \) -print0 | xargs -0 clang-format -style=LLVM -i

#--- task6 singly linked list
singly_linked_list.o: singly_linked_list.c singly_linked_list.h
	gcc -g -c singly_linked_list.c -o singly_linked_list.o

singly_linked_list.a: singly_linked_list.o
	ar rc singly_linked_list.a singly_linked_list.o

singly_linked_list_test.o: singly_linked_list_test.c
	gcc -g -c singly_linked_list_test.c -o singly_linked_list_test.o

singly_linked_list_test: singly_linked_list_test.o singly_linked_list.a
	gcc -g -o singly_linked_list_test singly_linked_list_test.o singly_linked_list.a -lm
#---

test: singly_linked_list_test
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "Running $$test"; \
		./$$test || exit 1; \
	done
	