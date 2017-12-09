cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

add_subdirectory(serialport)

set(HARDWARE_SOURCES adlib.cpp
                     dma.cpp
                     gameblaster.cpp
                     hardware.cpp
                     iohandler.cpp
                     joystick.cpp
                     keyboard.cpp
                     memory.cpp
                     mixer.cpp
                     pcspeaker.cpp
                     pci_bus.cpp
                     pic.cpp
                     sblaster.cpp
                     tandy_sound.cpp
                     timer.cpp
                     vga.cpp
                     vga_attr.cpp
                     vga_crtc.cpp
                     vga_dac.cpp
                     vga_draw.cpp
                     vga_gfx.cpp
                     vga_other.cpp
                     vga_memory.cpp
                     vga_misc.cpp
                     vga_seq.cpp
                     vga_xga.cpp
                     vga_s3.cpp
                     vga_tseng.cpp
                     vga_paradise.cpp
                     cmos.cpp
                     disney.cpp
                     gus.cpp
                     mpu401.cpp
                     ipx.cpp
                     ipxserver.cpp
                     dbopl.cpp)

set(HARDWARE_HEADERS )

add_library(hardware STATIC ${HARDWARE_SOURCES} ${HARDWARE_HEADERS})
