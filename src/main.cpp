#include <random>
#include "check.h"

std::unique_ptr<std::set<std::tuple<double, double, double>>> generate_test_points(int);
void graph_results();

int main() {
    auto test_points = generate_test_points(100);
    execute_tests(test_points);
}
/**
 * Random number generator used to test function approximation.
 *
 * @param num_of_points the number of random points to generate
 * @return set<double> a set of triples representing (x,y,z) coordinates
 */
std::unique_ptr<std::set<std::tuple<double, double, double>>> generate_test_points(int num_of_points) {
    std::uniform_real_distribution<double> interval(0, 1); // P(i|a,b) = 1/(b-a)
    std::random_device seed; // used to ensure randomness
    std::mt19937 rng(seed()); // Mersenne Twister random number generator

    // Even if the rng repeats numbers, a set should guarantee uniqueness
    std::unique_ptr<std::set<std::tuple<double, double, double>>> test_points(new std::set<std::tuple<double, double, double>>());

    for (int i = 0; i < num_of_points; i++) {
        double x = interval(rng);
        double y = interval(rng);
        double z = interval(rng);

        auto new_coordinate = std::make_tuple(x, y, z);
        test_points->insert(new_coordinate);
    }

    return test_points;
}

