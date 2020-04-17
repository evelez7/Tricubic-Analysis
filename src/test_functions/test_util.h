#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <cmath>
#include <memory>
#include <list>
#include <set>
#include <tuple>
#include <array>
#include <string>
#include <tricubic.h>

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
typedef double(*exact)(double, double, double);

std::shared_ptr<std::list<double>> fill_list(double *, std::shared_ptr<std::set<std::tuple<double, double, double>>> const &);

int get_num_of_tests();

std::string get_function_name(int const&);

std::tuple<interpolator, exact> get_function_pair(int const&);

#endif
