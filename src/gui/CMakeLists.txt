cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(GUI_SOURCES sdlmain.cpp
                sdl_mapper.cpp
                render.cpp
                render_scalers.cpp
                sdl_gui.cpp)

set(GUI_HEADERS dosbox_logo.h
                render_scalers.h
                render_templates.h
                render_loops.h
                render_simple.h
                render_templates_sai.h
                render_templates_hq.h
                render_templates_hq2x.h
                render_templates_hq3x.h
                midi.cpp midi_win32.h
                midi_oss.h
                midi_coreaudio.h
                midi_alsa.h
                midi_coremidi.h
                dosbox_splash.h)

add_library(gui STATIC ${GUI_SOURCES} ${GUI_HEADERS})
