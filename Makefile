.PHONY: all test clean check_fmt fmt

SUBDIRS = data_structures allocators gc

all:
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir; done

test:
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir test || exit 1; done

clean:
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir clean; done

check_fmt:
	find $(SUBDIRS) -type f \( -name "*.c" -o -name "*.h" \) -print0 \
	| xargs -0 clang-format -style=LLVM --dry-run --Werror

fmt:
	find $(SUBDIRS) -type f \( -name "*.c" -o -name "*.h" \) -print0 \
	| xargs -0 clang-format -style=LLVM -i
