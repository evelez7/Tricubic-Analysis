#include "util.h"
#include <random>
#include <iostream>

#define POINT_LIMIT 1000000

/**
 * Random number generator used to test function approximation.
 *
 * @param num_of_points the number of random points to generate
 * @return set<double> a set of triples representing (x,y,z) coordinates
 */
std::shared_ptr<std::set<std::tuple<double, double, double>>> generate_test() {
    std::uniform_real_distribution<double> interval(0, 1); // P(i|a,b) = 1/(b-a)
    std::random_device seed; // used to ensure randomness
    std::mt19937 rng(seed()); // Mersenne Twister random number generator

    // Even if the rng repeats numbers, a set should guarantee uniqueness
    std::shared_ptr<std::set<std::tuple<double, double, double>>> test_points(new std::set<std::tuple<double, double, double>>());

    while (test_points->size() < POINT_LIMIT) {
        double x = interval(rng);
        double y = interval(rng);
        double z = interval(rng);

        auto new_coordinate = std::make_tuple(x, y, z);
        test_points->insert(new_coordinate);
    }

    return test_points;
}

double shift_math(double original_component, int new_min) {
    // new_min is the minimum of the new interval of the cube [a,b]
    auto a = new_min;
    // since we deal with unit cubes, b is only 1 more than a on the new interval
    auto b = new_min + 1;

    return (a + ((b-a) * original_component));
}

/**
 * Pseudo shifts the cube needed for tricubic interpolation by shifting the test points generated on a [0,1] interval
 *
 * @param original_test_points the original set of triples used for testing on the original unit cube
 * @param new_min the new minimum value that a component of a point can take (thus, the minimum for all the components)
 * @return a new set consisting of the original points, now shifted appropriately
 */
std::shared_ptr<std::set<std::tuple<double, double, double>>> shift_test_points(std::shared_ptr<std::set<std::tuple<double, double, double>>> original_test_points, double new_min) {
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
 * Calculate the norm of a vector
 *
 * @param to_norm the vector whose norm is to be calculated
 * @return double representing the norm
 */
double norm(std::shared_ptr<std::vector<double>> const& to_norm) {
    double sum = 0;
    for (auto value : *to_norm) {
        sum += pow(value, 2);
    }

    return sqrt(sum);
}

double get_num_of_test_points() {
    return POINT_LIMIT;
}