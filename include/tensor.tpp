#include <tensor.hpp>


// Outside of header, checks if dimension is correctly defined.
int dimension_checkup(int _order, int* _dim) {
    int result = 1;
    if (_order <= 0) {
        throw std::range_error("Invalid order for tensor initialization.\n");
    }
    for (int i = 0; i < _order; ++i) {
        if (_dim[i] <= 0) {
            throw std::range_error("Invalid dimension size for tensor initialization.\n");
        } else {
            result *= _dim[i];
        }
    }
    return result;
}

// Outside of header, recognize shapes of tensor.
size_t shape_recognition(int _order, int* _dim) {
    size_t result = JLIB_TSR_NO_BEHAVIOR;
    if (_order == 1) {
        result |= JLIB_TSR_IS_VECTOR;
    } else if (_order == 2) {
        result |= JLIB_TSR_IS_MATRIX;
    }
    return result;
}

// Delete overload, cares about allocation particularity.
template<typename type> jlib::tsr<type>::~tsr() {
    if (msg & JLIB_TSR_DIM_ALLOCATED) {delete[] dim;}
    if (msg & JLIB_TSR_DATA_ALLOCATED) {delete[] data;}
}

// Get dim value at index value in array.
template<typename type> int jlib::tsr<type>::shape(int index) const {
    if (index < 0 || index >= this->order) {
        throw std::range_error("Index out of range for dimension access in tensor.\n");
    }
    return this->dim[index];
}

// Get data value at index in array.
template<typename type> type& jlib::tsr<type>::operator [] (int index) {
    if (index < 0 || index >= this->size) {
        throw std::range_error("Index out of range for data access in tensor.\n");
    }
    return this->data[index];
}

// Get data at coordinate array position.
template<typename type> type& jlib::tsr<type>::operator () (int* coords) {
    int index = coords[0];
    for (int i = 1; i < this->order; ++i) {
        index *= this->shape[i];
        index += coords[i];
    }
    return this->data[index];
}

// Reshapes dim for new possible storage of given tensor.
template<typename type> void jlib::tsr<type>::reshape_reference(int _order, int* _dim) {
    int newsize = dimension_checkup(_order, _dim);
    if(this->size == newsize) {
        this->msg = (this->msg & JLIB_TSR_DATA_ALLOCATED) | shape_recognition(_order, _dim);
        this->order = _order;
        this->size = newsize;
        this->dim = _dim;
    } else {
        throw std::range_error("Reshape invalid on tensor.\n");
    }
}

// Reshapes dim for new possible storage of given tensor (allocates new array).
template<typename type> void jlib::tsr<type>::reshape_newalloc(int _order, int* _dim) {
    int newsize = dimension_checkup(_order, _dim);
    if(this->size == newsize) {
        this->order = _order;
        this->size = newsize;
        if (this->msg & JLIB_TSR_DIM_ALLOCATED) {
            delete[] this->dim;
            this->dim = nullptr;
        }
        this->dim = new type[_order];
        for (int i = 0; i < _order; ++i) {
            this->dim[i] = _dim[i];
        }
        this->msg = (this->msg & JLIB_TSR_DATA_ALLOCATED) | JLIB_TSR_DIM_ALLOCATED | shape_recognition(_order, _dim);
    }
}

// Zero initialised tensor with lookup dimension (delete called on data but is not called on dim).
template<typename type> jlib::tsr<type> jlib::init_empty_from_dim(int _order, int* _dim) {
    jlib::tsr<type> result;
    result.msg = JLIB_TSR_DATA_ALLOCATED | shape_recognition(_order, _dim);
    result.order = _order;
    result.size = dimension_checkup(_order, _dim);
    result.dim = _dim;
    result.data = new type[result.size]();
    return result;
}

// Zero initialised tensor with its own dimension object (delete is called on dim and data).
template<typename type> jlib::tsr<type> jlib::init_empty_standalone(int _order, int* _dim) {
    jlib::tsr<type> result;
    result.msg = JLIB_TSR_DATA_ALLOCATED | JLIB_TSR_DIM_ALLOCATED | shape_recognition(_order, _dim);
    result.order = _order;
    result.size = dimension_checkup(_order, _dim);
    result.dim = new type[_order];
    result.data = new type[result.size]();
    for (int i = 0; i < _order; ++i) {
        result.dim[i] = _dim[i];
    }
    return result;
}

// Lookup tensor in term of values and dimension (delete is not called on dim and data).
template<typename type> jlib::tsr<type> jlib::init_lookup(int _order, int* _dim, type* _data) {
    jlib::tsr<type> result;
    result.msg = shape_recognition(_order, _dim);
    result.order = _order;
    result.size = dimension_checkup(_order, _dim);
    result.dim = _dim;
    result.data = _data;
    return result;
}

// Tensor from an existing dimension but separated data (delete called on data but is not called on dim).
template<typename type> jlib::tsr<type> jlib::init_from_dim(int _order, int* _dim, type* _data) {
    jlib::tsr<type> result;
    result.msg = JLIB_TSR_DATA_ALLOCATED  | shape_recognition(_order, _dim);
    result.order = _order;
    result.size = dimension_checkup(_order, _dim);
    result.dim = _dim;
    result.data = new type[result.size];
    for (int i = 0; i < result.size; ++i) {
        result.data[i] = _data[i];
    }
    return result;
}

// Every object is being allocated for that object (delete is called on dim and data).
template<typename type> jlib::tsr<type> jlib::init_standalone(int _order, int* _dim, type* _data) {
    jlib::tsr<type> result;
    result.msg = JLIB_TSR_DATA_ALLOCATED | JLIB_TSR_DIM_ALLOCATED | shape_recognition(_order, _dim);
    result.order = _order;
    result.size = dimension_checkup(_order, _dim);
    result.dim = new type[_order];
    result.data = new type[result.size];
    for (int i = 0; i < _order; ++i) {
        result.dim[i] = _dim[i];
    }
    for (int i = 0; i < result.size; ++i) {
        result.data[i] = _data[i];
    }
    return result;
}

// Create copy with same dimension pointer (unsafe if original tensor is expired).
template<typename type> jlib::tsr<type> jlib::copy_data(jlib::tsr<type>& tensor) {
    jlib::tsr<type> result;
    result.msg = JLIB_TSR_DATA_ALLOCATED | shape_recognition(tensor.order, tensor.dim);
    result.order = tensor.order;
    result.size = tensor.size;
    result.dim = tensor.dim;
    result.data = new type[result.size];
    for (int i = 0; i < result.size; ++i) {
        result.data[i] = tensor.data[i];
    }
    if (result.order == 1) {
        result.msg |= JLIB_TSR_IS_VECTOR;
    } else if (result.order == 2) {
        result.msg |= JLIB_TSR_IS_MATRIX;
    }
    return result;
}

// Create fully allocated copy.
template<typename type> jlib::tsr<type> jlib::copy_full(jlib::tsr<type>& tensor) {
    jlib::tsr<type> result;
    result.msg = JLIB_TSR_DATA_ALLOCATED | JLIB_TSR_DIM_ALLOCATED  | shape_recognition(tensor.order, tensor.dim);
    result.order = tensor.order;
    result.size = tensor.size;
    result.dim = new type[tensor.order];
    result.data = new type[result.size];
    for (int i = 0; i < result.order; ++i) {
        result.dim[i] = tensor.dim[i];
    }
    for (int i = 0; i < result.size; ++i) {
        result.data[i] = tensor.data[i];
    }
    return result;
}

// Gets rid of unnecessary dimensions and lower order if needed.
template<typename type> jlib::tsr<type> jlib::reduction(jlib::tsr<type>& tensor) {
    int neworder = 0;
    for (int i = 0; i < tensor.order; ++i) {
        if (tensor.dim[i]) {
            neworder++;
        }
    }
    if (neworder != tensor.order) {
        int j = 0;
        int* newdim = new int[neworder];
        for (int i = 0; i < tensor.order; i++) {
            if (tensor.dim[i]) {
                newdim[j] = tensor.dim[i];
                j++;
            }
        }
        tensor.order = neworder;
        delete tensor.dim;
    }
}