#ifndef TRIC_ANALYSIS_CHECK_H
#define TRIC_ANALYSIS_CHECK_H
#include <memory>
#include <set>
#include <tuple>

std::unique_ptr<double[]> execute_test(int const&, std::unique_ptr<std::set<std::tuple<double, double, double>>> const&);

#endif //TRIC_ANALYSIS_CHECK_H
