#ifndef TRIC_ANALYSIS_UTIL_H
#define TRIC_ANALYSIS_UTIL_H

#include <set>
#include <array>
#include <tuple>
#include <memory>
#include <list>

/**
 * @typedef represents the 2D matrix for the corners of a unit cube
 * The original points are defined in corners.h
 */
typedef std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> corners_matrix;

/**
 * @typedef represents a set of triples containing only doubles, the data type for the test point structures
 */
typedef std::shared_ptr<std::set<std::tuple<double, double, double>>> set_of_double_triples;
std::shared_ptr<std::set<std::tuple<double, double, double>>> generate_test();
double norm(std::shared_ptr<std::list<double>> const&);
set_of_double_triples shift_test_points(set_of_double_triples const&, double);
double get_num_of_test_points();
std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> shift_corners(double const&);

#endif //TRIC_ANALYSIS_UTIL_H
