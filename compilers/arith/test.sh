#!/bin/bash

set -x

CC=clang++

# compile compiler
$CC arith.cc -o arith

# execute
./arith

# clean up
rm arith
