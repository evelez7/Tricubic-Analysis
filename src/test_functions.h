#ifndef TRIC_EXAMPLE_TEST_FUNCTIONS_H
#define TRIC_EXAMPLE_TEST_FUNCTIONS_H
#include <tricubic.h>
#include <cmath>
#include <set>
#include <tuple>

void execute_tests(std::set<std::tuple<double, double, double>> const*);
double* example_1(std::set<std::tuple<double, double, double>> const*);
double* example_2(std::set<std::tuple<double, double, double>> const*);
void fill_array(double[64], double*, std::set<std::tuple<double, double, double>> const*);

#endif //TRIC_EXAMPLE_TEST_FUNCTIONS_H
