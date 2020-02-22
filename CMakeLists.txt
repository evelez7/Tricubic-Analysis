cmake_minimum_required(VERSION 3.15)
project(tric_analysis)


set(CMAKE_CXX_STANDARD 14)
set(SRC ./src)
set(TRIC ./tricubic)
find_package(PythonLibs REQUIRED)

set(
        SOURCE
        ${SRC}/main.cpp
        ${SRC}/p.h
        ${SRC}/test_functions.cpp
        ${SRC}/test_functions.h
        ${SRC}/check.cpp
        ${SRC}/check.h
)

set(
        TRICUBIC
        ${TRIC}/coeff.h
        ${TRIC}/libtricubic.cpp
        ${TRIC}/ltricubic_utils.h
        ${TRIC}/tricubic.h
        ${TRIC}/tricubic_utils.cpp
        )

add_executable(tric_analysis ${SOURCE} ${TRICUBIC})
include_directories(./tricubic)
add_library(tricubic ./tricubic/libtricubic.cpp)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(tric_analysis ${PYTHON_LIBRARIES})
