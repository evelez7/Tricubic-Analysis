#ifndef TRIC_ANALYSIS_CHECK_H
#define TRIC_ANALYSIS_CHECK_H
#include <memory>
#include <set>

std::unique_ptr<double[]> execute_tests(std::unique_ptr<std::set<std::tuple<double, double, double>>> const&);
std::unique_ptr<double[]> test_1(std::unique_ptr<std::set<std::tuple<double, double, double>>> const&);
double check_error();

#endif //TRIC_ANALYSIS_CHECK_H
