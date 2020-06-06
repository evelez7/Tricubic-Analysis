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

double shift(double const& original_component, double const& new_min, double const& new_max) {
    auto a = new_min;
    auto b = new_max;

    return (a + ((b-a) * original_component));
}

std::tuple<double, double, double> get_component_deltas(std::tuple<double, double, double> const& minimums, std::tuple<double, double, double> const& maximums) {
    return std::make_tuple(std::get<0>(maximums) - std::get<0>(minimums), std::get<1>(maximums) - std::get<1>(minimums), std::get<2>(maximums) - std::get<2>(minimums));
}