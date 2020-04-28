#ifndef TRIC_ANALYSIS_CORNERS_UTIL_H
#define TRIC_ANALYSIS_CORNERS_UTIL_H

#include "general_util.h"

std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> shift_corners(double const&);

corners_matrix randomize_corners(double min = 0, double max = 1);

corners_matrix reset_corners(corners_matrix);

/**
 * \brief Determine the artificial corners of a cube around a matrix of points
 * 
 * \details Used for the enclosure strategy of creating a unit cube around 8 points
 * 
 * \param points
 * \param distance distance that the enclosure should be away from the reference points
 */
corners_matrix create_enclosure(corners_matrix const&, double const& distance = 1);

#endif //TRIC_ANALYSIS_CORNERS_UTIL_H