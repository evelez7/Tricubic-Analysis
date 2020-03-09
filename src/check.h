#ifndef TRIC_ANALYSIS_CHECK_H
#define TRIC_ANALYSIS_CHECK_H

#include <memory>
#include <set>
#include <tuple>

void execute_all_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>> const&);
void execute_single_test(int const&, std::shared_ptr<std::set<std::tuple<double, double, double>>> const&);

#endif //TRIC_ANALYSIS_CHECK_H
