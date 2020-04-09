#include "check.h"
#include "test_functions.h"
#include "util.h"
#include <iostream>
#include <list>

#define SHIFT_LIMIT 10

/**
 * @typedef 
 * @brief  A set containing triples of doubles. Used for the n test points created at program start for function testing.
 */
typedef std::shared_ptr<std::set<std::tuple<double, double, double>>> set_of_double_triples;

/**
 * @typedef Alias for the functions in test_functions used for interpolating and estimating
 */
typedef std::shared_ptr<std::list<double>>(*interpolator)(std::shared_ptr<std::set<std::tuple<double, double, double>>> const&, std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> const&);

/**
 * @typedef Alias for the exact functions in test_functions used to compare the results of the respective interpolators
 */
typedef double(*control)(double, double, double);

// BEGIN forward declarations
void execute_single_test(set_of_double_triples&, int const &, double const&);

double check_error(std::shared_ptr<std::set<std::tuple<double, double, double>>> const&,
                   std::shared_ptr<std::set<std::tuple<double, double, double>>> const&,
                   interpolator interpolator_function, control control_function,
                   std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> const& corners);

double error_calculation(std::shared_ptr<std::list<double>> const&, std::shared_ptr<std::list<double>> const&);

std::shared_ptr<std::vector<double>>
generate_expected(std::shared_ptr<std::set<std::tuple<double, double, double>>> test_points,
                  double (*test_function)(double, double, double));

double norm(std::shared_ptr<std::vector<double>> const &);

std::shared_ptr<std::list<double>>
generate_expected_list(set_of_double_triples,
                       double (*test_function)(double, double, double));
// END forward declarations

double original_a = 0;
double original_b = 1;

/**
 * @brief Prints a line of asterisks to "beautify" output
 */
void print_border() {
    std::cout << std::endl;
    for (int i = 0; i < 20; i++) {
        std::cout << "*";
    }
    std::cout << std::endl << std::endl;
}

/**
 * @brief Prints notice that original cube points will be shifted
 */ 
void print_shift_notice() {
    std::cout << "Shifting points to conform with new interval" << std::endl;
}

/**
 * @brief Prints notice  
 */
void print_interval_notice(double new_base) {
    std::cout << "Testing on unit cube with interval [" << original_a + new_base << "," << original_b + new_base << "]" << std::endl << std::endl;
}

/**
 * @brief See check.h for full documentation
 */
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

/**
 * @brief See check.h for full documentation
 */
void execute_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>> &test_points, int const &id) {
    for (int i = 0; i < SHIFT_LIMIT; i++) {
        execute_single_test(test_points, id, i);
    }
}

/**
 * @brief Selects a test to execute based on an id
 * 
 * @details Called many times from either overloaded execute_tests function. Also fetches all details to call check_error and shift_test_points 
 * 
 * @param test_points used to test interpolator and control functions
 * @param id identifier for which function to execute specified in test_functions.cpp
 * @param new_interval_start the new lowest value from which a component of the unit cube can start (might be 0)
 */
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

    double error_value = 0;

//    if (new_interval_start == 0) {
//        error_value = check_error(original_test_points, original_test_points, interpolator, base, corners);
//    } else {
        error_value = check_error(original_test_points, shifted_test_points, interpolator, base , corners);
//    }
    std::cout << "Error value: " << error_value << std::endl << std::endl;
}

/**
 * @brief
 * 
 * @param test_points
 * @param interpolator_function
 * @param control_function
 */
double check_error(std::shared_ptr<std::set<std::tuple<double, double, double>>> const & original_test_points,
        std::shared_ptr<std::set<std::tuple<double, double, double>>> const& shifted_test_points,
        interpolator interpolator_function, control control_function,
        std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> const& corners) {
    auto approximates = interpolator_function(original_test_points, corners);
    auto exact = generate_expected_list(shifted_test_points, control_function);

    return error_calculation(approximates, exact);
}

/**
 * @brief Performs the math to calculate the error between two vectors 
 *
 * @param approximate_vector vector of the values approximated at the ith test point
 * @param exact_vector vector of the exact value of the ith test point
 * @return the error double
 */
double error_calculation(std::shared_ptr<std::vector<double>> const &approximate_vector,
                         std::shared_ptr<std::vector<double>> const &exact_vector) {
    auto difference_vector = std::make_shared<std::vector<double>>();

    if (approximate_vector->size() != exact_vector->size()) {
        throw "Vectors not of equal size";
    }

    for (int i = 0; i < approximate_vector->size(); i++) {
        auto approximate_val = approximate_vector->at(i);
        auto exact_val = exact_vector->at(i);

        difference_vector->push_back(exact_val - approximate_val);
    }

    auto difference_norm = norm(difference_vector);
    auto approximate_norm = norm(approximate_vector);
    auto difference_norm_squared = pow(difference_norm, 2.0);
    auto approximate_norm_squared = pow(approximate_norm, 2.0);
    auto exact_norm = norm(exact_vector);
    auto exact_norm_squared = pow(exact_norm, 2.0);

    auto final = sqrt(difference_norm_squared / exact_norm_squared);
    return final;
}

/**
 * @brief Performs the math to calculate the error between two lists
 * 
 */
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

/**
 * @brief Using the exact function, create the vector holding all exact values with respect to the test points
 *
 * @param test_points a set of triples, each one a test point in a given interval
 * @param test_function the exact function (which is interpolated else where)
 * @return vector holding the exact values for the exact function at a given triple of test_points
 */
std::shared_ptr<std::vector<double>>
generate_expected(std::shared_ptr<std::set<std::tuple<double, double, double>>> test_points,
                  double (*test_function)(double, double, double)) {
    auto exact_vector = std::make_shared<std::vector<double>>();

    for (auto point : *test_points) {
        auto x = std::get<0>(point);
        auto y = std::get<1>(point);
        auto z = std::get<2>(point);

        exact_vector->push_back(test_function(x, y, z));
    }

    return exact_vector;
}

std::shared_ptr<std::list<double>>
generate_expected_list(set_of_double_triples test_points,
                  double (*test_function)(double, double, double)) {
    auto exact_list = std::make_shared<std::list<double>>();

    for (auto point : *test_points) {
        auto x = std::get<0>(point);
        auto y = std::get<1>(point);
        auto z = std::get<2>(point);

        exact_list->push_back(test_function(x, y, z));
    }

    return exact_list;
}
