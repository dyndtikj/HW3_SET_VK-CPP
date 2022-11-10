#!/usr/bin/env bash

TEST_FILES="./build/tests/tests"
chmod +x ${TEST_FILES}
VG_LOG="./build/valgrind.log"

NO_LOST_PATTERN="All heap blocks were freed -- no leaks are possible"
NO_ERROR_PATTERN="ERROR SUMMARY: 0 errors"

rm -f VG_LOG

valgrind --tool=memcheck --leak-check=summary --leak-check=full --track-origins=yes --log-file=${VG_LOG} ${TEST_FILES} || exit 1
NO_LOST=$(grep "${NO_LOST_PATTERN}" "${VG_LOG}")
NO_ERROR=$(grep "${NO_ERROR_PATTERN}" "${VG_LOG}")
if [ -z "${NO_LOST}" ] || [ -z "${NO_ERROR}" ]; then cat "${VG_LOG}"; exit 1; fi
echo " ***** SUCCESS MEMTEST *****"