/** \file points_util.cpp */

#include "points_util.h"
#include <random>
#include <iostream>

#define POINT_LIMIT 500000


std::tuple<double, double, double> shift_math_reset(std::tuple<double, double, double> const&, int);

/**
 * Random number generator used to test function approximation.
 *
 * \param num_of_points the number of random points to generate
 * \return set<double> a set of triples representing (x,y,z) coordinates
 */
set_of_double_triples generate_test_points(double const& min, double const& max) {
    std::uniform_real_distribution<double> interval(min, max); // P(i|a,b) = 1/(b-a)
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
 *
 * @param x_min
 * @param x_max
 * @param y_min
 * @param y_max
 * @param z_min
 * @param z_max
 * @return
 */
set_of_double_triples generate_test_points(double const& x_min, double const& x_max, double const& y_min, double const& y_max, double const& z_min, double const& z_max) {
    std::uniform_real_distribution<double> x_interval(x_min, x_max);
    std::random_device x_seed;
    std::mt19937 x_rng(x_seed());

    auto x_values = std::make_unique<std::set<double>>();
    for (int i = 0; i < POINT_LIMIT; i++) {
        x_values->insert(x_interval(x_rng));
    }

    std::uniform_real_distribution<double> y_interval(y_min, y_max);
    std::random_device y_seed;
    std::mt19937 y_rng(y_seed());

    auto y_values = std::make_unique<std::set<double>>();
    for (int i = 0; i < POINT_LIMIT; i++) {
        y_values->insert(y_interval(y_rng));
    }

    std::uniform_real_distribution<double> z_interval(z_min, z_max);
    std::random_device z_seed;
    std::mt19937 z_rng(z_seed());

    auto z_values = std::make_unique<std::set<double>>();
    for (int i = 0; i < POINT_LIMIT; i++) {
        z_values->insert(z_interval(z_rng));
    }

    auto new_test_points = std::make_shared<std::set<std::tuple<double, double, double>>>();
    auto x_iterator = x_values->begin();
    auto y_iterator = y_values->begin();
    auto z_iterator = z_values->begin();

    for (; x_iterator != x_values->end(); ++x_iterator, ++y_iterator, *z_iterator) {
        new_test_points->emplace(std::make_tuple(*x_iterator, *y_iterator, *z_iterator));
    }
    return new_test_points;
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

set_of_double_triples shift_test_points(set_of_double_triples const& original_test_points, double new_min, double new_max) {
    auto shifted_points = std::make_shared<std::set<std::tuple<double, double, double>>>();

    for (auto point : *original_test_points) {
        auto x = std::get<0>(point);
        auto y = std::get<1>(point);
        auto z = std::get<2>(point);

        auto new_x = shift(x, new_min, new_max);
        auto new_y = shift(y, new_min, new_max);
        auto new_z = shift(z, new_min, new_max);

        auto new_triple = std::make_tuple(new_x, new_y, new_z);
        shifted_points->insert(new_triple);
    }

    return shifted_points;
}

double get_num_of_test_points() {
    return POINT_LIMIT;
}