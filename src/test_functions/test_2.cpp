#include "test_util.h"
#include "test_2.h"
#include <tricubic.h>

namespace test_2 {
    /**
 * f(x,y,z) = sin(x+y+z)
 *
 * @param x
 * @param y
 * @param z
 * @return the value of f(x) @ (x,y,z) of type double
 */
double exact(double x, double y, double z) {
  return sin(x + y + z);
}

/**
 * f(x,y,z)=sin(x+y+z)
 */
std::shared_ptr<std::list<double>> interpolator(std::shared_ptr<std::set<std::tuple<double, double, double>>> const &test_coords, std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> const& corners) {
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
  for (int i = 0; i < corners->size(); i++) {
    auto triple = corners->at(i);
    auto x = std::get<0>(triple);
    auto y = std::get<1>(triple);
    auto z = std::get<2>(triple);

    // base f vals
    f[i] = sin(x + y + z);

    // first derivative vals
    df_dx[i] = cos(x + y + z);
    df_dy[i] = cos(x + y + z);
    df_dz[i] = cos(x + y + z);

    // second derivative vals
    d2f_dxdy[i] = -sin(x + y + z);
    d2f_dxdz[i] = -sin(x + y + z);
    d2f_dydz[i] = -sin(x + y + z);

    // third derivative val
    d3f_dxdydz[i] = -cos(x + y + z);
  }

  tricubic_get_coeff(alpha, f, df_dx, df_dy, df_dz, d2f_dxdy, d2f_dxdz, d2f_dydz, d3f_dxdydz);

  return fill_list(alpha, test_coords);
}
}