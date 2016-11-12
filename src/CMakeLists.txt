find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(GTKMM3 REQUIRED gtkmm-3.0)
pkg_check_modules(GST REQUIRED gstreamer-1.0)
pkg_check_modules(TAGLIB REQUIRED taglib)
pkg_check_modules(SQLITE3 REQUIRED sqlite3)

include_directories(
  ${GTK3_INCLUDE_DIRS}
  ${GTKMM3_INCLUDE_DIRS}
  ${GST_INCLUDE_DIRS}
  ${TAGLIB_INCLUDE_DIRS}
  ${SQLITE3_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

link_directories(
  ${GTK3_LIBRARY_DIRS}
  ${GTKMM3_LIBRARY_DIRS}
  ${GST_LIBRARY_DIRS}
  ${TAGLIB_LIBRARY_DIRS}
  ${SQLITE3_LIBRARY_DIRS}
  )

add_definitions(
  ${GTK3_CFLAGS_OTHER}
  ${GTKMM3_CFLAGS_OTHER}
  ${GTKMM_DEFINITIONS}
  )


add_subdirectory(GUI)
add_subdirectory(Audio)
add_subdirectory(Utilities)
add_subdirectory(Spectrum)
add_subdirectory(Audio-Library)
add_subdirectory(Audio-Info)

add_executable(fidel
  main.cpp
  GUI
  Audio
  Audio-Info
  Utilities
  Audio-Library
  Spectrum
  ) #more headers and cpp files can be added

target_compile_features(fidel PRIVATE cxx_range_for)

target_link_libraries(fidel
  ${GTK3_LIBRARIES}
  ${GTKMM3_LIBRARIES}
  ${TAGLIB_LIBRARIES}
  ${GST_LIBRARIES}
  ${SQLITE3_LIBRARIES}
  GUI
  Audio-Library
  Audio
  Audio-Info
  Utilities
  Spectrum
  -fopenmp
  -lgobject-2.0
  -lglib-2.0
  )

 message(STATUS "Generarating ${CMAKE_SOURCE_DIR}/.clang_complete")
 get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
 file(WRITE ${CMAKE_SOURCE_DIR}/.clang_complete "")
 foreach(dir ${dirs})
   file(APPEND ${CMAKE_SOURCE_DIR}/.clang_complete "-I${dir}\n")
 endforeach()
 #string(REPLACE "'" "" CMAKE_CXX_FLAGS_SPLIT ${CMAKE_CXX_FLAGS})
 #string(REPLACE " " ";" CMAKE_CXX_FLAGS_SPLIT ${CMAKE_CXX_FLAGS_SPLIT})
 foreach(flag ${CMAKE_CXX_FLAGS_SPLIT})
   file(APPEND ${CMAKE_SOURCE_DIR}/.clang_complete "${flag}\n")
 endforeach()
