project(fidel)
cmake_minimum_required(VERSION 2.6)
add_subdirectory(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -Wall -g -fopenmp -lresolv -lz -lpthread -lltdl -ldl -ldl  -lpcap -lnet -lssl -lcrypto -lpcre -lpanel -lmenu -lform -lncurses -pthread -lgtk-x11-2.0 -lgdk-x11-2.0 -lgio-2.0 -lpangoft2-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo -lfreetype -lfontconfig -lpango-1.0 -lgmodule-2.0 -latk-1.0 -lgobject-2.0 -lgthread-2.0 -lrt -lglib-2.0   -lgthread-2.0 ")
set_target_properties(fidel PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_DEBUG_POSTFIX "_debug" CACHE STRING "Set Debug library postfix" FORCE) #changes the debug postfix to _debug
set_target_properties(fidel PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}) #sets the debug postfix
