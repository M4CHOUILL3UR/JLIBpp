#ifndef JLIB_VEC_T
#define JLIB_VEC_T

#include "vec.hpp"

//template<typename T, int S> jlib::vec<T, S>::vec() : data{} {}

template<typename T, int S> jlib::vec<T, S>::vec(T value) {
    std::fill(data, data + S, value);
}

template<typename T, int S> jlib::vec<T, S>::vec(int size, T* list) : data{} {
    if (size != S) {throw std::length_error("Wrong length on parameter for jlib::vec object creation.");}
    if (!list) {throw std::invalid_argument("Null pointer passed for jlib::vec object creation.");}
    std::copy(list, list + S, data);
}

template<typename T, int S> jlib::vec<T, S>::vec(std::initializer_list<T> list) : data{} {
    if (list.size() != S) {throw std::length_error("Wrong initializer list for jlib::vec object creation.");}
    std::copy(list.begin(), list.end(), data);
}

template<typename T, int S> T& jlib::vec<T, S>::operator () (int index) {
    if (index < 0 || index >= S) {throw std::out_of_range("Out of range index for jlib::vec(0 <= index < S).");}
    return this->data[index];
}

template<typename T, int S> jlib::vec<T, S> jlib::vec<T, S>::operator + (jlib::vec<T, S>& that) {
    jlib::vec<T, S> res;
    std::copy(this, this + S, res.data);
    for (int i = 0; i < S; ++i) {
        res.data[i] += that.data[i];
    }
    return res;
}

template<typename T, int S> jlib::vec<T, S> jlib::vec<T, S>::operator - (jlib::vec<T, S>& that) {
    jlib::vec<T, S> res;
    std::copy(this, this + S, res.data);
    for (int i = 0; i < S; ++i) {
        res.data[i] -= that.data[i];
    }
    return res;
}

template<typename T, int S> T jlib::vec<T, S>::operator * (jlib::vec<T, S>& that) {
    T res{};
    for (int i = 0; i < S; ++i) {
        res += this->data[i] * that.data[i];
    }
    return res;
}

template<typename T, int S> jlib::vec<T, S> jlib::vec<T, S>::operator * (T scalar) {
    if (scalar == T(0)) {
        jlib::vec<T, S> res{};
        return res;
    } else if (scalar == T(1)) {
        jlib::vec<T, S> res;
        std::copy(this, this + S, res.data);
        return res;
    } else {
        jlib::vec<T, S> res;
        for (int i = 0; i < S; ++i) {
            res.data[i] = this->data[i] * scalar;
        }
        return res;
    }
}

template<typename T, int S> jlib::vec<T, S> jlib::vec<T, S>::operator / (T scalar) {
    if (scalar == T(0)) {
        throw std::invalid_argument("Divide by zero for jlib::vec<T, S>::operator /.");
    } else if (scalar == T(1)) {
        jlib::vec<T, S> res;
        std::copy(this, this + S, res.data);
        return res;
    } else {
        jlib::vec<T, S> res;
        for (int i = 0; i < S; ++i) {
            res.data[i] = this->data[i] / scalar;
        }
        return res;
    }
}

template<typename T, int S> jlib::vec<T, S>& jlib::vec<T, S>::operator += (jlib::vec<T, S>& that) {
    for (int i = 0; i < S; ++i) {
        this->data[i] += that.data[i];
    }
    return *this;
}

template<typename T, int S> jlib::vec<T, S>& jlib::vec<T, S>::operator -= (jlib::vec<T, S>& that) {
    for (int i = 0; i < S; ++i) {
        this->data[i] -= that.data[i];
    }
    return *this;
}

template<typename T, int S> jlib::vec<T, S>& jlib::vec<T, S>::operator *= (T scalar) {
    if (scalar == T(0)) {
        for (int i = 0; i < S; ++i) {
            this->data[i] = T(0);
        }
    } else if (scalar != T(1)) {
        for (int i = 0; i < S; ++i) {
            this->data[i] *= scalar;
        }
    }
    return *this;
}

template<typename T, int S> jlib::vec<T, S>& jlib::vec<T, S>::operator /= (T scalar) {
    if (scalar == T(0)) {
        throw std::invalid_argument("Divide by zero for jlib::vec<T, S>::operator /=.");
    } else if (scalar != T(1)) {
        for (int i = 0; i < S; ++i) {
            this->data[i] /= scalar;
        }
    }
    return *this;
}

template<typename T, int S> T jlib::vec<T, S>::norm(double order) {
    T res = T(0);
    for (int i = 0; i < S; ++i) {
        res += pow(this->data[i], order);
    }
    return pow(res, 1/order);
}

#endif