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

/**
 * \typedef interpolator 
 * \brief Pointer to a function representing the tricubic interpolator
 */
typedef std::shared_ptr<std::list<double>>(*interpolator)(std::shared_ptr<std::set<std::tuple<double, double, double>>> const&, std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> const&);

/**
 * \typedef control
 * \brief Pointer to a function representing the exact function which has direct correspondance to the appropriate interpolator 
 */
typedef double(*control)(double, double, double);

double shift(double const&, double);

double norm(std::shared_ptr<std::list<double>> const&);

#endif //TRIC_ANALYSIS_UTIL_H