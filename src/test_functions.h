#ifndef TRIC_EXAMPLE_TEST_FUNCTIONS_H
#define TRIC_EXAMPLE_TEST_FUNCTIONS_H
#include <tricubic.h>
#include <cmath>
#include <set>
#include <tuple>
#include <vector>
#include <string>

typedef std::shared_ptr<std::vector<double>>(*interpolator)(std::shared_ptr<std::set<std::tuple<double, double, double>>> const&);
typedef double(*control_function)(double, double, double);

int get_num_of_tests();
std::string get_function_name(int const&);
std::tuple<interpolator, control_function> get_function_pair(int const&);

#endif //TRIC_EXAMPLE_TEST_FUNCTIONS_H