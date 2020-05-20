#include "test_util.h"
#include "../util/general_util.h"

#include <iostream>
#include <list>
#include "test_1.h"
#include "test_2.h"
#include "test_3.h"
#include "test_4.h"
#include "test_5.h"
#include "test_6.h"
#define NUM_OF_TESTS 6

std::shared_ptr<std::list<double>> fill_list(double *alpha, set_of_double_triples const &test_points) {
  auto approx_ptr = std::make_shared<std::list<double>>();

  for (auto point : *test_points) {
    double x = std::get<0>(point);
    double y = std::get<1>(point);
    double z = std::get<2>(point);

    auto result = tricubic_eval(alpha, x, y, z);

    approx_ptr->push_back(result);
  }

  return approx_ptr;
}

int get_num_of_tests() {
  return NUM_OF_TESTS;
}

std::string get_function_name(int const &id) {
  switch (id) {
  case 0: {
    return "x^2 + y^2 + z^2";
  }
  case 1: {
    return "sin(x + y + z";
  }
  case 2: {
    return "1/sqrt(x^2 + y^2 + z^2";
  }
  case 3: {
    return "x^2 * y^2 * z^2";
  }
  case 4: {
    return "(e^(-kr))/r";
  }
  case 5: {
    return "e^(x^2 + y^2 + z^2)^1/2";
  }
  default: {
    throw std::exception();
  }
  }
}

/**
 * @brief Returns the appropriate function pair for a certain test
 *
 * @param id
 * @return a 2-ple of type <interpolator, exact>, both pointers to functions
 */
std::tuple<interpolator, exact> get_function_pair(int const &id) {
    switch (id) {
        case 0: {
            return std::make_tuple(test_1::interpolator, test_1::exact);
        }
        case 1: {
            return std::make_tuple(test_2::interpolator, test_2::exact);
        }
        case 2: {
            return std::make_tuple(test_3::interpolator, test_3::exact);
        }
        case 3: {
            return std::make_tuple(test_4::interpolator, test_4::exact);
        }
        case 4: {
            return std::make_tuple(test_5::interpolator, test_5::exact);
        }
        case 5: {
            return std::make_tuple(test_6::interpolator, test_6::exact);
        }
        default: {
            throw std::exception();
        }
    }
}