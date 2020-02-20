#include "test_functions.h"
#include "p.h"

#define SET_LIMIT 8

double get_cos_val(double, double, double);
double get_sin_val(double, double, double);

void execute_tests(std::set<std::tuple<double, double, double>> const* test_points) {
    double* results_1 = example_1(test_points);
}

/**
 * f(x,y,z)=x^2 + y^2 + z^2
 */
double * example_1(std::set<std::tuple<double, double, double>> const* test_points) {
    // let f(x,y,z) = x^2 + y^2 + z^2
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
double* example_2(std::set<std::tuple<double, double, double>> const* test_coords) {
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
        double x = P::points[i][0];
        double y = P::points[i][1];
        double z = P::points[i][2];
        // base f vals
        f[i] = get_sin_val(x, y, z);

        // first derivative vals
        df_dx[i] = get_cos_val(x, y, z);
        df_dy[i] = get_cos_val(x, y, z);
        df_dz[i] = get_cos_val(x, y, z);

        // second derivative vals
        d2f_dxdy[i] = -get_sin_val(x, y, z);
        d2f_dxdz[i] = -get_sin_val(x, y, z);
        d2f_dydz[i] = -get_sin_val(x, y, z);

        // third derivative val
        d3f_dxdydz[i] = -get_cos_val(x, y, z);
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
void fill_array(double alpha[64], double* approximations, std::set<std::tuple<double, double, double>> const* test_coords) {
    int i = 0;
    for (auto coord : *test_coords) {
        double x = std::get<0>(coord);
        double y = std::get<1>(coord);
        double z = std::get<2>(coord);

        *(approximations + i) = tricubic_eval(alpha, x, y, z);
    }
}

double get_cos_val(double x, double y, double z) {
    return cos(x + y + z);
}

double get_sin_val(double x, double y, double z) {
    return sin(x + y + z);
}