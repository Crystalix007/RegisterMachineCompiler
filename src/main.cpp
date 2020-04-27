#include "driver.hpp"
#include <iostream>

template<typename _ty>
std::ostream& operator<<(std::ostream& os, const std::vector<_ty>& vec);

int main() {
	Grammar::Driver driver{};

	driver.parse(std::cin);

	const auto lists = driver.getLists();

	for (const auto& list : lists) {
		for (uint32_t i = 0; i <= list.size(); i++) {
			std::vector<uint32_t> subVec{ list.end() - i, list.end() };

			std::cout << subVec << ": " << driver.getListEncoding(subVec) << std::endl;
		}

		std::cout << std::endl;
	}
}

template<typename _ty>
std::ostream& operator<<(std::ostream& os, const std::vector<_ty>& vec) {
	if (vec.empty()) {
		os << "[]";
	}	else {
		std::cout << "[ ";

		for (uint32_t i = 0; i < vec.size(); i++)
			std::cout << vec[i] << (i + 1 == vec.size() ? "" : ", ");

		std::cout << " ]";
	}

	return os;
}
