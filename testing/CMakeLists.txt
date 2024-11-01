cmake_minimum_required(VERSION 3.14)

project(testing)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(glog REQUIRED)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Freetype REQUIRED)

set(FRIBIDI_INCLUDE_DIR "/usr/include/fribidi")
set(FRIBIDI_LIBRARY "/usr/lib/x86_64-linux-gnu/libfribidi.so")

set(HARFBUZZ_INCLUDE_DIRS "/usr/include/harfbuzz")
set(HARFBUZZ_LIBRARY "/usr/lib/x86_64-linux-gnu/libharfbuzz.so")

add_executable(
  testing_main
  testing_main.cpp
  ~/BidiRenderer/glyph_string.cpp
)

target_link_libraries(
  testing_main
  GTest::gtest_main
  glog::glog
)

target_link_libraries(testing_main Qt5::Core Qt5::Widgets)
target_link_libraries(testing_main Freetype::Freetype)
target_link_libraries(testing_main ${FRIBIDI_LIBRARY})
target_link_libraries(testing_main ${HARFBUZZ_LIBRARY})


target_include_directories(testing_main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../")
target_include_directories(testing_main PRIVATE ${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})
target_include_directories(testing_main PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_include_directories(testing_main PRIVATE ${FRIBIDI_INCLUDE_DIR})
target_include_directories(testing_main PRIVATE ${HARFBUZZ_INCLUDE_DIRS})
