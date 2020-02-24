#include "check.h"
#include "test_functions.h"

void check_error(std::unique_ptr<double[]>&, std::unique_ptr<std::set<std::tuple<double, double, double>>> const&, double (*test)(double, double, double), std::unique_ptr<double[]> (*interpolator)(std::unique_ptr<std::set<std::tuple<double, double, double>>> const&));
double error(double, double);

std::unique_ptr<double[]> execute_test(int const& id, std::unique_ptr<std::set<std::tuple<double, double, double>>> const& test_points) {
    std::unique_ptr<double[]> errors(new double[test_points->size()]);

    switch(id) {
        case 1: {
            check_error(errors, test_points, function_1, test_function_1);
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