#!/bin/bash

NAMES="$(find "./project" "./tests" | grep -E ".*(\.cpp|\.h|\.hpp|\.hh)$")"

echo -e "Files found to format = \n\"\"\"\n$NAMES\n\"\"\""

clang-format --verbose -i --style=file $NAMES