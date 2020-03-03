#include <iostream>
#include "test_functions.h"
#include "corners.h"
#define SET_LIMIT 8

std::shared_ptr<std::vector<double>> fill_array(double*, std::shared_ptr<std::set<std::tuple<double, double, double>>> const&);

/**
 * f(x,y,z) = x^2 + y^2 + z^2
 *
 * @param x
 * @param y
 * @param z
 * @return the value of f(x) @ (x,y,z) of type double
 */
double function_1(double x, double y, double z) {
    return (std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
}

/**
 * f(x,y,z) = sin(x+y+z)
 *
 * @param x
 * @param y
 * @param z
 * @return the value of f(x) @ (x,y,z) of type double
 */
double function_2(double x, double y, double z) {
    return sin(x+y+z);
}

/**
 * Uses function_1 as the function to approximate through tricubic interpolation
 *
 * @param test_points 
 * @return unique_ptr<double[]> an array of approximations of the same size as test_points
 */
std::shared_ptr<std::vector<double>> test_function_1(std::shared_ptr<std::set<std::tuple<double, double, double>>> const& test_points) {
    double f[8] = {0, 1, 1, 2, 1, 2, 2, 3};
    double df_dx[8] = {0, 2, 0, 2, 0, 2, 0, 2};
    double df_dy[8] = {0, 0, 2, 2, 0, 0, 2, 2};
    double df_dz[8] = {0, 0, 0, 0, 2, 2, 2, 2};
    double d2f_dxdy[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    double d2f_dxdz[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    double d2f_dydz[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    double d3f_dxdydz[8] = {0, 0, 0, 0, 0, 0, 0};

    double alpha[64];

    tricubic_get_coeff(alpha, f, df_dx, df_dy, df_dz, d2f_dxdy, d2f_dxdz, d2f_dydz, d3f_dxdydz);

    return fill_array(alpha, test_points);
}

/**
 * f(x,y,z)=sin(x+y+z)
 */
std::shared_ptr<std::vector<double>> test_function_2(std::shared_ptr<std::set<std::tuple<double, double, double>>> const& test_coords) {
    double f[8];
    double df_dx[8];
    double df_dy[8];
    double df_dz[8];
    double d2f_dxdy[8];
    double d2f_dxdz[8];
    double d2f_dydz[8];
    double d3f_dxdydz[8];

    double alpha[64];

    // get base f values
    for (int i = 0; i < SET_LIMIT; i++) {
        double x = corners::points[i][0];
        double y = corners::points[i][1];
        double z = corners::points[i][2];
        // base f vals
        f[i] = sin(x+y+z);

        // first derivative vals
        df_dx[i] = cos(x+y+z);
        df_dy[i] = cos(x+y+z);
        df_dz[i] = cos(x+y+z);

        // second derivative vals
        d2f_dxdy[i] = -sin(x+y+z);
        d2f_dxdz[i] = -sin(x+y+z);
        d2f_dydz[i] = -sin(x+y+z);

        // third derivative val
        d3f_dxdydz[i] = -cos(x+y+z);
    }

    tricubic_get_coeff(alpha, f, df_dx, df_dy, df_dz, d2f_dxdy, d2f_dxdz, d2f_dydz,d3f_dxdydz);

    return fill_array(alpha, test_coords);
}

/**
 *
 * @param alpha Vector of size 64 containing the coefficients of the interpolater
 * @param approximations
 * @param test_coords
 */
std::shared_ptr<std::vector<double>> fill_array(double* alpha, std::shared_ptr<std::set<std::tuple<double, double, double>>> const& test_points) {
    auto approximations_ptr = std::make_shared<std::vector<double>>();
    approximations_ptr->reserve(test_points->size());

    for (auto coord : *test_points) {
        double x = std::get<0>(coord);
        double y = std::get<1>(coord);
        double z = std::get<2>(coord);

        approximations_ptr->push_back(tricubic_eval(alpha, x, y, z));
    }

    return approximations_ptr;
}

int get_num_of_tests() {
    return 2;
}