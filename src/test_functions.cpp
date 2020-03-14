#include "test_functions.h"
#include "corners.h"
#include "util.h"
#include <iostream>

#define SET_LIMIT 8
#define NUM_OF_TESTS 6

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
 * f(x,y,z) = 1/sqrt(x^2 + y^2 + z^2)
 *
 * @param x
 * @param y
 * @param z
 * @return
 */
double function_3(double x, double y, double z) {
    auto denominator = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    if (denominator == 0.0) {
        return 0;
    }
    return (1/denominator);
}

/**
 * f(x,y,z) = x^2 * y^2 * z^2
 *
 * @param x
 * @param y
 * @param z
 * @return
 */
double function_4(double x, double y, double z) {
    auto x_term = pow(x, 2);
    auto y_term = pow(y, 2);
    auto z_term = pow(z, 2);

    return (x_term * y_term * z_term);
}

/**
 * f(x,y,z) = (e^-kr)/r
 *
 * @param x
 * @param y
 * @param z
 * @return
 */
auto k = 0.5;
double function_5(double x, double y, double z) {
    auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

    auto numerator = exp((-1.0*k)*r);

    auto answer = numerator/r;

    if (x == 0 && y == 0 && z == 0) {
        return 0;
    }
    return answer;
}

double function_5_dx(double x, double y, double z) {
    auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

    auto num_first_term = -1.0*exp(-1.0*k*r)*x;
    auto denom_first_term = pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 3.0/2.0);
    auto first_term = num_first_term/denom_first_term;

    auto num_second = exp(-1.0*k*r) * k * x;
    auto denom_second = pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0);
    auto second_term = num_second/denom_second;

    auto answer = first_term - second_term;

    if (x == 0 && y == 0 && z == 0) {
        return 0;
    }
    return answer;
}

double function_5_dy(double x, double y, double z) {
    auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

    auto num_first_term = -1.0*exp(-1.0*k*r)*y;
    auto denom_first_term = pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 3.0/2.0);
    auto first_term = num_first_term/denom_first_term;

    auto num_second = exp(-1.0*k*r) * k * y;
    auto denom_second = pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0);
    auto second_term = num_second/denom_second;

    auto answer = first_term - second_term;

    if (x == 0 && y == 0 && z == 0) {
        return 0;
    }
    return answer;
}

double function_5_dz(double x, double y, double z) {
    auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

    auto num_first_term = -1.0*exp(-1*k*r)*z;
    auto denom_first_term = pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 3.0/2.0);
    auto first_term = num_first_term/denom_first_term;

    auto num_second = exp(-1.0*k*r) * k * z;
    auto denom_second = pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0);
    auto second_term = num_second/denom_second;

    auto answer = first_term - second_term;

    if (x == 0 && y == 0 && z == 0) {
        return 0;
    }
    return answer;
}

double function_5_dxdy(double x, double y, double z) {
    auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

    auto num_first = 3.0*exp(-1*k*r)*x*y;
    auto denom_first = pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 5.0/2.0);
    auto first_term = num_first/denom_first;

    auto num_second = 3.0 * exp(-1*k*r) * k * x * y;
    auto denom_second = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 2.0);
    auto second_term = num_second/denom_second;

    auto num_third = exp(-1.0*k*r) * pow(k, 2.0) * x * y;
    auto denom_third = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 3.0/2.0);
    auto third_term = num_third/denom_third;

    auto answer = first_term + second_term + third_term;

    if (x == 0 && y == 0 && z == 0) {
        return 0;
    }
    return answer;
}

double function_5_dxdz(double x, double y, double z) {
    auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

    auto num_first = 3.0*exp(-1*k*r) * x * z;
    auto denom_first = pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 5.0/2.0);
    auto first_term = num_first/denom_first;

    auto num_second = 3.0 * exp(-1*k*r) * k * x * z;
    auto denom_second = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 2.0);
    auto second_term = num_second/denom_second;

    auto num_third = exp(-1*k*r) * pow(k, 2.0) * x * z;
    auto denom_third = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 3.0/2.0);
    auto third_term = num_third/denom_third;

    auto answer = first_term + second_term + third_term;

    if (x == 0 && y == 0 && z == 0) {
        return 0;
    }
    return answer;
}

double function_5_dydz(double x, double y, double z) {
    auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

    auto num_first = 3.0*exp(-1*k*r) * y * z;
    auto denom_first = pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 5.0/2.0);
    auto first_term = num_first/denom_first;

    auto num_second = 3.0 * exp(-1*k*r) * k * y * z;
    auto denom_second = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 2.0);
    auto second_term = num_second/denom_second;

    auto num_third = exp(-1*k*r) * pow(k, 2.0) * y * z;
    auto denom_third = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 3.0/2.0);
    auto third_term = num_third/denom_third;

    auto answer = first_term + second_term + third_term;

    if (x == 0 && y == 0 && z == 0) {
        return 0;
    }
    return answer;
}

double function_5_dxdydz(double x, double y, double z) {
    auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

    auto num_first = -1.0*15.0*exp(-1*k*r) * x * y * z;
    auto denom_first = pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 7.0/2.0);
    auto first_term = num_first/denom_first;

    auto num_second = -1.0 * 15.0 * exp(-1*k*r) * k * x * y * z;
    auto denom_second = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 3.0);
    auto second_term = num_second/denom_second;

    auto num_third = -1 * 6.0 * exp(-1*k*r) * pow(k, 2.0) * x * y * z;
    auto denom_third = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 5.0/2.0);
    auto third_term = num_third/denom_third;

    auto num_fourth = -1 * exp(-1 * k * r) * pow(k, 3.0) * x * y * z;
    auto denom_fourth = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 2.0);
    auto fourth_term = num_fourth/denom_fourth;

    auto answer = first_term + second_term + third_term + fourth_term;

    if (x == 0 && y == 0 && z == 0) {
        return 0;
    }
    return answer;
}

double function_6(double x, double y, double z) {
    return exp(pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 1.0/2.0));
}

double function_6_dxdydz(double x, double y, double z) {
    auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

    auto num_first = 3.0*exp(r) * x * y * z;
    auto denom_first = pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 5.0/2.0);
    auto first_term = num_first/denom_first;

    auto num_second = -1.0 * 3.0 * exp(r) * x * y * z;
    auto denom_second = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 2.0);
    auto second_term = num_second/denom_second;

    auto num_third = exp(r) * x * y * z;
    auto denom_third = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 3.0/2.0);
    auto third_term = num_third/denom_third;

    auto answer = first_term + second_term + third_term;

    if (x == 0 && y == 0 && z == 0) {
        return 0;
    }
    return answer;
}
double function_6_dydz(double x, double y, double z) {
    auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

    auto num_first = exp(r) * y * z;
    auto denom_first = pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 3.0/2.0);
    auto first_term = num_first/denom_first;

    auto num_second = exp(r) *  y * z;
    auto denom_second = pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0);
    auto second_term = num_second/denom_second;

    auto answer = first_term + second_term;

    if (x == 0 && y == 0 && z == 0) {
        return 0;
    }
    return answer;
}

double function_6_dxdz(double x, double y, double z) {
    auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

    auto num_first = exp(r) * x * z;
    auto denom_first = pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 3.0/2.0);
    auto first_term = num_first/denom_first;

    auto num_second = exp(r) *  x * z;
    auto denom_second = pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0);
    auto second_term = num_second/denom_second;

    auto answer = first_term + second_term;

    if (x == 0 && y == 0 && z == 0) {
        return 0;
    }
    return answer;
}

double function_6_dxdy(double x, double y, double z) {
    auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

    auto num_first = exp(r) * x * y;
    auto denom_first = pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 3.0/2.0);
    auto first_term = num_first/denom_first;

    auto num_second = exp(r) *  x * y;
    auto denom_second = pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0);
    auto second_term = num_second/denom_second;

    auto answer = first_term + second_term;

    if (x == 0 && y == 0 && z == 0) {
        return 0;
    }
    return answer;
}


double function_6_dx(double x, double y, double z) {
    auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

    auto num = exp(r) * x;
    auto denom = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 1.0/2.0);

    auto answer = num/denom;
    if (x == 0 && y == 0 && z == 0) {
        return 0;
    }
    return answer;
}

double function_6_dy(double x, double y, double z) {
    auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

    auto num = exp(r) * y;
    auto denom = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 1.0/2.0);

    auto answer = num/denom;
    if (x == 0 && y == 0 && z == 0) {
        return 0;
    }
    return answer;
}

double function_6_dz(double x, double y, double z) {
    auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

    auto num = exp(r) * z;
    auto denom = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 1.0/2.0);

    auto answer = num/denom;
    if (x == 0 && y == 0 && z == 0) {
        return 0;
    }
    return answer;
}
/**
 * f(x,y,z) = sin(x^2 + y^2 + z^2)
 *
 * @param x
 * @param y
 * @param z
 * @return
 */
//double function_5(double x, double y, double z) {
//    auto x_term = pow(x, 2.0);
//    auto y_term = pow(y, 2.0);
//    auto z_term = pow(z, 2.0);
//
//    return sin(x + y +z);
//}

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
    auto approximations_ptr = std::make_shared<std::vector<double>>();
    approximations_ptr->reserve(test_coords->size());
//
//    for (auto coord : *test_coords) {
//        double x = std::get<0>(coord);
//        double y = std::get<1>(coord);
//        double z = std::get<2>(coord);
//
//        std::cout << "approx: " << tricubic_eval(alpha, x, y, z) << std::endl;
//        std::cout << "exact: " << function_2(x, y, z) << std::endl;
//        std::cout << " coord: (" << x << "," << y << "," << z << std::endl << std::endl;
//    }

    return fill_array(alpha, test_coords);
}

std::shared_ptr<std::vector<double>> test_function_3(std::shared_ptr<std::set<std::tuple<double, double, double>>> const& test_coords) {
    double f[8];
    double df_dx[8];
    double df_dy[8];
    double df_dz[8];
    double d2f_dxdy[8];
    double d2f_dxdz[8];
    double d2f_dydz[8];
    double d3f_dxdydz[8];

    double alpha[64];

    for (int i = 0; i < SET_LIMIT; i++) {
        double x = corners::points[i][0];
        double y = corners::points[i][1];
        double z = corners::points[i][2];

        f[i] = function_3(x, y, z);
        df_dx[i] = ((-1*x)/(pow((pow(x,2.0) + pow(y,2.0) + pow(z,2.0)), 3.0/2.0)));
        df_dy[i] =(-y/(pow((pow(x,2.0) + pow(y,2.0) + pow(z,2.0)), 7.0/2.0)));
        df_dz[i] =(-z/(pow((pow(x,2.0) + pow(y,2.0) + pow(z,2.0)), 7.0/2.0)));
        d2f_dxdy[i] = ((3.0*x*y)/(pow((pow(x,2.0) + pow(y,2.0) + pow(z,2.0)), 5.0/2.0)));
        d2f_dxdz[i] = ((3.0*x*z)/(pow((pow(x,2.0) + pow(y,2.0) + pow(z,2.0)), 5.0/2.0)));
        d2f_dydz[i] = ((3.0*x*z)/(pow((pow(x,2.0) + pow(y,2.0) + pow(z,2.0)), 5.0/2.0)));
        d3f_dxdydz[i] = ((-15.0*x*y*z)/(pow((pow(x,2.0) + pow(y, 2.0) + pow(z,2.0)), 7.0/2.0)));
    }
    tricubic_get_coeff(alpha, f, df_dx, df_dy, df_dz, d2f_dxdy, d2f_dxdz, d2f_dydz,d3f_dxdydz);
    return fill_array(alpha, test_coords);
}

std::shared_ptr<std::vector<double>> test_function_4(std::shared_ptr<std::set<std::tuple<double, double, double>>> const& test_points) {
    double f[8];
    double df_dx[8];
    double df_dy[8];
    double df_dz[8];
    double d2f_dxdy[8];
    double d2f_dxdz[8];
    double d2f_dydz[8];
    double d3f_dxdydz[8];

    double alpha[64];

    for (int i = 0; i < SET_LIMIT; i++) {
        double x = corners::points[i][0];
        double y = corners::points[i][1];
        double z = corners::points[i][2];

        f[i] = function_4(x, y, z);
        df_dx[i] = (2 * x * pow(y, 2.0) * pow(z, 2.0));
        df_dy[i] = (2 * y * pow(x, 2.0) * pow(z, 2.0));
        df_dz[i] = (2 * z * pow(x, 2.0) * pow(y, 2.0));
        d2f_dxdy[i] = (4 * x * y * pow(z, 2.0));
        d2f_dxdz[i] = (4 * z * x * pow(y, 2.0));
        d2f_dydz[i] = (4 * z * y * pow(x, 2.0));
        d3f_dxdydz[i] = (8 * x * y * z);
    }

    tricubic_get_coeff(alpha, f, df_dx, df_dy, df_dz, d2f_dxdy, d2f_dxdz, d2f_dydz,d3f_dxdydz);
    return fill_array(alpha, test_points);
}

std::shared_ptr<std::vector<double>> test_function_5(std::shared_ptr<std::set<std::tuple<double, double, double>>> const& test_points) {
    double f[8];
    double df_dx[8];
    double df_dy[8];
    double df_dz[8];
    double d2f_dxdy[8];
    double d2f_dxdz[8];
    double d2f_dydz[8];
    double d3f_dxdydz[8];

    double alpha[64];

    for (int i = 0; i < SET_LIMIT; i++) {
        double x = corners::points[i][0];
        double y = corners::points[i][1];
        double z = corners::points[i][2];

        x =

        f[i] = function_5(x, y, z);
        df_dx[i] = function_5_dx(x, y, z);
        df_dy[i] = function_5_dy(x, y, z);
        df_dz[i] = function_5_dz(x, y, z);
        d2f_dxdy[i] = function_5_dxdy(x, y, z);
        d2f_dxdz[i] = function_5_dxdz(x, y, z);
        d2f_dydz[i] = function_5_dydz(x, y, z);
        d3f_dxdydz[i] = function_5_dxdydz(x, y, z);
    }

    tricubic_get_coeff(alpha, f, df_dx, df_dy, df_dz, d2f_dxdy, d2f_dxdz, d2f_dydz,d3f_dxdydz);
    return fill_array(alpha, test_points);
}

std::shared_ptr<std::vector<double>> test_function_6(std::shared_ptr<std::set<std::tuple<double, double, double>>> const& test_points) {
    double f[8];
    double df_dx[8];
    double df_dy[8];
    double df_dz[8];
    double d2f_dxdy[8];
    double d2f_dxdz[8];
    double d2f_dydz[8];
    double d3f_dxdydz[8];

    double alpha[64];

    for (int i = 0; i < SET_LIMIT; i++) {
        double x = corners::points[i][0];
        double y = corners::points[i][1];
        double z = corners::points[i][2];

        f[i] = function_5(x, y, z);
        df_dx[i] = function_5_dx(x, y, z);
        df_dy[i] = function_5_dy(x, y, z);
        df_dz[i] = function_5_dz(x, y, z);
        d2f_dxdy[i] = function_5_dxdy(x, y, z);
        d2f_dxdz[i] = function_5_dxdz(x, y, z);
        d2f_dydz[i] = function_5_dydz(x, y, z);
        d3f_dxdydz[i] = function_5_dxdydz(x, y, z);
    }

    tricubic_get_coeff(alpha, f, df_dx, df_dy, df_dz, d2f_dxdy, d2f_dxdz, d2f_dydz,d3f_dxdydz);
    return fill_array(alpha, test_points);
}
//
//std::shared_ptr<std::vector<double>> test_function_5(std::shared_ptr<std::set<std::tuple<double, double, double>>> const& test_points) {
//    double f[8];
//    double df_dx[8];
//    double df_dy[8];
//    double df_dz[8];
//    double d2f_dxdy[8];
//    double d2f_dxdz[8];
//    double d2f_dydz[8];
//    double d3f_dxdydz[8];
//
//    double alpha[64];
//
//    for (int i = 0; i < SET_LIMIT; i++) {
//        double x = corners::points[i][0];
//        double y = corners::points[i][1];
//        double z = corners::points[i][2];
//
//        f[i] = function_5(x, y, z);
////        df_dx[i] = (2*x) * cos(pow(x,2.0) * pow(y, 2.0) )
//    }
//}

/**
 * Fill a
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
    return NUM_OF_TESTS;
}

std::string get_function_name(int const& id) {
    switch(id) {
        case 0: {
            return "x^2 + y^2 + z^2";
        }
        case 1: {
            return "sin(x + y + z";
        }
        case 2: {
            return "1/sqrt(x^2 + y^2 + z^2";
        }
        case 3: {
            return "x^2 + y^2 + z^2";
        }
        case 4: {
            return "(e^(-kr))/r";
        }
        case 5: {
            return "e^(x^2 + y^2 + z^2)^1/2";
        }
        default: {
            throw std::exception();
        }
    }
}

std::tuple<interpolator, control_function> get_function_pair(int const& id) {
    switch(id) {
        case 0: {
            return std::make_tuple(test_function_1, function_1);
        }
        case 1: {
            return std::make_tuple(test_function_2, function_2);
        }
        case 2: {
            return std::make_tuple(test_function_3, function_3);
        }
        case 3: {
            return std::make_tuple(test_function_4, function_4);
        }
        case 4: {
            return std::make_tuple(test_function_5, function_5);
        }
        case 5: {
            return std::make_tuple(test_function_6, function_6);
        }
        default: {
            throw std::exception();
        }
    }
}