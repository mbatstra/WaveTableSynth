#pragma once
#include <cmath>

using SampleFunc = float (*)(float);

namespace sf {
  inline float sin(float theta)
  {
    return std::sin(theta);
  }

  inline float square(float theta)
  {
    return 1 ? std::sin(theta) > 0 : 0;
  }

  inline float saw(float theta)
  {
  return theta - floor(theta);
  }
}
