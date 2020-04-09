#ifndef TRIC_ANALYSIS_CHECK_H
#define TRIC_ANALYSIS_CHECK_H

/** @file */ 
#include <memory>
#include <set>
#include <tuple>

typedef std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> corners_matrix;

/**
 * 
 * @param new_interval_start
 */
void execute_tests(set_of_double_triples &, int const&);

/**
 * 
 */
void execute_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>>&);

#endif //TRIC_ANALYSIS_CHECK_H