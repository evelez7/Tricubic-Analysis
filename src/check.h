/** \file */
#ifndef TRIC_ANALYSIS_CHECK_H
#define TRIC_ANALYSIS_CHECK_H
#include <memory>
#include <set>
#include <tuple>

/**
 * \typedef
 * \brief
 */
typedef std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> corners_matrix;

/**
 * \typedef
 * \brief
 */
typedef std::shared_ptr<std::set<std::tuple<double, double, double>>> set_of_double_triples;

/**
 * 
 * \param new_interval_start
 */
void execute_tests(set_of_double_triples &, int const&);

/**
 * 
 * \param 
 */
void execute_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>>&);

void execute_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>>&, corners_matrix &);

#endif //TRIC_ANALYSIS_CHECK_H