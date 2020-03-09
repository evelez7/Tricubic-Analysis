#include "util.h"
#include "check.h"
#include "test_functions.h"
#include <iostream>

// BEGIN forward declarations
double check_error(std::shared_ptr<std::set<std::tuple<double, double, double>>> const&, double (*test)(double, double, double), std::shared_ptr<std::vector<double>> (*interpolator)(std::shared_ptr<std::set<std::tuple<double, double, double>>> const&));
double error_calculation(std::shared_ptr<std::vector<double>> const&, std::shared_ptr<std::vector<double>> const&);
std::shared_ptr<std::vector<double>> generate_expected(std::shared_ptr<std::set<std::tuple<double,double,double>>> test_points, double (*test_function) (double, double, double));
double norm(std::shared_ptr<std::vector<double>> const&);
// END forward declarations

/**
 * Calls execute_test n number of times, n being the number of tests present
 *
 * @param test_points the set of unique triples to be tested for accuracy
 */
void execute_all_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>> const& test_points) {
    auto num_of_tests = get_num_of_tests();

    for (int i = 0; i < num_of_tests; i++) {
        execute_single_test(i, test_points);
    }
}

/**
 * Execute a specific test whose "ID" is given by run_tests.
 * run_tests calls this function n number of times, n being the number of functions present in the test suite.
 *
 * @param id the test number to be executed
 * @param test_points the set of unqiue triples to be tested and passes to the error checking function
 */
void execute_single_test(int const& id, std::shared_ptr<std::set<std::tuple<double, double, double>>> const& test_points) {
    auto error_value = 0.0;

    switch(id) {
        case 0: {
            std::cout << "Checking function for " << "sphere" << std::endl;
            error_value = check_error(test_points, function_1, test_function_1);
            break;
        }
        case 1: {
            std::cout << "Checking function for " << "sin(x + y + z)" << std::endl;
            error_value = check_error(test_points, function_2, test_function_2);

            break;
        }
        case 2: {
            std::cout << "Checking function for " << "1/(x^2 + y^2 + z^2)^1/2" << std::endl;
            error_value = check_error(test_points, function_3, test_function_3);
            break;
        }
        case 3: {
            std::cout << "Checking function " << "x^2 * y^2 * z^2" << std::endl;
            error_value = check_error(test_points, function_4, test_function_4);
            break;
        }
        default: {
            break;
        }
    }
    std::cout << "error: " << error_value << std::endl;
    std::cout << std::endl;
}

/**
 * This function generates the approximate and expected vectors from the interpolated and exact functions.
 * It calls error_calculation to execute the formula between the approximate and expected vectors.
 *
 * @param test_points vector of points to be used
 * @param test pointer to the exact function
 * @param interpolator pointer to the function that interpolates the exact function
 * @return a double value representing the error between the expected and approximate vectors (calls error_calculation)
 */
double check_error(std::shared_ptr<std::set<std::tuple<double, double, double>>> const& test_points, double (*test)(double, double, double), std::shared_ptr<std::vector<double>> (*interpolator)(std::shared_ptr<std::set<std::tuple<double, double, double>>> const&)) {
    auto approximates = interpolator(test_points);
    auto exact = generate_expected(test_points, test);

    return error_calculation(approximates, exact);
}

/**
 * Performs the math to calculate the error (sqrt((norm(expected - approximate)^2)/(approximate_norm)^2))
 *
 * @param approximate_vector vector of the values approximated at the ith test point
 * @param exact_vector vector of the exact value of the ith test point
 * @return the error double
 */
double error_calculation(std::shared_ptr<std::vector<double>> const& approximate_vector, std::shared_ptr<std::vector<double>> const& exact_vector) {
    auto difference_vector = std::make_shared<std::vector<double>>();

    if (approximate_vector->size() != exact_vector->size()) {
        throw "Vectors not of equal size";
    }

    for (int i = 0; i < approximate_vector->size(); i++) {
        auto approximate_val = approximate_vector->at(i);
        auto exact_val = exact_vector->at(i);

        difference_vector->push_back(exact_val-approximate_val);
    }

    auto difference_norm = norm(difference_vector);
    auto approximate_norm = norm(approximate_vector);
    auto difference_norm_squared = pow(difference_norm, 2);
    auto approximate_norm_squared = pow(approximate_norm, 2);

    auto final = sqrt(difference_norm_squared/approximate_norm_squared);
    return final;
}

/**
 *  Using the exact function, create the vector holding all exact values with respect to the test points
 *
 * @param test_points a set of triples, each one a test point in a given interval
 * @param test_function the exact function (which is interpolated else where)
 * @return vector holding the exact values for the exact function at a given triple of test_points
 */
std::shared_ptr<std::vector<double>> generate_expected(std::shared_ptr<std::set<std::tuple<double,double,double>>> test_points, double (*test_function) (double, double, double)) {
    auto exact_vector = std::make_shared<std::vector<double>>();
    for (auto point : *test_points) {
        auto x = std::get<0>(point);
        auto y = std::get<1>(point);
        auto z = std::get<2>(point);

        exact_vector->push_back(test_function(x,y,z));
    }
    return exact_vector;
}

