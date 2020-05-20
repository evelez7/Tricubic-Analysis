/** \file check.cpp */

#include "check.h"
#include "test_functions/test_util.h"
#include "util/general_util.h"
#include "util/corner_util.h"
#include "util/points_util.h"
#include <iostream>
#include <list>

/**
 * \def SHIFT_LIMIT
 * \brief The number of shifts to be conducted for the unit cube and thus the test points
 */
#define SHIFT_LIMIT 10

// BEGIN FORWARD DECLARATIONS

/**
 * \brief Selects a test to execute based on an id
 * 
 * \details Called many times from either overloaded execute_tests function. Also fetches all details to call check_error and shift_test_points 
 * 
 * \param test_points used to test interpolator and control functions
 * \param id identifier for which function to execute specified in test_functions.cpp
 * \param new_interval_start the new lowest value from which a component of the unit cube can start (might be 0)
 */
void execute_single_test(set_of_double_triples&, int const &, double const&);

void execute_single_test(set_of_double_triples&, int const&, corners_matrix &, double const& min = 0, double const& max = 0);
/**
 * \brief Orchestrates necessities for calculating the error 
 * 
 * \details The superior to error_calculation. Gathers the values from the control and interpolator functions and sends them to error_calculation
 *
 * \param original_test_points The points used to evaluate the control
 * \param shifted_test_points The points used to evaluate the interpolator (is the same as original at a = 0)
 * \param interpolator_function The function used to estimate test points within a unit cube
 * \param control_function The corresponding exact function of the interpolator
 * \param corners The position of the corners of the unit cube
 * \return the error double
 */
double check_error(set_of_double_triples const&, set_of_double_triples const&, interpolator, control, corners_matrix const&);

/**
 * \brief Performs the math to calculate the error between two vectors 
 * 
 * \details The formula is sqrt(||V_e - V_a||^2 / ||V_e||^2)
 *
 * \param approximate_list list of the values approximated at the ith test point
 * \param exact_list list of the exact value of the ith test point
 * \return the error double
 */
double error_calculation(std::shared_ptr<std::list<double>> const&, std::shared_ptr<std::list<double>> const&);

/**
 * \brief Generates a list of expected solutions
 * 
 * \details Generates a list which is used as a standard to compare the interpolated solutions by in check_error
 * 
 * \param test_points Evaluated using exact_function to generate expected solutions
 * \param exact_function The corresponding control to an interpolator 
 * \return a list of equal size to test_points that holds the expected evaluations of exact_function at some test point 
 */
std::shared_ptr<std::list<double>>
generate_expected_list(set_of_double_triples,
                       double (*test_function)(double, double, double));

// END FORWARD DECLARATIONS

/**
 * \brief The initial beginning of the interval of the unit cube
 */
double original_a = 0;

/**
 * \brief The initial end of the interval of the unit cube
 */
double original_b = 1;

/**
 * \brief Prints a line of asterisks to "beautify" output
 */
void print_border() {
    std::cout << std::endl;
    for (int i = 0; i < 20; i++) {
        std::cout << "*";
    }
    std::cout << std::endl << std::endl;
}

/**
 * \brief Prints notice that original cube points will be shifted
 */ 
void print_shift_notice() {
    std::cout << "Shifting points to conform with new interval" << std::endl;
}

/**
 * \brief Prints notice of new interval 
 */
void print_interval_notice(double new_base) {
    std::cout << "Testing on unit cube with interval [" << original_a + new_base << "," << original_b + new_base << "]" << std::endl << std::endl;
}

void execute_tests(set_of_double_triples& test_points) {
    for (int i = 0; i < SHIFT_LIMIT; i++) {
        print_border();

        if (i != 0) {
            print_shift_notice();
        }

        print_interval_notice(i);

        for (int j = 0; j < get_num_of_tests(); j++) {
            execute_single_test(test_points, j, i);
        }

        print_border();
    }
}

void execute_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>> &test_points, int const &id) {
    for (int i = 0; i < SHIFT_LIMIT; i++) {
        execute_single_test(test_points, id, i);
    }
}

void execute_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>> &test_points, corners_matrix & enclosure) {
    for (int i = 0; i < get_num_of_tests(); i++) {
        execute_single_test(test_points, i, enclosure);
    }
}

void execute_single_test(set_of_double_triples &original_test_points, int const &id,
                    double const &new_interval_start) {
    // if new interval is 0, then the original corners will be given
    auto corners = shift_corners(new_interval_start);
    auto function_name = get_function_name(id);

    // tuple<interpolator, control>
    auto function_pair = get_function_pair(id);

    // both are pointers to functions
    auto interpolator = std::get<0>(function_pair);
    auto base = std::get<1>(function_pair);

    auto shifted_test_points = shift_test_points(original_test_points, new_interval_start);


    std::cout << "Testing f(x, y, z) = "
              << function_name
              << std::endl;

    auto error_value = check_error(original_test_points, shifted_test_points, interpolator, base , corners);

    std::cout << "Error value: " << error_value << std::endl << std::endl;
}

void execute_single_test(set_of_double_triples &original_test_points, int const &id,
                         corners_matrix & enclosure, double const& min, double const& max) {
    auto function_name = get_function_name(id);

    // tuple<interpolator, control>
    auto function_pair = get_function_pair(id);

    // both are pointers to functions
    auto interpolator = std::get<0>(function_pair);
    auto base = std::get<1>(function_pair);

    auto shifted_test_points = shift_test_points(original_test_points, min, max);

    std::cout << "Testing f(x, y, z) = "
              << function_name
              << std::endl;

    auto error_value = check_error(original_test_points, original_test_points, interpolator, base , enclosure);

    std::cout << "Error value: " << error_value << std::endl << std::endl;
}

double check_error(set_of_double_triples const& original_test_points,
        set_of_double_triples const& shifted_test_points,
        interpolator interpolator_function, control control_function,
        corners_matrix const& corners) {
    auto approximates = interpolator_function(original_test_points, corners);
    auto exact = generate_expected_list(shifted_test_points, control_function);

    return error_calculation(approximates, exact);
}

double error_calculation(std::shared_ptr<std::list<double>> const &approximate_list,
                         std::shared_ptr<std::list<double>> const &exact_list) {
    auto difference_list = std::make_shared<std::list<double>>();

    if (approximate_list->size() != exact_list->size()) {
        throw "Vectors not of equal size";
    }

    auto approx_it = approximate_list->begin();
    auto exact_it = exact_list->begin();

    for(; approx_it != approximate_list->end() && exact_it != exact_list->end(); ++approx_it, ++exact_it) {
        difference_list->push_back((*exact_it) - (*approx_it));
    }

    auto difference_norm = norm(difference_list);
    auto difference_norm_squared = pow(difference_norm, 2.0);

    auto exact_norm = norm(exact_list);
    auto exact_norm_squared = pow(exact_norm, 2.0);

    auto final = sqrt(difference_norm_squared / exact_norm_squared);
    return final;
}

std::shared_ptr<std::list<double>>
generate_expected_list(set_of_double_triples test_points,
                  control exact_function) {
    auto exact_list = std::make_shared<std::list<double>>();

    for (auto point : *test_points) {
        auto x = std::get<0>(point);
        auto y = std::get<1>(point);
        auto z = std::get<2>(point);

        exact_list->push_back(exact_function(x, y, z));
    }

    return exact_list;
}
