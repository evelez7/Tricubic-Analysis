#ifndef TRIC_ANALYSIS_CORNERS_H
#define TRIC_ANALYSIS_CORNERS_H

namespace original_corners {
    /**
     * \brief 2D matrix for the corners of the unit cube
     *
     * \details We consider the traditional, original unit cube presented by Lekien and Marsden.
     * We identify each corner by the labels found in the tricubic technical manual in order of the definition of the matrix:
     * (0,0,0) -> p_1
     * (1,0,0) -> p_2
     * (0,1,0) -> p_3
     * (1,1,0) -> p_4
     * (0,0,1) -> p_5
     * (1,0,1) -> p_6
     * (0,1,1) -> p_7
     * (1,1,1) -> p_8
     */
    double points[8][3] = {{0.0, 0.0, 0.0},
                          {1.0, 0.0, 0.0},
                          {0.0, 1.0, 0.0},
                          {1.0, 1.0, 0.0},
                          {0.0, 0.0, 1.0},
                          {1.0, 0.0, 1.0},
                          {0.0, 1.0, 1.0},
                          {1.0, 1.0, 1.0}};

    int num_rows = 8;
    int num_columns = 3;
}

#endif //TRIC_ANALYSIS_CORNERS_H
