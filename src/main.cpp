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
 * \details
 *
 * \param verbose an optional argument to enable additional output
 */
void run_enclosure_tests(bool const& verbose = false);
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

void run_enclosure_tests(bool const& verbose) {
    if (verbose)
        std::cout << "Beginning tests of enclosures" << std::endl;

    // set the corners to random points in 3D space
    auto random_corners = randomize_corners();
    
    auto original_maximums = find_maximums(random_corners);
    auto original_minimums = find_minimums(random_corners);


    auto enclosure = create_enclosure(random_corners, original_minimums, original_maximums, 0.000000000001);

    auto enclosure_minimums = find_minimums(enclosure);
    auto enclosure_bar = get_coordinate_bars(enclosure, enclosure_minimums);

    auto enclosure_maximums = find_maximums(enclosure);
    auto delta_components = get_component_deltas(enclosure_maximums, enclosure_minimums);
    auto enclosure_tilde = get_coordinate_tilde(enclosure_bar, delta_components);

    auto random_points = generate_test_points(std::get<0>(original_minimums), std::get<0>(original_maximums));
    execute_tests(random_points, enclosure);
}

void enclosure_testing_generalized() {
    auto random_points = generate_test_points();

    auto original_maximums = find_maximums(random_points);
    auto original_minimums = find_minimums(random_points);
//    auto enclosure = create_enclosure(random_points, original_minimums, original_maximums);


}

void enclosure_testing_harder() {
    auto random_points = generate_test_points();

    auto original_maximums = find_maximums(random_points);
    auto original_minimums = find_minimums(random_points);


}