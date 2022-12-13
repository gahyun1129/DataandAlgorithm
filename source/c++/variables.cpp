#include <iostream>

void test() {
	static int var;
	++var;

	std::cout << var << std::endl;
}
int main() {
	//test();
	//test();
	////int a = var; 정적 변수는 함수의 외부에선 사용할 수 없음.

	//int const* a, * b; // a가 가리키는 저장소의 데이터가 상수임을 나타냄.
	//const int* c, * d; // c가 가리키는 저장소의 데이터가 상수임을 나타냄.
	//int* e, const* f; // f가 가리키는 저장소의 데이터가 상수임을 나타냄.
	//int* const g = 0;  //g가 가리키는 메모리 주소는 상수임을 나타냄.
	//static int* h; //포인터 p가 정적 타입이란 사실을 나타냄.

	bool x = true;
	std::cout << x << "은 " << std::boolalpha << x << ", " << std::noboolalpha << !x << "은 " << std::boolalpha << !x << std::endl;

	std::boolalpha(std::cout);
	std::cout << x << std::endl;

	wchar_t wc[] = L"hello world!";

	std::wcout << wc << ", wchar_t 바이트 크기: " << sizeof(wchar_t) << ", 문자 길이: " << wcslen(wc) << std::endl;

	std::wcin >> wc;

	return 0;
}