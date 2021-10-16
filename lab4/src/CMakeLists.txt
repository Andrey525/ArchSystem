cmake_minimum_required(VERSION 3.0)
project(project)

set(SOURCE_EXE main/main.c)
set(SOURCE_LIB dgemm/dgemm.c)

add_library(dgemmlib STATIC ${SOURCE_LIB})
target_include_directories(dgemmlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/./dgemm)

add_executable(dgemmexe ${SOURCE_EXE})
target_link_libraries(dgemmexe dgemmlib)



set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../bin)