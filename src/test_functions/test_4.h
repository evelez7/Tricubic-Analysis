//
//

#ifndef TRIC_ANALYSIS_TEST_4_H
#define TRIC_ANALYSIS_TEST_4_H
#include "test_util.h"

namespace test_4 {
    double exact(double, double, double);

    std::shared_ptr<std::list<double>> interpolator(std::shared_ptr<std::set<std::tuple<double, double, double>>> const&, std::shared_ptr<std::array<std::tuple<double, double, double>, 8>> const&);
}
#endif //TRIC_ANALYSIS_TEST_4_H
