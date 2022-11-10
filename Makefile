DEMO_DIR = build/hw3_set_main
TESTS_DIR = build/tests/tests
.PHONY: all build rebuild check test coverage clean linters valgrind

all: clean format linters build test run

build: clean
	scripts/build.sh

test:
	scripts/build.sh -DBUILD_TESTS=ON
	./${TESTS_DIR}

rebuild: clean build

run: build
	./${DEMO_DIR}

coverage:
	scripts/coverage.sh ./${TESTS_DIR}

format:
	scripts/format.sh

valgrind:
	scripts/valgrind.sh ${TESTS_DIR}

linters:
	scripts/linters.sh

clean:
	rm -rf build/