/** \file main.cpp */

#include "check.h"
#include "util/points_util.h"
#include "util/corner_util.h"
#include "util/general_util.h"
#include <iostream>
#include <string.h>
#include <getopt.h>

// define number of shifts, thus the number of unit cubes to interpolate in
#define SHIFT_LIMIT 10

// BEGIN forward declarations
void run_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>> &, int const&);

void run_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>> &);

/**
 * \brief Run tests related to interpolating in a non-convenient area
 *
 * \details Two types of enclosure tests exist: distanced and in-place
 * Mode 0 runs both tests, mode 1 runs distanced and mode 2 runs in place
 *
 * \param verbose an optional argument to enable additional output
 * \param mode decides which mode to run the tests, defaults to 0 (both)
 */
void run_enclosure_tests(bool const& verbose = false, int const& mode = 0, double const& distance = 0.00000000000001);

// END forward declarations

/**
 * @brief Determines whether the full test suite is executed
 */ 
int main(int argc, char** argv) {

    // TODO: implement using getopt for flags`
    // TODO: Create emthod for the points testing
    if (argc < 2) {
        std::cout << "Generating " << get_num_of_test_points() << " test points" << std::endl;
        auto test_points = generate_test_points();
        run_tests(test_points);

    } else if (strncmp(argv[1], "enclosures", 10) == 0) {
        // TODO: get verbose flag from commandline options
        bool temp_verbose = true;
        run_enclosure_tests(temp_verbose);

    } else {
        std::cout << "Generating " << get_num_of_test_points() << " test points" << std::endl;
        auto test_points = generate_test_points();
        auto id = atoi(argv[1]);

        run_tests(test_points, id);
    }
}

/**
 * @brief Calls appropriate function in check.h to execute tests
 *
 * @param id the id of the function to test, decided by check.cpp
 * @param test_points the set of triples to test
 * @overload Runs tests only for the function specified by the param id
 */
void run_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>> & test_points, int const& id) {
    execute_tests(test_points, id);
}

/**
 * @brief Calls appropriate function in check.h to execute tests
 *
 * @param test_points the set of triples to test
 * @overload Runs tests for all functions within test_functions.h
 */
void run_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>> & test_points) {
    execute_tests(test_points);
}

void enclosure_math(corners_matrix & enclosure, corners_matrix const& random_corners, std::tuple<double, double, double> const& interval_minimums, std::tuple<double, double, double> const& interval_maximums) {

    auto enclosure_minimums = find_minimums(enclosure);
    auto enclosure_bar = get_coordinate_bars(enclosure, enclosure_minimums);

    auto enclosure_maximums = find_maximums(enclosure);
    auto component_deltas = get_component_deltas(enclosure_maximums, enclosure_minimums);
    auto enclosure_tilde = get_coordinate_tilde(enclosure_bar, component_deltas);

    // FIX: this might not work since it is possible the different components will exist within different intervals
    auto random_points = generate_test_points(std::get<0>(interval_minimums),
            std::get<0>(interval_maximums),
            std::get<1>(interval_minimums),
            std::get<1>(interval_maximums),
            std::get<2>(interval_minimums),
            std::get<2>(interval_maximums));
    execute_tests(random_points, enclosure);
}

void run_enclosure_tests(bool const& verbose, int const& mode, double const& distance) {
    std::cout << "Beginning tests of enclosures" << std::endl;

    auto random_corners = randomize_corners();

    auto original_maximums = find_maximums(random_corners);
    auto original_minimums = find_minimums(random_corners);
    corners_matrix enclosure;

    switch(mode) {
        case 0:
            std::cout << "Testing distanced enclosures at " << distance << " length" << std::endl << std::endl;
            enclosure = create_enclosure(random_corners, original_minimums, original_maximums, distance);
            enclosure_math(enclosure, random_corners, original_minimums, original_maximums);

            std:: cout << "Testing inplace enclosure" << std::endl << std::endl;
            enclosure = create_enclosure(random_corners, original_minimums, original_maximums);
            enclosure_math(enclosure, random_corners, original_minimums, original_maximums);
            return;
        case 1:
            std::cout << "Testing distanced enclosures at " << distance << " length" << std::endl << std::endl;
            enclosure = create_enclosure(random_corners, original_minimums, original_maximums, distance);
            break;
        case 2:
            std:: cout << "Testing inplace enclosure" << std::endl << std::endl;
            enclosure = create_enclosure(random_corners, original_minimums, original_maximums);
            break;
        default:
            throw "something went wrong";
    }
    enclosure_math(enclosure, random_corners, original_minimums, original_maximums);
}

