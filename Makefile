clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

fmt_mac:
	find . -type f \( -name "*.c" -o -name "*.h" \) -print0 | xargs -0 clang-format -style=LLVM -i

#---# quadratic (task 4)
quadratic_solver.o: quadratic_solver.c quadratic_solver.h
	gcc -g -c quadratic_solver.c -o quadratic_solver.o

quadratic_solver.a: quadratic_solver.o
	ar rc quadratic_solver.a quadratic_solver.o

quadratic_solver_test.o: quadratic_solver_test.c quadratic_solver.h
	gcc -g -c quadratic_solver_test.c -o quadratic_solver_test.o

quadratic_solver_test: quadratic_solver_test.o quadratic_solver.a
	gcc -g -o quadratic_solver_test quadratic_solver_test.o quadratic_solver.a -lm
#---#

test: quadratic_solver_test
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "Running $$test"; \
		./$$test || exit 1; \
	done
	