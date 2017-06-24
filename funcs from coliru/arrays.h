#include <iostream>

using std::cout;

template<typename T, size_t SIZE>
class Array {
    T arr[SIZE] = {};
public:
    Array(std::initializer_list<T> v) {
        int i = 0;
        for(auto& a : v) {
            arr[i++] = a;
        }
    }
    const T* begin() const {
        return arr;
    }
    const T* end() const {
        return arr + SIZE;
    }
};

template<typename T, size_t ROWS, size_t COLS>
struct Array2d {
    T arr[ROWS*COLS] = {};
    Array2d(std::initializer_list<std::initializer_list<T>> v) {
        int i = 0;
        for(auto& row : v) {
            for(auto& a : row) {
                arr[i++] = a;
            }
        }
    }
    class Row {
        T* _row;
    public:
        Row(T* row) : _row(row) {}
        const T* begin() const {
            return _row;
        }
        const T* end() const {
            return _row + COLS;
        }
    };
    class iterator {
        T* _row;
    public:
        iterator(T* row): _row(row) {}
        iterator operator++() {
            _row = _row + COLS;
            return *this;
        }
        Row operator*() {
            return _row;
        }
        bool operator!=(iterator other) {
            return _row != other._row;
        }
    };
    const iterator begin() {
        return arr;
    }
    const iterator end() {
        return arr + COLS * ROWS;
    }
};

int main() {
    Array<char, 10> a1 = {'H', 'e', 'l', 'l', 'o'};
    for(auto c : a1) {
        cout << c;
    }
    cout << std::endl;

    Array2d<char, 2, 5> a2 = { {'H', 'e', 'l', 'l', 'o'}, {'W', 'o', 'r', 'l', 'd'} };
    for(auto row : a2) {
        for(auto c : row) {
            cout << c;
        }
        cout << std::endl;
    }
}
