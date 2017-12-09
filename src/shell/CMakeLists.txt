cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(SHELL_SOURCES shell.cpp
                  shell_batch.cpp
                  shell_cmds.cpp
                  shell_misc.cpp)

set(SHELL_HEADERS )

add_library(shell STATIC ${SHELL_SOURCES} ${SHELL_HEADERS})
