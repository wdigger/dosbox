cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(FPU_SOURCES fpu.cpp)

set(FPU_HEADERS fpu_instructions.h
                fpu_instructions_x86.h)

add_library(fpu STATIC ${FPU_SOURCES} ${FPU_HEADERS})
