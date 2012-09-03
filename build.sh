#!/bin/sh -xe

clang -Wall -v -std=gnu99 -o src/gdb_breakpoint.o src/gdb_breakpoint.c -lbfd
clang -o gdb_breakpoint src/gdb_breakpoint.o -lbfd
