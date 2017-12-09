cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(DOS_SOURCES dos.cpp
                dos_devices.cpp
                dos_execute.cpp
                dos_files.cpp
                dos_ioctl.cpp
                dos_memory.cpp
                dos_misc.cpp
                dos_classes.cpp
                dos_programs.cpp
                dos_tables.cpp
                drives.cpp
                drive_virtual.cpp
                drive_local.cpp
                drive_cache.cpp
                drive_fat.cpp
                drive_iso.cpp
                dos_mscdex.cpp
                dos_keyboard_layout.cpp
                cdrom.cpp
                cdrom_ioctl_win32.cpp
                cdrom_aspi_win32.cpp
                cdrom_ioctl_linux.cpp
                cdrom_image.cpp
                cdrom_ioctl_os2.cpp)

set(DOS_HEADERS drives.h
                dev_con.h
                cdrom.h)

add_library(dos STATIC ${DOS_SOURCES} ${DOS_HEADERS})
