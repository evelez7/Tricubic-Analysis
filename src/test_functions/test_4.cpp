#include "test_util.h"
#include "test_4.h"
#include <tricubic.h>

/**
 * f(x,y,z) = x^2 * y^2 * z^2
 *
 * @param x
 * @param y
 * @param z
 * @return
 */
double test_4::exact(double x, double y, double z) {
  auto x_term = pow(x, 2);
  auto y_term = pow(y, 2);
  auto z_term = pow(z, 2);

  return (x_term * y_term * z_term);
}

std::shared_ptr<std::list<double>> test_4::interpolator(std::shared_ptr<std::set<std::tuple<double, double, double>>> const &test_points, std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> const &corners) {
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
    df_dx[i] = (2 * x * pow(y, 2.0) * pow(z, 2.0));
    df_dy[i] = (2 * y * pow(x, 2.0) * pow(z, 2.0));
    df_dz[i] = (2 * z * pow(x, 2.0) * pow(y, 2.0));
    d2f_dxdy[i] = (4 * x * y * pow(z, 2.0));
    d2f_dxdz[i] = (4 * z * x * pow(y, 2.0));
    d2f_dydz[i] = (4 * z * y * pow(x, 2.0));
    d3f_dxdydz[i] = (8 * x * y * z);
  }

  tricubic_get_coeff(alpha, f, df_dx, df_dy, df_dz, d2f_dxdy, d2f_dxdz, d2f_dydz, d3f_dxdydz);
  return fill_list(alpha, test_points);
}
