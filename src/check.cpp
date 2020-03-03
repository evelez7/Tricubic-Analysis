#include "check.h"
#include "test_functions.h"
#include <iostream>

double check_error(std::shared_ptr<std::vector<double>>&, std::shared_ptr<std::set<std::tuple<double, double, double>>> const&, double (*test)(double, double, double), std::shared_ptr<std::vector<double>> (*interpolator)(std::shared_ptr<std::set<std::tuple<double, double, double>>> const&));
void execute_test(int const&, std::shared_ptr<std::set<std::tuple<double, double, double>>> const&);
double error(double, double);
double error(std::shared_ptr<std::vector<double>>, std::shared_ptr<std::vector<double>>);
double calculate_mean(std::shared_ptr<std::vector<double>> const&);
std::shared_ptr<std::vector<double>> generate_exact_vector(std::shared_ptr<std::set<std::tuple<double,double,double>>> test_points, double (*test_function) (double, double, double));

void run_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>> const& test_points) {
    auto num_of_tests = get_num_of_tests();

    auto error_array_length = test_points->size();
    for (int i = 0; i < num_of_tests; i++) {

        execute_test(i, test_points);
    }
}
void execute_test(int const& id, std::shared_ptr<std::set<std::tuple<double, double, double>>> const& test_points) {
    auto errors = std::make_shared<std::vector<double>>();
    errors->reserve(test_points->size());

    switch(id) {
        case 0: {
            auto error = check_error(errors, test_points, function_1, test_function_1);
            std::cout << "Checking function for " << "sphere" << std::endl;
            std::cout << "error: " << error << std::endl;
            break;
        }
        case 1: {
            auto error = check_error(errors, test_points, function_2, test_function_2);
            std::cout << "Checking function for " << "sin" << std::endl;
            std::cout << "error: " << error << std::endl;
            break;
        }
        default: {
            break;
        }
    }
}

// TODO: Name of function misleading, probably should pass approximate and exact
// TODO: exact should be called expected
double check_error(std::shared_ptr<std::vector<double>>& error_vector, std::shared_ptr<std::set<std::tuple<double, double, double>>> const& test_points, double (*test)(double, double, double), std::shared_ptr<std::vector<double>> (*interpolator)(std::shared_ptr<std::set<std::tuple<double, double, double>>> const&)) {
    auto approximates = interpolator(test_points);
    auto exact = generate_exact_vector(test_points, test);

    return error(approximates, exact);
}

double norm(std::shared_ptr<std::vector<double>> to_norm) {
    double sum = 0;
    for (auto value : *to_norm) {
        sum += pow(value, 2);
    }

    return sqrt(sum);
}

double error(std::shared_ptr<std::vector<double>> approximate_vector, std::shared_ptr<std::vector<double>> exact_vector) {
    auto difference_vector = std::make_shared<std::vector<double>>();

    if (approximate_vector->size() != exact_vector->size()) {
        throw "What the fuck";
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


std::shared_ptr<std::vector<double>> generate_exact_vector(std::shared_ptr<std::set<std::tuple<double,double,double>>> test_points, double (*test_function) (double, double, double)) {
//    auto exact_vector = std::make_shared<std::set<std::tuple<double,double,double>>>();
    auto exact_vector = std::make_shared<std::vector<double>>();
    for (auto point : *test_points) {
        auto x = std::get<0>(point);
        auto y = std::get<1>(point);
        auto z = std::get<2>(point);

//        auto new_coordinate = std::make_tuple(x, y, z);
        exact_vector->push_back(test_function(x,y,z));
    }
    return exact_vector;
}

double calculate_mean(std::shared_ptr<std::vector<double>> const& error_array_ptr) {
    double total = 0.0;
    auto length = error_array_ptr->size();

    for (int i = 0; i < length; i++) {
        try {
            error_array_ptr->at(i) += total;
        } catch (const std::out_of_range& e) {
            std::cout << "Exception thrown in calculate_mean" << std::endl;
        }
    }

    return (total/length);
}