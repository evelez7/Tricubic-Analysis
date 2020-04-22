/** \file util.h */
#ifndef TRIC_ANALYSIS_POINTS_UTIL_H
#define TRIC_ANALYSIS_POINTS_UTIL_H

#include "general_util.h"

std::shared_ptr<std::set<std::tuple<double, double, double>>> generate_test_points();

double norm(std::shared_ptr<std::list<double>> const&);

set_of_double_triples shift_test_points(set_of_double_triples const&, double);

double get_num_of_test_points();

#endif //TRIC_ANALYSIS_POINTS_UTIL_H
