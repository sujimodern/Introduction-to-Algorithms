#!/bin/sh
in=$1
name="${in%.*}"
out="${name}.o"
clang -Wall -O0 -g -o "$out" "$in" && ./"$out"
