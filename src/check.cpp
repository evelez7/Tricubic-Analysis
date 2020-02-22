#include "check.h"
#include "test_functions.h"

std::unique_ptr<double[]> execute_tests(std::unique_ptr<std::set<std::tuple<double, double, double>>> const& test_points) {
    test_1(test_points);
}

std::unique_ptr<double[]> test_1(std::unique_ptr<std::set<std::tuple<double, double, double>>> const& test_points) {
    std::unique_ptr<double[]> error_values(new double[test_points->size()]);

    for (auto coord_triple : *test_points) {
        auto x = std::get<0>(coord_triple);
        auto y = std::get<1>(coord_triple);
        auto z = std::get<2>(coord_triple);


    }
}

