#ifndef JLIB_VEC_H
#define JLIB_VEC_H

#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <cmath>

namespace jlib {
    template<typename T, int S> struct vec {
        static_assert(S > 0, "Invalid jlib::vec size parameter.");
        T data[S];

        vec() = default;
        vec(T value);
        vec(int size, T* list);
        vec(std::initializer_list<T> list);

        T& operator () (int index);

        vec operator + (vec& that);
        vec operator - (vec& that);
        T operator * (vec& that);
        vec operator * (T scalar);
        vec operator / (T scalar);

        vec& operator += (vec& that);
        vec& operator -= (vec& that);
        vec& operator *= (T scalar);
        vec& operator /= (T scalar);

        T norm(double order = 2);
    };
}

#include "vec.tpp"
#endif