#!/usr/bin/env bash
set -e
TESTS="build/tests/tests"

lcov -t tests -o ./build/tests/coverage_report.info -c -d ./build/tests
	genhtml -o ./build/tests/coverage_report ./build/tests/coverage_report.info
