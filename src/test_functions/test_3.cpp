#include "test_util.h"
#include "test_3.h"
#include <tricubic.h>

/**
 * f(x,y,z) = 1/sqrt(x^2 + y^2 + z^2)
 *
 * @param x
 * @param y
 * @param z
 * @return
 */
double test_3::exact(double x, double y, double z) {
  auto denominator = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
  if (denominator == 0.0) {
    return 0;
  }
  return (1 / denominator);
}

std::shared_ptr<std::list<double>> test_3::interpolator(std::shared_ptr<std::set<std::tuple<double, double, double>>> const &test_coords, std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> const &corners) {
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

    df_dx[i] = ((-x) / (pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 3.0 / 2.0)));
    df_dy[i] = (-y / (pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 3.0 / 2.0)));
    df_dz[i] = (-z / (pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 3.0 / 2.0)));

    d2f_dxdy[i] = ((3.0 * x * y) / (pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 5.0 / 2.0)));
    d2f_dxdz[i] = ((3.0 * x * z) / (pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 5.0 / 2.0)));
    d2f_dydz[i] = ((3.0 * x * z) / (pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 5.0 / 2.0)));

    d3f_dxdydz[i] = ((-15.0 * x * y * z) / (pow((pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0)), 7.0 / 2.0)));
  }
  tricubic_get_coeff(alpha, f, df_dx, df_dy, df_dz, d2f_dxdy, d2f_dxdz, d2f_dydz, d3f_dxdydz);
  return fill_list(alpha, test_coords);
}
