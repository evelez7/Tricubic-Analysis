#include "util.h"
#include "corners.h"
#include <random>
#include <list>
#include <iostream>

#define POINT_LIMIT 500000

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
 * Random number generator used to test function approximation.
 *
 * @param num_of_points the number of random points to generate
 * @return set<double> a set of triples representing (x,y,z) coordinates
 */
set_of_double_triples generate_test() {
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

double shift_math(double const& original_component, double new_min) {
    // new_min is the minimum of the new interval of the cube [a,b]
    auto a = new_min;
    // since we deal with unit cubes, b is only 1 more than a on the new interval
    auto b = new_min + 1;

    return (a + ((b-a) * original_component));
}

/**
 * @brief Pseudo shifts the unit cube by shifting the original test points
 *
 * @param original_test_points the original set of triples used for testing on the original unit cube
 * @param new_min the new minimum value that a component of a point can take (thus, the minimum for all the components)
 * @return a new set consisting of the original points, now shifted appropriately
 */
set_of_double_triples shift_test_points(set_of_double_triples const& original_test_points, double new_min) {
    auto shifted_points = std::make_shared<std::set<std::tuple<double, double, double>>>();

    for (auto point : *original_test_points) {
        auto x = std::get<0>(point);
        auto y = std::get<1>(point);
        auto z = std::get<2>(point);

        auto new_x = shift_math(x, new_min);
        auto new_y = shift_math(y, new_min);
        auto new_z = shift_math(z, new_min);

        auto new_triple = std::make_tuple(new_x, new_y, new_z);
        shifted_points->insert(new_triple);
    }

    return shifted_points;
}

/**
 *
 * @param new_interval_start
 * @return
 */
corners_matrix shift_corners(double const& new_interval_start) {
    corners_matrix shifted_corners(new std::array<std::tuple<double, double, double>, 8>);


    for (int i = 0; i < original_corners::num_rows; i++) {
            auto x = original_corners::points[i][0];
            auto y = original_corners::points[i][1];
            auto z = original_corners::points[i][2];

            x = shift_math(x, new_interval_start);
            y = shift_math(y, new_interval_start);
            z = shift_math(z, new_interval_start);

            auto new_corner = std::make_tuple(x, y, z);
            shifted_corners->at(i) = new_corner;

    }

    return shifted_corners;
}

double norm(std::shared_ptr<std::list<double>> const& to_norm) {
    double sum = 0;
    auto to_norm_it = to_norm->begin();

    for (; to_norm_it != to_norm->end(); ++to_norm_it) {
        sum += pow(*to_norm_it, 2.0);
    }

    return sqrt(sum);
}

double get_num_of_test_points() {
    return POINT_LIMIT;
}