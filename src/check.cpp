#include "check.h"
#include "test_functions.h"
#include "util.h"
#include <iostream>

#define SHIFT_LIMIT 10
/**
 * @typedef represents the 2D matrix for the corners of a unit cube
 * The original points are defined in corners.h
 */
typedef std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> corners_matrix;

/**
 * @typedef represents a set of triples containing only doubles, the data type for the test point structures
 */
typedef std::shared_ptr<std::set<std::tuple<double, double, double>>> set_of_double_triples;
typedef std::shared_ptr<std::vector<double>>(*interpolator)(std::shared_ptr<std::set<std::tuple<double, double, double>>> const&, std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> const&);
typedef double(*control)(double, double, double);

double original_a = 0;
double original_b = 1;

void print_border() {
    std::cout << std::endl;
    for (int i = 0; i < 20; i++) {
        std::cout << "*";
    }
    std::cout << std::endl << std::endl;
}

void print_shift_notice() {
    std::cout << "Shifting points to conform with new interval" << std::endl;
}

void print_interval_notice(double new_base) {
    std::cout << "Testing on unit cube with interval [" << original_a + new_base << "," << original_b + new_base << "]" << std::endl << std::endl;
}
// BEGIN forward declarations
void execute_single_test(std::shared_ptr<std::set<std::tuple<double, double, double>>> , int const &, double const&);
double check_error(std::shared_ptr<std::set<std::tuple<double, double, double>>> const & test_points,
                   interpolator interpolator_function, control control_function,
                   std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> const& corners);
double error_calculation(std::shared_ptr<std::vector<double>> const &, std::shared_ptr<std::vector<double>> const &);

std::shared_ptr<std::vector<double>>
generate_expected(std::shared_ptr<std::set<std::tuple<double, double, double>>> test_points,
                  double (*test_function)(double, double, double));

double norm(std::shared_ptr<std::vector<double>> const &);
// END forward declarations

void execute_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>> &test_points) {

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

void execute_single_test(std::shared_ptr<std::set<std::tuple<double, double, double>>> test_points, int const &id,
                    double const &new_interval_start) {
    auto error_value = 0.0;
    // if new interval is 0, then the original corners will be given
    auto corners = shift_corners(new_interval_start);
    auto function_name = get_function_name(id);
    // tuple<interpolator, control>
    auto function_pair = get_function_pair(id);
    auto interpolator = std::get<0>(function_pair);
    auto base = std::get<1>(function_pair);

    if (new_interval_start != 0) {
        test_points = shift_test_points(test_points, new_interval_start);
    }

    std::cout << "Testing f(x, y, z) = "
              << function_name
              << std::endl;

    error_value = check_error(test_points, interpolator, base , corners);
    std::cout << "Error value: " << error_value << std::endl << std::endl;
}

double check_error(std::shared_ptr<std::set<std::tuple<double, double, double>>> const & test_points,
        interpolator interpolator_function, control control_function,
        std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> const& corners) {
    auto approximates = interpolator_function(test_points, corners);
    auto exact = generate_expected(test_points, control_function);

    return error_calculation(approximates, exact);
}

/**
 * Performs the math to calculate the error (sqrt((norm(expected - approximate)^2)/(approximate_norm)^2))
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
 *  Using the exact function, create the vector holding all exact values with respect to the test points
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
