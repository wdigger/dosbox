cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(DOSBox)
set(PROJECT_VERSION "0.75")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32" CACHE STRING "c++ flags")
#set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -m32" CACHE STRING "c flags")

find_package(SDL REQUIRED)
find_package(Curses REQUIRED)

include(CheckIncludeFiles)

check_include_files(inttypes.h HAVE_INTTYPES_H)
#check_include_files(inttypes.h HAVE_LIBASOUND)
check_include_files(memory.h HAVE_MEMORY_H)
check_include_files(stdint.h HAVE_STDINT_H)
check_include_files(stdlib.h HAVE_STDLIB_H)
check_include_files(string.h HAVE_STRING_H)
check_include_files(strings.h HAVE_STRINGS_H)
check_include_files(sys/socket.h HAVE_SYS_SOCKET_H)
check_include_files(sys/stat.h HAVE_SYS_STAT_H)
check_include_files(sys/types.h HAVE_SYS_TYPES_H)
check_include_files(unistd.h HAVE_UNISTD_H)
check_include_files(pwd.h HAVE_PWD_H)
check_include_files(netinet/in.h HAVE_NETINET_IN_H)

include(CheckTypeSize)

check_type_size("unsigned char" SIZEOF_UNSIGNED_CHAR)
check_type_size("unsigned short" SIZEOF_UNSIGNED_SHORT)
check_type_size("unsigned int" SIZEOF_UNSIGNED_INT)
check_type_size("unsigned long" SIZEOF_UNSIGNED_LONG)
check_type_size("unsigned long long" SIZEOF_UNSIGNED_LONG_LONG)
check_type_size("int*" SIZEOF_INT_P)

option(ENABLE_DEBUG "Enable debugging" OFF)
if(ENABLE_DEBUG)
  set(C_DEBUG 1)
else()
  set(C_DEBUG 0)
endif()

set(C_ATTRIBUTE_ALWAYS_INLINE 1)
set(C_DIRECTSERIAL 1)
set(C_DYNREC 1)
set(C_FPU 1)
set(C_FPU_X86 1)
set(C_HAS_ATTRIBUTE 1)
set(C_HAS_BUILTIN_EXPECT 1)
set(C_HAVE_MPROTECT 1)
set(C_OPENGL 0)
set(C_TARGETCPU "X86_64")
set(C_UNALIGNED_MEMORY 1)
set(VERSION GIT)

if(APPLE)
  set(MACOSX 1)
  find_library(CORE_MIDI_LIBRARY CoreMIDI)
  find_library(AUDIO_TOOLBOX_LIBRARY AudioToolbox)
elseif(UNIX)
  set(LINUX 1)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake_config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

include_directories(${INCLUDE_DIRECTORIES} ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${INCLUDE_DIRECTORIES} ${SDL_INCLUDE_DIR})
include_directories(${INCLUDE_DIRECTORIES} ${CURSES_INCLUDE_DIR})

add_subdirectory(src)

set(DOSBOX_SOURCES src/dosbox.cpp)

set(DOSBOX_HEADERS include/bios.h
                   include/bios_disk.h
                   include/callback.h
                   include/control.h
                   include/cpu.h
                   include/cross.h
                   include/debug.h
                   include/dma.h
                   include/dos_inc.h
                   include/dos_system.h
                   include/dosbox.h
                   include/fpu.h
                   include/hardware.h
                   include/inout.h
                   include/ipx.h
                   include/ipxserver.h
                   include/joystick.h
                   include/keyboard.h
                   include/logging.h
                   include/mapper.h
                   include/mem.h
                   include/midi.h
                   include/mixer.h
                   include/modules.h
                   include/mouse.h
                   include/paging.h
                   include/pci_bus.h
                   include/pic.h
                   include/programs.h
                   include/regs.h
                   include/render.h
                   include/serialport.h
                   include/setup.h
                   include/shell.h
                   include/support.h
                   include/timer.h
                   include/vga.h
                   include/video.h)

add_executable(dosbox MACOSX_BUNDLE WIN32 ${DOSBOX_SOURCES} ${DOSBOX_HEADERS})

target_link_libraries(dosbox cpu
                             dbdebug
                             dos
                             fpu
                             gui
                             hardware
                             ints
                             misc
                             shell
                             serialport
                             ${SDL_LIBRARY}
                             ${CURSES_LIBRARIES}
                             ${CORE_MIDI_LIBRARY}
                             ${AUDIO_TOOLBOX_LIBRARY})
