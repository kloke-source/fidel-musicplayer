find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(GTKMM3 REQUIRED gtkmm-3.0)
pkg_check_modules(GST REQUIRED gstreamer-1.0)
pkg_check_modules(TAGLIB REQUIRED taglib)

include_directories(
  ${GTK3_INCLUDE_DIRS}
  ${GTKMM3_INCLUDE_DIRS}
  ${GST_INCLUDE_DIRS}
  ${TAGLIB_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

link_directories(
  ${GTK3_LIBRARY_DIRS}
  ${GTKMM3_LIBRARY_DIRS}
  ${GST_LIBRARY_DIRS}
  ${TAGLIB_LIBRARY_DIRS}
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
add_subdirectory(Audio-Info)
add_subdirectory(Audio-Library)

add_executable(fidel
  main.cpp
  GUI
  Audio
  Audio-Library
  Audio-Info
  Spectrum
  Utilities
  ) #more headers and cpp files can be added

target_compile_features(fidel PRIVATE cxx_range_for)

target_link_libraries(fidel
  ${GTK3_LIBRARIES}
  ${GTKMM3_LIBRARIES}
  ${TAGLIB_LIBRARIES}
  ${GST_LIBRARIES}
  GUI
  Audio
  Audio-Info
  Audio-Library
  Spectrum
  Utilities
  -fopenmp
  -lgobject-2.0
  -lglib-2.0
  )
