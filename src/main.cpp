#include "driver.hpp"
#include <iostream>

int main() {
	Grammar::Driver driver{};

	driver.parse(std::cin);

	std::cout << driver.getEncoding() << std::endl;
}
