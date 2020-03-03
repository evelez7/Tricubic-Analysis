#ifndef TRIC_EXAMPLE_TEST_FUNCTIONS_H
#define TRIC_EXAMPLE_TEST_FUNCTIONS_H
#include <tricubic.h>
#include <cmath>
#include <set>
#include <tuple>
#include <vector>

int get_num_of_tests();
double function_1(double, double, double);
double function_2(double, double, double);
std::shared_ptr<std::vector<double>> test_function_1(std::shared_ptr<std::set<std::tuple<double, double, double>>> const&);
std::shared_ptr<std::vector<double>> test_function_2(std::shared_ptr<std::set<std::tuple<double, double, double>>> const&);

#endif //TRIC_EXAMPLE_TEST_FUNCTIONS_H
