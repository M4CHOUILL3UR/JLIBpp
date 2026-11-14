#ifndef JLIB_TSR_H
#define JLIB_TSR_H

#include <stdexcept>

#define JLIB_TSR_NO_BEHAVIOR 0
#define JLIB_TSR_DIM_ALLOCATED 1
#define JLIB_TSR_DATA_ALLOCATED 2
#define JLIB_TSR_IS_MATRIX 4
#define JLIB_TSR_IS_VECTOR 8

namespace jlib {
    template<typename type> struct tsr {
        size_t msg;
        int order;
        int size;
        int* dim;
        type* data;

        ~tsr(); // Delete overload, cares about allocation particularity.

        int shape(int index) const; // Get dim value at index value in array.
        type& operator [] (int index); // Get data value at index in array.
        type& operator () (int *coords); // Get data at coordinate array position.
        
        void reshape_reference(int _order, int* _dim); // Reshapes dim for new possible storage of given tensor (changes allocation to not allocated).
        void reshape_newalloc(int _order, int* _dim); // Reshapes dim for new possible storage of given tensor (allocates new array).
    };

    template<typename type> tsr<type> init_empty_from_dim(int _order, int* _dim); // Zero initialised tensor with lookup dimension (delete called on data but is not called on dim).
    template<typename type> tsr<type> init_empty_standalone(int _order, int* _dim); // Zero initialised tensor with its own dimension object (delete is called on dim and data).
    template<typename type> tsr<type> init_lookup(int _order, int* _dim, type* _data); // Lookup tensor in term of values and dimension (delete is not called on dim and data).
    template<typename type> tsr<type> init_from_dim(int _order, int* _dim, type* _data); // Tensor from an existing dimension but separated data (delete called on data but is not called on dim).
    template<typename type> tsr<type> init_standalone(int _order, int* _dim, type* _data); // Every object is being allocated for that object (delete is called on dim and data).

    template<typename type> tsr<type> copy_data(tsr<type>& tensor); // Create copy with same dimension pointer (unsafe if original tensor is expired).
    template<typename type> tsr<type> copy_full(tsr<type>& tensor); // Create fully allocated copy.

    template<typename type> tsr<type> reduction(tsr<type>& tensor); // Gets rid of unnecessary dimensions and lower order if needed.
}

#include "tensor.tpp"
#endif