#pragma once

namespace ardos::utils {

class CoordTransform {
public:
  CoordTransform(long in_min, long in_max, long out_min, long out_max);

  long map(long value) const;
  long reverse(long value) const;

private:
  long in_min, in_max;
  long out_min, out_max;
};

} // namespace ardos::utils