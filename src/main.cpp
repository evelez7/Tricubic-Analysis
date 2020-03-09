#include "check.h"
#include "util.h"
#include <iostream>

#define SHIFT_LIMIT 10

void print_border();
void print_shift_notice();
void print_interval_notice(double);
void run_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>> const&);
void run_tests(int const& id, std::shared_ptr<std::set<std::tuple<double, double, double>>> const&);

double original_a = 0;
double original_b = 1;

int main(int argc, char** argv) {
    std::cout << "Generating " << get_num_of_test_points() << " test points" << std::endl;
    auto test_points = generate_test();

    if (argc < 2) {
        run_tests(test_points);
    } else {
        auto id = atoi(argv[1]);

        run_tests(id, test_points);
    }
}

void run_tests(int const& id, std::shared_ptr<std::set<std::tuple<double, double, double>>> const& test_points) {
    for (int i = 0; i < SHIFT_LIMIT; i++) {
        print_border();

        print_interval_notice(i);
        if (i == 0) {
            execute_single_test(id, test_points);
            continue;
        }

        print_shift_notice();
        auto shifted_points = shift_test_points(test_points, i);
        execute_single_test(id, shifted_points);
    }
}

void run_tests(std::shared_ptr<std::set<std::tuple<double, double, double>>> const& test_points) {
   for (int i = 0; i < SHIFT_LIMIT; i++) {
        print_border();
       print_interval_notice(i);
       if (i == 0) {
           execute_all_tests(test_points);
           continue;
       }

       print_shift_notice();
       auto shifted_points = shift_test_points(test_points, i);
       execute_all_tests(shifted_points);
   }
}

void print_border() {
    std::cout << std::endl;
    for (int i = 0; i < 20; i++) {
        std::cout << "*";
    }
    std::cout << std::endl << std::endl;
}

void print_shift_notice() {
    std::cout << "Shifting points to conform with new interval" << std::endl << std::endl;
}

void print_interval_notice(double new_base) {
    std::cout << "Testing on unit cube with interval [" << original_a + new_base << "," << original_b + new_base << "]" << std::endl << std::endl;
}