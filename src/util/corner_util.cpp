/** \file corner_util.cpp */

#include "corner_util.h"
#include "../corners.h"
#include <random>
#include <iostream>
#include <limits>

double min_helper(double const&, double const&);

double max_helper(double const&, double const&);
/**
 *
 * \param new_interval_start
 * \return
 */
corners_matrix shift_corners(double const& new_interval_start) {
    corners_matrix shifted_corners(new std::array<std::tuple<double, double, double>, 8>);


    for (int i = 0; i < original_corners::num_rows; i++) {
        auto x = original_corners::points[i][0];
        auto y = original_corners::points[i][1];
        auto z = original_corners::points[i][2];

        x = shift(x, new_interval_start);
        y = shift(y, new_interval_start);
        z = shift(z, new_interval_start);

        auto new_corner = std::make_tuple(x, y, z);
        shifted_corners->at(i) = new_corner;

    }

    return shifted_corners;
}

/**
 * \brief Translate original corners to different randomized locations, between a min and max
 * 
 * \details Works similarly to generate_test_points().
 * The min and max can be specified, or min will default to 0
 * 
 * 
 */
corners_matrix randomize_corners(double min, double max) {
    std::uniform_real_distribution<double> interval(min, max); // P(i| a,b) = 1/(b-a)
    std::random_device seed;  // used to ensure randomness
    std::mt19937 rng(seed()); // Mersenne Twister rng

    auto translated_matrix = std::make_shared<std::array<std::tuple<double, double, double>, 8>>();

    for (int i = 0; i < translated_matrix->size(); i++) {
        double x = interval(rng);
        double y = interval(rng);
        double z = interval(rng);

        auto new_coordinate = std::make_tuple(x, y, z);
        translated_matrix->at(i) = new_coordinate;
    }

    return translated_matrix;
}

std::tuple<double, double, double> shift_math_reset(std::tuple<double, double, double> const& coordinate_triple, int point_id) {
    auto corresponding_unit_corner = original_corners::points[point_id];

    auto to_reset_x = std::get<0>(coordinate_triple);
    auto to_reset_y = std::get<1>(coordinate_triple);
    auto to_reset_z = std::get<2>(coordinate_triple);

    double new_x, new_y, new_z;

    auto reset_corner = std::make_shared<std::tuple<double, double, double>>();
    if (std::abs(std::abs(to_reset_x) - corresponding_unit_corner[0]) > 1) {
        new_x = std::abs(to_reset_x) - std::abs(std::abs(to_reset_x) - std::floor(std::abs(to_reset_x)));
    } else {
        new_x = to_reset_x;
    }

    if (std::abs(std::abs(to_reset_y) - corresponding_unit_corner[1]) > 1) {
        new_y = std::abs(to_reset_y) - std::abs(std::abs(to_reset_y) - 1);
    } else {
        new_y = to_reset_y;
    }

    if (std::abs(std::abs(to_reset_z) - corresponding_unit_corner[2]) > 1) {
        new_z = std::abs(to_reset_z) - std::abs(std::abs(to_reset_z) - 1);
    } else {
        new_z = to_reset_z;
    }

    new_x = new_x / new_x;
    new_y = new_y / new_y;
//    new_z =
}

corners_matrix reset_corners(corners_matrix matrix_to_reset) {
    auto corners_iterator = matrix_to_reset->begin();

    auto new_corners_matrix = std::make_shared<std::array<std::tuple<double, double, double>, 8>>();
    int p_id = 0;

    for (; corners_iterator != matrix_to_reset->end(); ++corners_iterator, ++p_id) {
        auto coordinate_triple = *corners_iterator;
        auto new_coord_triple = shift_math_reset(coordinate_triple, p_id);
        new_corners_matrix->at(p_id) = new_coord_triple;
    }
}

bool verify_corners(corners_matrix to_verify) {

}

/**
 * \brief Find minimum x, y, z in set of points
 * 
 * \param points a matrix containing corners
 */
std::tuple<double, double, double> find_minimums(corners_matrix const& points) {
    auto points_iterator = points->begin();

    double x_min = INFINITY; double y_min = INFINITY; double z_min = INFINITY;

    for (; points_iterator != points->end(); ++points_iterator) {
        auto coordinate_triple = *points_iterator;

        x_min = min_helper(std::get<0>(coordinate_triple), x_min);
        y_min = min_helper(std::get<1>(coordinate_triple), y_min);
        z_min = min_helper(std::get<2>(coordinate_triple), z_min);
    }

    return std::make_tuple(x_min, y_min, z_min);
}

double min_helper(double const& coord_component, double const& component_min) {
    if (coord_component < component_min) {
        return coord_component;
    }
    return component_min;
}

std::tuple<double, double, double> find_maximums(corners_matrix const& points) {
    auto points_iterator = points->begin();

    double x_max = -INFINITY; double y_max = -INFINITY; double z_max = -INFINITY;

    for (; points_iterator != points->end(); ++points_iterator) {
        auto coordinate_triple = *points_iterator;

        x_max = max_helper(std::get<0>(coordinate_triple), x_max);
        y_max = max_helper(std::get<1>(coordinate_triple), y_max);
        z_max = max_helper(std::get<2>(coordinate_triple), z_max);
    }

    return std::make_tuple(x_max, y_max, z_max);
}

double max_helper(double const& coord_component, double const& component_max) {
    if (coord_component > component_max) {
        return coord_component;
    }
    return component_max;
}

corners_matrix create_enclosure(corners_matrix const& points, double const& distance) {
    // NOTE: the components of these triples are not related
    // they do not constitute a real coordinate within the data set
    auto min_components = find_minimums(points);
    auto max_components = find_maximums(points);

    auto new_enclosure_corners = std::make_shared<std::array<std::tuple<double, double, double>, 8>>(); 
    
}