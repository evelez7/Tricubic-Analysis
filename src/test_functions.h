#ifndef TRIC_EXAMPLE_TEST_FUNCTIONS_H
#define TRIC_EXAMPLE_TEST_FUNCTIONS_H

#include <tricubic.h>
#include <cmath>
#include <set>
#include <tuple>
#include <array>
#include <vector>
#include <memory>
#include <string>

typedef std::shared_ptr<std::vector<double>>(*interpolator)(std::shared_ptr<std::set<std::tuple<double, double, double>>> const&, std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> const&);
typedef double(*control)(double, double, double);

int get_num_of_tests();
std::string get_function_name(int const&);
std::tuple<interpolator,control> get_function_pair(int const&);

#endif //TRIC_EXAMPLE_TEST_FUNCTIONS_H