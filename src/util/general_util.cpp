/** \file general_util.cpp */

#include "general_util.h"
#include <cmath>

/**
 * 
 */
double norm(std::shared_ptr<std::list<double>> const& to_norm) {
    double sum = 0;
    auto to_norm_it = to_norm->begin();

    for (; to_norm_it != to_norm->end(); ++to_norm_it) {
        sum += pow(*to_norm_it, 2.0);
    }

    return sqrt(sum);
}

double shift(double const& original_component, double new_min) {
    // new_min is the minimum of the new interval of the cube [a,b]
    auto a = new_min;
    // since we deal with unit cubes, b is only 1 more than a on the new interval
    auto b = new_min + 1;

    return (a + ((b-a) * original_component));
}
