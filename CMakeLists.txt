cmake_minimum_required(VERSION 3.16)
project(huffman C)

set(CMAKE_C_STANDARD 99)

add_executable(huffman main.c huffman.c io.c)