#include <ardos/utils/coord_transform.h>

namespace ardos::utils {

CoordTransform::CoordTransform(long in_min, long in_max, long out_min,
                               long out_max)
    : in_min(in_min), in_max(in_max), out_min(out_min), out_max(out_max) {}

long CoordTransform::map(long value) const {
  return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

long CoordTransform::reverse(long value) const {
  return (value - out_min) * (in_max - in_min) / (out_max - out_min) + in_min;
}

} // namespace ardos::utils