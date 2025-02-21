#!/bin/bash

set -x

CC=clang++

# compile compiler
$CC arith.cc

# execute
./a.out "3"

# clean up
rm a.out
