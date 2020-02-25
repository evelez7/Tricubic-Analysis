#include "check.h"
#include "test_functions.h"
#include <iostream>

void check_error(std::unique_ptr<double[]>&, std::unique_ptr<std::set<std::tuple<double, double, double>>> const&, double (*test)(double, double, double), std::unique_ptr<double[]> (*interpolator)(std::unique_ptr<std::set<std::tuple<double, double, double>>> const&));
std::unique_ptr<double[]> execute_test(int const&, std::unique_ptr<std::set<std::tuple<double, double, double>>> const&);
double error(double, double);
double calculate_mean(std::unique_ptr<double[]> const&, int);

void run_tests(std::unique_ptr<std::set<std::tuple<double, double, double>>> const& test_points) {
    auto num_of_tests = get_num_of_tests();

    auto error_array_length = test_points->size();
    std::cout << error_array_length << std::endl;
    for (int i = 0; i < num_of_tests; i++) {
        auto errors = execute_test(i, test_points);

        auto mean = calculate_mean(errors, error_array_length);
        std::cout << "Mean: " << mean << std::endl;
    }
}
std::unique_ptr<double[]> execute_test(int const& id, std::unique_ptr<std::set<std::tuple<double, double, double>>> const& test_points) {
    std::unique_ptr<double[]> errors(new double[test_points->size()]);

    switch(id) {
        case 1: {
            check_error(errors, test_points, function_1, test_function_1);
            std::cout << "Checking function for " << "sphere" << std::endl;
            break;
        }
        case 2: {
            check_error(errors, test_points, function_2, test_function_2);
            break;
        }
        default: {
            break;
        }
    }
    return errors;
}

void check_error(std::unique_ptr<double[]>& error_vector, std::unique_ptr<std::set<std::tuple<double, double, double>>> const& test_points, double (*test)(double, double, double), std::unique_ptr<double[]> (*interpolator)(std::unique_ptr<std::set<std::tuple<double, double, double>>> const&)) {
    auto approximated_values = interpolator(test_points);

    int i = 0;
    for (auto coords : *test_points) {
        auto x = std::get<0>(coords);
        auto y = std::get<1>(coords);
        auto z = std::get<2>(coords);

        auto exact_value = test(x, y, z);
        auto approximated_value = approximated_values[i];
        error_vector[i] = error(exact_value, approximated_value);
    }
}

double error(double exact_value, double approximated_value) {
    auto numerator = pow((exact_value - approximated_value), 2);
    auto fraction = numerator / approximated_value;

    return sqrt(fraction);
}

double calculate_mean(std::unique_ptr<double[]> const& error_array_ptr, int array_length) {
    double total = 0;

    for (int i = 0; i < array_length; i++) {
        std::cout << error_array_ptr[i] << std:: endl;
        error_array_ptr[i] += total;
    }

    return (total/array_length);
}