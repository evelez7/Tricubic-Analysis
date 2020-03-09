#ifndef TRIC_ANALYSIS_UTIL_H
#define TRIC_ANALYSIS_UTIL_H

#include <set>
#include <tuple>
#include <vector>
#include <memory>

std::shared_ptr<std::set<std::tuple<double, double, double>>> generate_test();
double norm(std::shared_ptr<std::vector<double>> const&);
std::shared_ptr<std::set<std::tuple<double, double, double>>> shift_test_points(std::shared_ptr<std::set<std::tuple<double, double, double>>>, double);
double get_num_of_test_points();

#endif //TRIC_ANALYSIS_UTIL_H
