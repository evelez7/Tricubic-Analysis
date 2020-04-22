cmake_minimum_required(VERSION 3.15)
project(tric_analysis)

set(CMAKE_CXX_STANDARD 14)
set(SRC ./src)
set(TRIC ./tricubic)
set(TESTS ./src/test_functions)
set(UTIL ./src/util)

find_package(PythonLibs REQUIRED)

set(
        SOURCE
        ${SRC}/main.cpp
        ${SRC}/corners.h
        ${SRC}/check.cpp
        ${SRC}/check.h
        ${TESTS}/test_1.cpp
        ${TESTS}/test_2.cpp
        ${TESTS}/test_3.cpp
        ${TESTS}/test_4.cpp
        ${TESTS}/test_5.cpp
        ${TESTS}/test_6.cpp
        ${TESTS}/test_util.cpp
        ${TESTS}/test_util.h
        ${UTIL}/corner_util.h
        ${UTIL}/corner_util.cpp
        ${UTIL}/points_util.h
        ${UTIL}/points_util.cpp
        ${UTIL}/general_util.h
        ${UTIL}/general_util.cpp
)

set(
        TRICUBIC
        ${TRIC}/coeff.h
        ${TRIC}/libtricubic.cpp
        ${TRIC}/ltricubic_utils.h
        ${TRIC}/tricubic.h
        ${TRIC}/tricubic_utils.cpp
        src/test_functions/test_1.h src/test_functions/test_2.h src/test_functions/test_3.h src/test_functions/test_4.h src/test_functions/test_5.h src/test_functions/test_6.h)

add_executable(tric_analysis ${SOURCE} ${TRICUBIC})
include_directories(./tricubic)
add_library(tricubic ./tricubic/libtricubic.cpp)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(tric_analysis ${PYTHON_LIBRARIES})
