cmake_minimum_required(VERSION 3.0)
project(project)

set(SOURCE_EXE main/main.c)
set(SOURCE_LIB memtest/memtest.c)

add_library(memtestlib STATIC ${SOURCE_LIB})
target_include_directories(memtestlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/./memtest)

add_executable(memtestexe ${SOURCE_EXE})
target_link_libraries(memtestexe memtestlib)



set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../bin)