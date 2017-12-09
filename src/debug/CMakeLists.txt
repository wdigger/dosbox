cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(DEBUG_SOURCES debug.cpp
                  debug_gui.cpp
                  debug_disasm.cpp
                  debug_win32.cpp)

set(DEBUG_HEADERS debug_inc.h
                  disasm_tables.h)

add_library(dbdebug STATIC ${DEBUG_SOURCES} ${DEBUG_HEADERS})
