#ifndef TRIC_EXAMPLE_TEST_FUNCTIONS_H
#define TRIC_EXAMPLE_TEST_FUNCTIONS_H
#include <tricubic.h>
#include <cmath>
#include <set>
#include <tuple>

double* test_function_1(std::set<std::tuple<double, double, double>> const*);
double* test_function_2(std::set<std::tuple<double, double, double>> const*);

#endif //TRIC_EXAMPLE_TEST_FUNCTIONS_H
