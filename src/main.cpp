#include "check.h"
#include "util.h"
#include <iostream>

#define SHIFT_LIMIT 10

void print_border();
void print_shift_notice(double);
double original_a = 0;
double original_b = 1;

int main() {
    std::cout << "Generating " << get_num_of_test_points() << " test points" << std::endl;
    auto test_points = generate_test();

    print_border();
    std::cout << "testing on unit cube on interval [0,1]" << std::endl << std::endl;
    run_tests(test_points);

    for (int i = 1; i < SHIFT_LIMIT; i++) {
        print_border();
        print_shift_notice(i);
        auto shifted_points = shift_test_points(test_points, i);

        run_tests(shifted_points);
    }
}

void print_border() {
    std::cout << std::endl;
    for (int i = 0; i < 20; i++) {
        std::cout << "*";
    }
    std::cout << std::endl << std::endl;
}



void print_shift_notice(double new_base) {
    std::cout << "Shifting points to conform with unit cube on interval [" << original_a + new_base << "," << original_b + new_base << "]" << std::endl;
}