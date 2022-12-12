#include <iostream>
#include <iomanip>
#include <locale>

int main() {

	std::cout << "hello world!" << std::endl;
	//std::cerr << "문제 발생" << std::endl;

	//std::cout << std::setfill('0');
	//std::cout << std::setw(3) << 3 << std::endl;
	//std::cout << std::setw(3) << n << std::endl;

	int n = 2022;
	std::cout << std::setw(12) << std::hex << std::showbase << n << std::endl;
	std::cout << std::endl;

	std::cout << std::left << std::setw(12) << std::hex << std::showbase << n << std::endl;
	std::cout << std::internal << std::setw(12) << std::hex << std::showbase << n << std::endl;
	std::cout << std::right << std::setw(12) << std::hex << std::showbase << n << std::endl;
}