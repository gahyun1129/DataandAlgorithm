#include <iostream>

struct X {
	static void f();
	static int n;
	int m;
};

void X::f() {
	std::cout << "안녕하세요 n 변수는 " << n << std::endl;
}

int X::n = 10;

enum color1 {
	RED, GREEN, BLUE
};

enum class color2 {
	GREEN, YELLOW, RED
};

color1 background = RED;
//color1 color = color2::RED;

//color2 stop = RED;
//color2 wait = YELLOW;
color2 go = color2::GREEN;

int main() {
	X::f();
	X::n = 100;
	X::f();
}