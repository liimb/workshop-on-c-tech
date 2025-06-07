objects = stack.o stack_test.o singly_linked_list.o singly_linked_list_test.o \
          integral_solver.o integral_solver_test.o \
          quadratic_solver.o quadratic_solver_test.o

tests = stack_test singly_linked_list_test integral_solver_test quadratic_solver_test

.PHONY: all clean test

all: $(tests)

%.o: %.c
	gcc -g -c $< -o $@

stack_test: stack_test.o stack.o
	gcc -g -o $@ $^ -lm

singly_linked_list_test: singly_linked_list_test.o singly_linked_list.o
	gcc -g -o $@ $^ -lm

integral_solver_test: integral_solver_test.o integral_solver.o
	gcc -g -o $@ $^ -lm

quadratic_solver_test: quadratic_solver_test.o quadratic_solver.o
	gcc -g -o $@ $^ -lm

clean:
	rm -f *.o $(tests)

test: all
	@for test in $(tests); do \
		echo "Running $$test"; \
		valgrind --leak-check=full --show-leak-kinds=all \
		         --track-origins=yes --error-exitcode=1 \
		         ./$$test || exit 1; \
		echo ""; \
	done

.PRECIOUS: %.o
