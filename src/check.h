#ifndef TRIC_ANALYSIS_CHECK_H
#define TRIC_ANALYSIS_CHECK_H

#include <memory>
#include <set>
#include <tuple>

/**
 * 
 * @param new_interval_start
 */
void execute_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>>&, int const&);

void execute_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>>&);

#endif //TRIC_ANALYSIS_CHECK_H