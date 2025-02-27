clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

fmt_mac:
	find . -type f \( -name "*.c" -o -name "*.h" \) -print0 | xargs -0 clang-format -style=LLVM -i

#--- task5 integral
integral_solver.o: integral_solver.c integral_solver.h
	gcc -g -c integral_solver.c -o integral_solver.o

integral_solver.a: integral_solver.o
	ar rc integral_solver.a integral_solver.o

integral_solver_test.o: integral_solver_test.c
	gcc -g -c integral_solver_test.c -o integral_solver_test.o

integral_solver_test: integral_solver_test.o integral_solver.a
	gcc -g -o integral_solver_test integral_solver_test.o integral_solver.a -lm
#---

test: integral_solver_test
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "Running $$test"; \
		./$$test || exit 1; \
	done
	