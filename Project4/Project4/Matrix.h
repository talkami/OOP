#include <iostream>
#include <memory>
#include <vector>
#include <map>

#include "MatrixCopier.h"

template<class T, size_t DIMENSIONS>
struct MatrixPrinter {
	static void print(const T* values, size_t size, const size_t* dimensions, std::ostream& out = cout) {
		out << '{';
		size_t size0 = size / dimensions[0];
		MatrixPrinter<T, DIMENSIONS - 1>::print(values, size0, dimensions + 1, out);
		for (size_t i = 1; i < dimensions[0]; ++i) {
			out << ',';
			MatrixPrinter<T, DIMENSIONS - 1>::print(values + (i*size0), size0, dimensions + 1, out);
		}
		out << '}';
	}
};

template<class T>
struct MatrixPrinter<T, 1> {
	static void print(const T* values, size_t size, const size_t* dimensions, std::ostream& out = cout) {
		out << '{';
		out << values[0];
		for (size_t i = 1; i < size; ++i) {
			out << ',' << values[i];
		}
		out << '}';
	}
};

template<class T, size_t DIMENSIONS>
class Matrix {
	constexpr static size_t NUM_DIMENSIONS = DIMENSIONS;
	std::unique_ptr<T[]> _array = nullptr;
	size_t _dimensions[DIMENSIONS] = {};
	const size_t _size = 0;
	friend class Matrix<T, DIMENSIONS + 1>;

	std::vector<int> getCoord(int location) {
		std::vector<int> coord(DIMENSIONS);
		for (int i = 0; i < DIMENSIONS; i++) {
			int temp = 1;
			for (int j = i + 1; j < DIMENSIONS; j++) {
				temp *= _dimensions[j];
			}
			coord.at(i) = (location / temp) % _dimensions[i];
		}
		return coord;
	}

	int getLocation(std::vector<int> coord) {
		int location = 0;
		for (int i = 0; i < DIMENSIONS; i++) {
			int temp = 1;
			for (int j = i + 1; j < DIMENSIONS; j++) {
				temp *= _dimensions[j];
			}
			location += temp*coord[i];
		}
		return location;
	}

	//returns the value of the matrix at the coordinate
	template<typename G = T>
	G getVal(std::vector<int> coordinate) {
		int location = getLocation(coordinate);
		return _array[location];
	}

	
public:
	size_t size() const { return _size; }
	Matrix() {}

	// DIMENSIONS == 1
	// We want here a ctor with this signature:
	//    Matrix(const std::initializer_list<T>& values) {
	// but SFINAE is needed to block this ctor from being used by Matrix with DIMENSIONS > 1
	// The SFINAE results with the exact signature we want, but only for cases DIMENSIONS == 1
	template<typename G = T>
	Matrix(const std::initializer_list<typename std::enable_if_t<DIMENSIONS == 1, G>>& values) {
		const_cast<size_t&>(_size) = values.size();
		_dimensions[0] = _size;
		_array = std::make_unique<T[]>(_size);
		size_t i = 0;
		for (auto& val : values) {
			_array[i++] = val;
		}
	}

	// DIMENSIONS > 1
	// We want here a ctor with this signature:
	//    Matrix(const std::initializer_list<Matrix<T, DIMENSIONS-1>>& values) {
	// although this ctor is not useful and won't be used by Matrix<T, 1> it will still be in class
	// and thus would compile as part of Matrix<T, 1> resulting with a parameter of type:
	//          const std::initializer_list< Matrix<T, 0> >& values
	// having Matrix<T, 0> as a parameter - even for a function that is not in use, inside a class that is used
	// would require the compiler to instantiate Matrix<T, 0> class which results with a warning
	// the SFINAE below solves this warning.
	// The SFINAE results with the exact signature we want, but only for cases DIMENSIONS > 1
	template<typename G = T>
	Matrix(const std::initializer_list<Matrix<typename std::enable_if_t<(DIMENSIONS > 1), G>, DIMENSIONS - 1>>& values) {
		_dimensions[0] = values.size();
		for (auto& m : values) {
			for (size_t dim = 0; dim < DIMENSIONS - 1; ++dim) {
				if (m._dimensions[dim] > _dimensions[dim + 1]) {
					_dimensions[dim + 1] = m._dimensions[dim];
				}
			}
		}
		size_t size = 1;
		for (size_t dim = 0; dim < DIMENSIONS; ++dim) {
			size *= _dimensions[dim];
		}
		const_cast<size_t&>(_size) = size;
		_array = std::make_unique<T[]>(_size); // "zero initialized" - T()
		size_t i = 0;
		size_t dest_size = _size / _dimensions[0];
		for (auto& m : values) {
			MatrixCopier<T, DIMENSIONS - 1>::copy(&(_array[i * dest_size]), dest_size, _dimensions + 1, m._array.get(), m._size, m._dimensions);
			++i;
		}
	}

	Matrix(Matrix&& m) {
		*this = std::move(m);
	}

	auto& operator=(Matrix&& m) {
		std::swap(_array, m._array);
		std::swap(const_cast<size_t&>(_size), const_cast<size_t&>(m._size));
		std::swap(_dimensions, m._dimensions);
		return *this;
	}

	size_t getDimension(size_t i) const {
		return _dimensions[i];
	}

	//needs to return something (a group to add to groups?)
	template<class GroupingFunc>
	void checkForNearbyGroup(std::vector<int> coordinate, std::vector<std::vector<int>>* exploredCoorinate, GroupingFunc groupingFunc){
		for (int i = 0; i < DIMENSIONS; i++) {
			//if the i's Dim is finished stop the recurrtion
			if (getDimension(i) == coordinate[i] + 1) {
				continue;
			}
			std::vector<int> tmpCoor = coordinate;
			tmpCoor[i] = tmpCoor[i] + 1;//BAD!!!!!
			if (groupingFunc(getval(tmpCoor)) == groupingFunc(getval(coordinate))){
				//if exploredCoordinate does not contains tmpCoor
				if(std::find(exploredCoordinate->begin(), exploredCoordinate->end(), tmpCoor) == exploredCoordinate->end()) {
					//add to groups
					exploredCoorinate->push_back(tmpCoor);
					checkForNearbyGroup(tmpCoor, exploredCoorinate, groupingFunc);
				}
			}
		}
	}


	//need to actually put stuff in groups
	//NEED TO CHANGE FUNCTION TO FIT OUR NEEDS!!!
	template<class GroupingFunc, typename G = T>
	auto groupValues(GroupingFunc groupingFunc) {
		using GroupingType = std::result_of_t<GroupingFunc(G&)>;
		std::map<GroupingType, std::vector<std::vector<std::vector<int>>>> groups;
		std::vector<std::vector<int>> exploredCoordinate;
		for (int i = 0; i < _size; i++) {
			std::vector<int> coordinate = getCoord(i);
			if(std::find(exploredCoordinate.begin(), exploredCoordinate.end(), coordinate) != exploredCoordinate.end()) {
   				continue;
			}
			exploredCoordinate.push_back(coordinate);//no point, we are not checking back
			checkForNearbyGroup(coordinate, &exploredCoorinate, groupingFunc, &groups);
		}
		return groups;
	}

	friend std::ostream& operator<<(std::ostream& out, const Matrix& m) {
		MatrixPrinter<T, DIMENSIONS>::print(m._array.get(), m._size, m._dimensions, out);
		return out;
	}
};

// defining Matrix2d<T> as Matrix<T, 2>
template<class T>
using Matrix2d = Matrix<T, 2>;


// defining Matrix3d<T> as Matrix<T, 3>
template<class T>
using Matrix3d = Matrix<T, 3>;
