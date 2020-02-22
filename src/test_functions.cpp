#include "test_functions.h"
#include "corners.h"

#define SET_LIMIT 8

void fill_array(double*, double*, std::set<std::tuple<double, double, double>> const*);

double function_1(double x, double y, double z) {
    return (std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
}

double function_2(double x, double y, double z) {
    return sin(x+y+z);
}

/**
 * f(x,y,z)=x^2 + y^2 + z^2
 */
double* test_function_1(std::set<std::tuple<double, double, double>> const* test_points) {
    double f[8] = {0, 1, 1, 2, 1, 2, 2, 3};
    double df_dx[8] = {0, 2, 0, 2, 0, 2, 0, 2};
    double df_dy[8] = {0, 0, 2, 2, 0, 0, 2, 2};
    double df_dz[8] = {0, 0, 0, 0, 2, 2, 2, 2};
    double d2f_dxdy[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    double d2f_dxdz[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    double d2f_dydz[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    double d3f_dxdydz[8] = {0, 0, 0, 0, 0, 0, 0};

    double alpha[64];
    auto* approximations = new double[test_points->size()];

    tricubic_get_coeff(alpha, f, df_dx, df_dy, df_dz, d2f_dxdy, d2f_dxdz, d2f_dydz, d3f_dxdydz);

    fill_array(alpha, approximations, test_points);

    return approximations;
}

/**
 * f(x,y,z)=sin(x+y+z)
 */
double* test_function_2(std::set<std::tuple<double, double, double>> const* test_coords) {
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
    auto* approximations = new double[test_coords->size()];

    fill_array(alpha, approximations, test_coords);
    return approximations;
}

/**
 *
 * @param alpha Vector of size 64 containing the coefficients of the interpolater
 * @param approximations
 * @param test_coords
 */
void fill_array(double* alpha, double* approximations, std::set<std::tuple<double, double, double>> const* test_coords) {
    int i = 0;
    for (auto coord : *test_coords) {
        double x = std::get<0>(coord);
        double y = std::get<1>(coord);
        double z = std::get<2>(coord);

        *(approximations + i) = tricubic_eval(alpha, x, y, z);
    }
}