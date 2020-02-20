//
// Created by Erick Velez on 2/17/20.
//

#ifndef TRIC_EXAMPLE_P_H
#define TRIC_EXAMPLE_P_H

namespace P {

    float points[8][3] = {{0, 0, 0},
                     {1, 0, 0},
                     {0, 1, 0},
                     {1, 1, 0},
                     {0, 0, 1},
                     {1, 0, 1},
                     {0, 1, 1},
                     {1, 1, 1}};

    int num_rows = 8;
    int num_columns = 8;
}
/**
 * Let P be the set of points given by the cube and needed to compute the b vector described as am 8x3 matrix
 *
 * The order is described in example1 in libtricubic-1.0/src
 */
#endif //TRIC_EXAMPLE_P_H
