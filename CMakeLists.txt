cmake_minimum_required(VERSION 3.30)
project(8bit_led C)

set(CMAKE_C_STANDARD 11)

add_executable(8bit_led main.c io.h)
