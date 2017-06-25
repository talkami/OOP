#include "Matrix.h"

template<typename Groups>
void print(const Groups& all_groups) {
	for (const auto& groupType : all_groups) {
		std::cout << groupType.first << ":" << std::endl;
		for (const auto& groupOfType : groupType.second) {
			for (const auto& coord : groupOfType) {
				std::cout << "{ ";
				for (auto i : coord) {   // was: for(int i : coord)
					std::cout << i << ' ';
				}
				std::cout << "} ";
			}
			std::cout << std::endl;
		}
	}
}

int main() {
	Matrix2d<char> m = {{ 'a', 'A', 'a' }, { 'B', 'a', 'B' }, { 'B', 'a', 'B' }};
	auto all_groups = m.groupValues([](auto i) {return islower(i) ? "L" : "U"; });
	print(all_groups);

	Matrix3d<int> m2 = { { { 1, 2, 3 },{ 1, 2 },{ 1, 2 } },{ { 1, 2 },{ 1, 2, 3, 4 } } };
	auto groups = m2.groupValues([](auto i) {return i % 3 ? "!x3" : "x3"; });
	print(groups);

}

/*
int main() {
	Matrix<int, 1> m0 = { 25, 10, 15 };
	std::cout << m0 << std::endl;
	std::cout << std::endl;

	Matrix<int, 3> m1 = { { { 10, 20, 30 },{ 10, 20 },{ 11, 22, 33 } },{ { 40, 50, 60 },{ 80, 90 },{ 51, 52, 53 } } };
	std::cout << m1 << std::endl;
	std::cout << m1.getDimension(2) << std::endl;
	std::cout << std::endl;

	// move-assignment
	Matrix3d<int> m2;
	m2 = std::move(m1);
	std::cout << m2 << std::endl;

	// move-ctor
	auto m3 = std::move(m2);
	std::cout << m3 << std::endl;

	IntVector m4 = std::move(m0);
	std::cout << m4 << std::endl;

	Matrix<int, 2> m5 = { {},{ 25, 10, 15 },{},{ 3 } };
	std::cout << m5 << std::endl;
	char x;
	std::cin >> x;
}
*/
