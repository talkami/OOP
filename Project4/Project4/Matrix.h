#pragma once
#include "MatrixCopier.h"
#include <iostream>
#include <memory>

template<class T, size_t DIMENSIONS>
class Matrix {
    constexpr static size_t NUM_DIMENSIONS = DIMENSIONS;
    std::unique_ptr<T[]> _array = nullptr;
    size_t _dimensions[DIMENSIONS] = {};
    const size_t _size = 0;
    friend class Matrix<T, DIMENSIONS+1>;
public:
    size_t size() const {return _size;}
    Matrix() {}

	template<typename G = T>
	Matrix(const std::initializer_list<typename std::enable_if_t<DIMENSIONS == 1, G>>& values);
	Matrix(Matrix&& m);
	auto& operator=(Matrix&& m);
	size_t getDimension(size_t i) const;
	template<typename Func>
	int groupValues(Func f);//change return value!	
	
	friend std::ostream& operator<<(std::ostream& out, const Matrix& m);

};

// defining Matrix2d<T> as Matrix<T, 2>
template<class T>
using Matrix2d = Matrix<T, 2>;
 
// defining Matrix3d<T> as Matrix<T, 3>
template<class T>
using Matrix3d = Matrix<T, 3>;

// defining IntVector as Matrix<int, 1>
using IntVector = Matrix<int, 1>;