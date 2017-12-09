cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

#add_subdirectory(core_full)
#add_subdirectory(core_normal)
#add_subdirectory(core_dyn_x86)
#add_subdirectory(core_dynrec)

set(CPU_SOURCES callback.cpp
                cpu.cpp
                flags.cpp
                modrm.cpp
                core_full.cpp
                paging.cpp
                core_normal.cpp
                core_simple.cpp
                core_prefetch.cpp
                core_dyn_x86.cpp
                core_dynrec.cpp)

set(CPU_HEADERS modrm.h
                instructions.h
                lazyflags.h)

add_library(cpu STATIC ${CPU_SOURCES} ${CPU_HEADERS})
