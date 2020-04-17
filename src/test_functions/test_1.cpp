#include "test_util.h"
#include "test_1.h"
#include <tricubic.h>

/**
	 * f(x,y,z) = x^2 + y^2 + z^2
	 *
	 * @param x
	 * @param y
	 * @param z
	 * @return the value of f(x) @ (x,y,z) of type double
	 */
double test_1::exact(double x, double y, double z) {
  return (std::pow(x, 2.0) + std::pow(y, 2.0) + std::pow(z, 2.0));
}

/**
 * Uses function_1 as the function to approximate through tricubic interpolation
 *
 * @param test_points 
 * @return unique_ptr<double[]> an array of approximations of the same size as test_points
 */
std::shared_ptr<std::list<double>> test_1::interpolator(std::shared_ptr<std::set<std::tuple<double, double, double>>> const &test_points, std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> const &corners) {
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
    df_dx[i] = 2 * x;
    df_dy[i] = 2 * y;
    df_dz[i] = 2 * z;
    d2f_dxdy[i] = 0;
    d2f_dxdz[i] = 0;
    d2f_dydz[i] = 0;
    d3f_dxdydz[i] = 0;
  }

  tricubic_get_coeff(alpha, f, df_dx, df_dy, df_dz, d2f_dxdy, d2f_dxdz, d2f_dydz, d3f_dxdydz);

  return fill_list(alpha, test_points);
}
