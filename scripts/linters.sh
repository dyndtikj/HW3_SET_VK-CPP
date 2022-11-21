#!/usr/bin/env bash

set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

function check_log() {
    LOG=$( { ${1}; } 2>&1 )
    STATUS=$?
    echo "$LOG"
    if echo "$LOG" | grep -q -E "${2}"
    then
        exit 1
    fi

    if [ $STATUS -ne 0 ]
    then
        exit $STATUS
    fi
}

print_header "RUN cpplint"
check_log "cpplint ./tests/*.cpp ./project/src/*.cpp" "Can't open for reading"

print_header "RUN cppcheck"
check_log "cppcheck  ./project/src/*.cpp --enable=all --inconclusive --error-exitcode=1 --suppress=missingIncludeSystem --suppress=unreadVariable --suppress=unreadVariable --suppress=unusedFunction --suppress=unmatchedSuppression" "\(information\)"

print_header "SUCCESS"

