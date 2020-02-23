#ifndef TRIC_EXAMPLE_TEST_FUNCTIONS_H
#define TRIC_EXAMPLE_TEST_FUNCTIONS_H
#include <tricubic.h>
#include <cmath>
#include <set>
#include <tuple>

double function_1(double, double, double);
double function_2(double, double, double);
std::unique_ptr<double[]> test_function_1(std::unique_ptr<std::set<std::tuple<double, double, double>>> const&);
std::unique_ptr<double[]> test_function_2(std::unique_ptr<std::set<std::tuple<double, double, double>>> const&);

#endif //TRIC_EXAMPLE_TEST_FUNCTIONS_H
