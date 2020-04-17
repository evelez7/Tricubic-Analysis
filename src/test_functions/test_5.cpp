#include "test_util.h"
#include "test_5.h"
#include <tricubic.h>

 /**
 * f(x,y,z) = (e^-kr)/r
 *
 * @param x
 * @param y
 * @param z
 * @return
 */
auto k = 0.5;
double test_5::exact(double x, double y, double z) {
  auto r = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 1.0 / 2.0);
  auto numerator = exp(-k * r);

  auto answer = numerator / r;

  if (x == 0 && y == 0 && z == 0) {
    return 0;
  }
  return answer;
}

double control_dx(double x, double y, double z) {
  auto r = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 1.0 / 2.0);

  auto num_first = -exp(-k * r) * x;
  auto denom_first = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 3.0 / 2.0);
  auto first_term = num_first / denom_first;

  auto num_second = k * exp(-k * r) * x;
  auto denom_second = pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0);
  auto second_term = num_second / denom_second;

  auto answer = first_term - second_term;

  if (x == 0 && y == 0 && z == 0) {
    return 0;
  }
  return answer;
}

double control_dy(double x, double y, double z) {
  auto r = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 1.0 / 2.0);

  auto num_first = -exp(-k * r) * y;
  auto denom_first = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 3.0 / 2.0);
  auto first_term = num_first / denom_first;

  auto num_second = k * exp(-k * r) * y;
  auto denom_second = pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0);
  auto second_term = num_second / denom_second;

  auto answer = first_term - second_term;

  if (x == 0 && y == 0 && z == 0) {
    return 0;
  }

  return answer;
}

double control_dz(double x, double y, double z) {
  auto r = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 1.0 / 2.0);

  auto num_first = -exp(-k * r) * z;
  auto denom_first = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 3.0 / 2.0);
  auto first_term = num_first / denom_first;

  auto num_second = k * exp(-k * r) * z;
  auto denom_second = pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0);
  auto second_term = num_second / denom_second;

  auto answer = first_term - second_term;

  if (x == 0 && y == 0 && z == 0) {
    return 0;
  }

  return answer;
}

double control_dxdy(double x, double y, double z) {
  auto r = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 1.0 / 2.0);

  auto num_first = 3.0 * exp(-k * r) * x * y;
  auto denom_first = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 5.0 / 2.0);
  auto first_term = num_first / denom_first;

  auto num_second = 1.5 * exp(-k * r) * x * y;
  auto denom_second = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 2.0);
  auto second_term = num_second / denom_second;

  auto num_third = 0.25 * exp(-k * r) * x * y;
  auto denom_third = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 3.0 / 2.0);
  auto third_term = num_third / denom_third;

  auto answer = first_term + second_term + third_term;

  if (x == 0 && y == 0 && z == 0) {
    return 0;
  }
  return answer;
}

double control_dxdz(double x, double y, double z) {
  auto r = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 1.0 / 2.0);
  ;

  auto num_first = 3.0 * exp(-k * r) * x * z;
  auto denom_first = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 5.0 / 2.0);
  auto first_term = num_first / denom_first;

  auto num_second = 1.5 * exp(-k * r) * x * z;
  auto denom_second = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 2.0);
  auto second_term = num_second / denom_second;

  auto num_third = 0.25 * exp(-k * r) * x * z;
  auto denom_third = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 3.0 / 2.0);
  auto third_term = num_third / denom_third;

  auto answer = first_term + second_term + third_term;

  if (x == 0 && y == 0 && z == 0) {
    return 0;
  }
  return answer;
}

double control_dydz(double x, double y, double z) {
  auto r = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 1.0 / 2.0);

  auto num_first = 3.0 * exp(-k * r) * y * z;
  auto denom_first = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 5.0 / 2.0);
  auto first_term = num_first / denom_first;

  auto num_second = 1.5 * exp(-k * r) * y * z;
  auto denom_second = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 2.0);
  auto second_term = num_second / denom_second;

  auto num_third = 0.25 * exp(-k * r) * y * z;
  auto denom_third = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 3.0 / 2.0);
  auto third_term = num_third / denom_third;

  auto answer = first_term + second_term + third_term;

  if (x == 0 && y == 0 && z == 0) {
    return 0;
  }
  return answer;
}

double control_dxdydz(double x, double y, double z) {
  auto r = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 1.0 / 2.0);

  auto num_first = -15.0 * exp(-k * r) * x * y * z;
  auto denom_first = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 7.0 / 2.0);
  auto first_term = num_first / denom_first;

  auto num_second = -7.5 * exp(-k * r) * x * y * z;
  auto denom_second = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 3.0);
  auto second_term = num_second / denom_second;

  auto num_third = -1.5 * exp(-k * r) * x * y * z;
  auto denom_third = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 5.0 / 2.0);
  auto third_term = num_third / denom_third;

  auto num_fourth = -0.125 * exp(-k * r) * x * y * z;
  auto denom_fourth = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 2.0);
  auto fourth_term = num_fourth / denom_fourth;

  auto answer = first_term + second_term + third_term + fourth_term;

  if (x == 0 && y == 0 && z == 0) {
    return 0;
  }
  return answer;
}

std::shared_ptr<std::list<double>> test_5::interpolator(std::shared_ptr<std::set<std::tuple<double, double, double>>> const &test_points, std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> const &corners) {
  double f[8];
  double df_dx[8];
  double df_dy[8];
  double df_dz[8];
  double d2f_dxdy[8];
  double d2f_dxdz[8];
  double d2f_dydz[8];
  double d3f_dxdydz[8];

  double alpha[64];

  for (int i = 0; i < corners->size(); i++) {
    auto triple = corners->at(i);
    auto x = std::get<0>(triple);
    auto y = std::get<1>(triple);
    auto z = std::get<2>(triple);

    f[i] = exact(x, y, z);
    df_dx[i] = control_dx(x, y, z);
    df_dy[i] = control_dy(x, y, z);
    df_dz[i] = control_dz(x, y, z);
    d2f_dxdy[i] = control_dxdy(x, y, z);
    d2f_dxdz[i] = control_dxdz(x, y, z);
    d2f_dydz[i] = control_dydz(x, y, z);
    d3f_dxdydz[i] = control_dxdydz(x, y, z);
  }

  tricubic_get_coeff(alpha, f, df_dx, df_dy, df_dz, d2f_dxdy, d2f_dxdz, d2f_dydz, d3f_dxdydz);
  return fill_list(alpha, test_points);
}
