cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(MISC_SOURCES cross.cpp
                 messages.cpp
                 programs.cpp
                 setup.cpp
                 support.cpp)

set(MISC_HEADERS )

add_library(misc STATIC ${MISC_SOURCES} ${MISC_HEADERS})
