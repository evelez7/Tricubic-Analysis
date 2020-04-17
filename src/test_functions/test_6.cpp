#include "test_util.h"
#include "test_6.h"

double test_6::exact(double x, double y, double z) {
  return exp(pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 1.0 / 2.0));
}

double exact_dxdydz(double x, double y, double z) {
  auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

  auto num_first = 3.0 * exp(r) * x * y * z;
  auto denom_first = pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 5.0 / 2.0);
  auto first_term = num_first / denom_first;

  auto num_second = -1.0 * 3.0 * exp(r) * x * y * z;
  auto denom_second = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 2.0);
  auto second_term = num_second / denom_second;

  auto num_third = exp(r) * x * y * z;
  auto denom_third = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 3.0 / 2.0);
  auto third_term = num_third / denom_third;

  auto answer = first_term + second_term + third_term;

  if (x == 0 && y == 0 && z == 0) {
    return 0;
  }
  return answer;
}
double exact_dydz(double x, double y, double z) {
  auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

  auto num_first = exp(r) * y * z;
  auto denom_first = pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 3.0 / 2.0);
  auto first_term = num_first / denom_first;

  auto num_second = exp(r) * y * z;
  auto denom_second = pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0);
  auto second_term = num_second / denom_second;

  auto answer = first_term + second_term;

  if (x == 0 && y == 0 && z == 0) {
    return 0;
  }
  return answer;
}

double exact_dxdz(double x, double y, double z) {
  auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

  auto num_first = exp(r) * x * z;
  auto denom_first = pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 3.0 / 2.0);
  auto first_term = num_first / denom_first;

  auto num_second = exp(r) * x * z;
  auto denom_second = pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0);
  auto second_term = num_second / denom_second;

  auto answer = first_term + second_term;

  if (x == 0 && y == 0 && z == 0) {
    return 0;
  }
  return answer;
}

double exact_dxdy(double x, double y, double z) {
  auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

  auto num_first = exp(r) * x * y;
  auto denom_first = pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 3.0 / 2.0);
  auto first_term = num_first / denom_first;

  auto num_second = exp(r) * x * y;
  auto denom_second = pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0);
  auto second_term = num_second / denom_second;

  auto answer = first_term + second_term;

  if (x == 0 && y == 0 && z == 0) {
    return 0;
  }
  return answer;
}

double exact_dx(double x, double y, double z) {
  auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

  auto num = exp(r) * x;
  auto denom = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 1.0 / 2.0);

  auto answer = num / denom;
  if (x == 0 && y == 0 && z == 0) {
    return 0;
  }
  return answer;
}

double exact_dy(double x, double y, double z) {
  auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

  auto num = exp(r) * y;
  auto denom = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 1.0 / 2.0);

  auto answer = num / denom;
  if (x == 0 && y == 0 && z == 0) {
    return 0;
  }
  return answer;
}

double exact_dz(double x, double y, double z) {
  auto r = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));

  auto num = exp(r) * z;
  auto denom = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 1.0 / 2.0);

  auto answer = num / denom;
  if (x == 0 && y == 0 && z == 0) {
    return 0;
  }
  return answer;
}

std::shared_ptr<std::list<double>> test_6::interpolator(std::shared_ptr<std::set<std::tuple<double, double, double>>> const &test_points, std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> const &corners) {
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
    df_dx[i] = exact_dx(x, y, z);
    df_dy[i] = exact_dy(x, y, z);
    df_dz[i] = exact_dz(x, y, z);
    d2f_dxdy[i] = exact_dxdy(x, y, z);
    d2f_dxdz[i] = exact_dxdz(x, y, z);
    d2f_dydz[i] = exact_dydz(x, y, z);
    d3f_dxdydz[i] = exact_dxdydz(x, y, z);
  }

  tricubic_get_coeff(alpha, f, df_dx, df_dy, df_dz, d2f_dxdy, d2f_dxdz, d2f_dydz, d3f_dxdydz);
  return fill_list(alpha, test_points);
}
