cmake_minimum_required(VERSION 3.16)
project(huffman C)

set(CMAKE_C_STANDARD 11)

add_executable(huffman main.c huffman.c io.c arguments.c binary_heap.c btree.c btreenode.c frequency.c huffman_code.c huffman_code.h)