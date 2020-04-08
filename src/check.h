#ifndef TRIC_ANALYSIS_CHECK_H
#define TRIC_ANALYSIS_CHECK_H

/** @file */ 
#include <memory>
#include <set>
#include <tuple>

/**
 * hehehe
 * @brief 2D matrix holding the corners of the unit cube
 * @var hello
 * @typedef 2d matrixi hdhdhd
 * this is a typedefo\
 * \var hello
 */
typedef std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> corners_matrix;

/**
 * 
 * @param new_interval_start
 */
void execute_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>>&, int const&);

/**
 * 
 */
void execute_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>>&);

#endif //TRIC_ANALYSIS_CHECK_H