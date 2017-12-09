cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(SERIALPORT_SOURCES directserial.cpp
                       libserial.cpp
                       serialdummy.cpp
                       serialport.cpp
                       softmodem.cpp
                       misc_util.cpp
                       nullmodem.cpp)

set(SERIALPORT_HEADERS directserial.h
                       libserial.h
                       serialdummy.h
                       softmodem.h
                       misc_util.h
                       nullmodem.h)

add_library(serialport STATIC ${SERIALPORT_SOURCES} ${SERIALPORT_HEADERS})
