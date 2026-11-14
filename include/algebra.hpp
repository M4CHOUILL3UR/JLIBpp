#ifndef JLIB_ALGEBRA_H
#define JLIB_ALGEBRA_H

#include "vec.hpp"
#include "tensor.hpp"

namespace jlib {
    using vec_2d = vec<double, 2>;
    using vec_3d = vec<double, 3>;
    using vec_4d = vec<double, 4>;
    using vec_6d = vec<double, 6>;
    using vec_9d = vec<double, 9>;

    using vec_2f = vec<float, 2>;
    using vec_3f = vec<float, 3>;
    using vec_4f = vec<float, 4>;
    using vec_6f = vec<float, 6>;
    using vec_9f = vec<float, 9>;
}

#endif