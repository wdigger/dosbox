cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(INTS_SOURCES mouse.cpp
                 xms.cpp
                 ems.cpp
                 int10.cpp
                 int10.h
                 int10_char.cpp
                 int10_memory.cpp
                 int10_misc.cpp
                 int10_modes.cpp
                 int10_vesa.cpp
                 int10_pal.cpp
                 int10_put_pixel.cpp
                 int10_video_state.cpp
                 int10_vptable.cpp
                 bios.cpp
                 bios_disk.cpp
                 bios_keyboard.cpp)

set(INTS_HEADERS xms.h)

add_library(ints STATIC ${INTS_SOURCES} ${INTS_HEADERS})
