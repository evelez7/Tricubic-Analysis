#include "check.h"
#include "util.h"
#include <iostream>

// define number of shifts, thus the number of unit cubes to interpolate in
#define SHIFT_LIMIT 10

// BEGIN forward declarations
void run_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>> &, int const&);

void run_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>> &);
// END forward declarations

/**
 * @brief Determines whether the full test suite is executed
 */ 
int main(int argc, char** argv) {
    std::cout << "Generating " << get_num_of_test_points() << " test points" << std::endl;
    auto test_points = generate_test();

    if (argc < 2) {
        run_tests(test_points);
    } else {
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

