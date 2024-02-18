#!/bin/sh
clear
echo "---- BUILDING ----"
make clean > /dev/null
make

echo
echo "---- TESTING ----"
binary/test
