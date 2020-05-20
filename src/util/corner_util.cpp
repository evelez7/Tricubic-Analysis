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

//corners_matrix reset_corners(corners_matrix matrix_to_reset) {
//    auto corners_iterator = matrix_to_reset->begin();
//
//    auto new_corners_matrix = std::make_shared<std::array<std::tuple<double, double, double>, 8>>();
//    int p_id = 0;
//
//    for (; corners_iterator != matrix_to_reset->end(); ++corners_iterator, ++p_id) {
//        auto coordinate_triple = *corners_iterator;
//        auto new_coord_triple = shift_math_reset(coordinate_triple, p_id);
//        new_corners_matrix->at(p_id) = new_coord_triple;
//    }
//}

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

std::tuple<double, double, double> find_minimums(set_of_double_triples const& points) {
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

std::tuple<double, double, double> find_maximums(set_of_double_triples const& points) {
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

/**
 * \brief Create an enclosure around a set of points
 *
 * \details This method expects only 8 coordinates, thus a corners_matrix in our view.
 * Use the overloaded method for a list of arbitrary triples
 *
 * @param corners
 * @param distance
 * @return
 */
corners_matrix create_enclosure(corners_matrix const& corners, std::tuple<double, double, double> const& min_components, std::tuple<double, double, double> const& max_components, double const& distance) {
    auto new_enclosure_corners = std::make_shared<std::array<std::tuple<double, double, double>, 8>>();

    // unfortunately, the order of the corners is not intuitive
    new_enclosure_corners->at(0) = std::make_tuple(std::get<0>(min_components), std::get<1>(min_components), std::get<2>(min_components));
    new_enclosure_corners->at(1) = std::make_tuple(std::get<0>(max_components), std::get<1>(min_components), std::get<2>(min_components));
    new_enclosure_corners->at(2) = std::make_tuple(std::get<0>(min_components), std::get<1>(max_components), std::get<2>(min_components));
    new_enclosure_corners->at(3) = std::make_tuple(std::get<0>(max_components), std::get<1>(max_components), std::get<0>(min_components));
    new_enclosure_corners->at(4) = std::make_tuple(std::get<0>(min_components), std::get<1>(min_components), std::get<2>(min_components));
    new_enclosure_corners->at(5) = std::make_tuple(std::get<0>(max_components), std::get<1>(min_components), std::get<2>(max_components));
    new_enclosure_corners->at(6) = std::make_tuple(std::get<0>(min_components), std::get<1>(max_components), std::get<2>(max_components));
    new_enclosure_corners->at(7) = std::make_tuple(std::get<0>(max_components), std::get<1>(max_components), std::get<2>(max_components));

    return new_enclosure_corners;
}

corners_matrix get_coordinate_bars(corners_matrix const& corners, std::tuple<double, double, double> const& minimum_components) {
    auto x_min = std::get<0>(minimum_components);
    auto y_min = std::get<1>(minimum_components);
    auto z_min = std::get<2>(minimum_components);
    auto corners_bar = std::make_shared<std::array<std::tuple<double, double, double>, 8>>();

    auto corners_it = corners->begin();
    auto corners_bar_it = corners_bar->begin();
    for(; corners_it != corners->end(); ++corners_it, ++corners_bar_it) {
        auto corners_triple = *corners_it;
        auto x_bar = std::get<0>(corners_triple) - x_min;
        auto y_bar = std::get<1>(corners_triple) - y_min;
        auto z_bar = std::get<2>(corners_triple) - z_min;
        *corners_bar_it = std::make_tuple(x_bar, y_bar, z_bar);
    }

    return corners_bar;
}

corners_matrix get_coordinate_tilde(corners_matrix const& corners_bar, std::tuple<double, double, double> const& component_deltas) {
    auto x_delta = std::get<0>(component_deltas);
    auto y_delta = std::get<1>(component_deltas);
    auto z_delta = std::get<2>(component_deltas);

    auto corners_bar_it = corners_bar->begin();
    auto corners_tilde = std::make_shared<std::array<std::tuple<double, double, double>, 8>>();
    auto corners_tilde_it = corners_tilde->begin();
    for (; corners_bar_it != corners_bar->end(); ++corners_bar_it, ++corners_tilde_it) {
        auto coordinate_bar = *corners_bar_it;

        *corners_tilde_it = std::make_tuple(std::get<0>(coordinate_bar)/x_delta, std::get<1>(coordinate_bar)/y_delta, std::get<2>(coordinate_bar)/z_delta);
    }

    return corners_tilde;
}