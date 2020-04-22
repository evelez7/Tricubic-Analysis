#ifndef TRIC_ANALYSIS_CORNERS_UTIL_H
#define TRIC_ANALYSIS_CORNERS_UTIL_H

#include "general_util.h"

std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> shift_corners(double const&);

corners_matrix randomize_corners(double min = 0, double max = 1);

corners_matrix reset_corners(corners_matrix);

#endif //TRIC_ANALYSIS_CORNERS_UTIL_H