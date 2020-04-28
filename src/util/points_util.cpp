/** \file points_util.cpp */

#include "points_util.h"
#include <random>
#include <iostream>

#define POINT_LIMIT 500000

/**
 * \typedef represents the 2D matrix for the corners of a unit cube
 * The original points are defined in corners.h
 */
typedef std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> corners_matrix;

/**
 * \typedef represents a set of triples containing only doubles, the data type for the test point structures
 */
typedef std::shared_ptr<std::set<std::tuple<double, double, double>>> set_of_double_triples;

std::tuple<double, double, double> shift_math_reset(std::tuple<double, double, double> const&, int);

/**
 * Random number generator used to test function approximation.
 *
 * \param num_of_points the number of random points to generate
 * \return set<double> a set of triples representing (x,y,z) coordinates
 */
set_of_double_triples generate_test_points() {
    std::uniform_real_distribution<double> interval(0, 1); // P(i|a,b) = 1/(b-a)
    std::random_device seed; // used to ensure randomness
    std::mt19937 rng(seed()); // Mersenne Twister random number generator

    // Even if the rng repeats numbers, a set should guarantee uniqueness
    set_of_double_triples test_points(new std::set<std::tuple<double, double, double>>());

    while (test_points->size() < POINT_LIMIT) {
        double x = interval(rng);
        double y = interval(rng);
        double z = interval(rng);

        if (x == 0 && y == 0 && z == 0) {
            continue;
        }

        auto new_coordinate = std::make_tuple(x, y, z);
        test_points->insert(new_coordinate);
    }

    return test_points;
}

/**
 * \brief Pseudo shifts the unit cube by shifting the original test points
 *
 * \param original_test_points the original set of triples used for testing on the original unit cube
 * \param new_min the new minimum value that a component of a point can take (thus, the minimum for all the components)
 * \return a new set consisting of the original points, now shifted appropriately
 */
set_of_double_triples shift_test_points(set_of_double_triples const& original_test_points, double new_min) {
    auto shifted_points = std::make_shared<std::set<std::tuple<double, double, double>>>();

    for (auto point : *original_test_points) {
        auto x = std::get<0>(point);
        auto y = std::get<1>(point);
        auto z = std::get<2>(point);

        auto new_x = shift(x, new_min);
        auto new_y = shift(y, new_min);
        auto new_z = shift(z, new_min);

        auto new_triple = std::make_tuple(new_x, new_y, new_z);
        shifted_points->insert(new_triple);
    }

    return shifted_points;
}

double get_num_of_test_points() {
    return POINT_LIMIT;
}