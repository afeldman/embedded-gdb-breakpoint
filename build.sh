#!/bin/sh -xe

clang -Wall -v -std=gnu99 -o gdb_breakpoint src/gdb_breakpoint.c -lbfd

