#include <iostream>

void test() {
	static int var;
	++var;

	std::cout << var << std::endl;
}
int main() {
	//test();
	//test();
	////int a = var; ���� ������ �Լ��� �ܺο��� ����� �� ����.

	//int const* a, * b; // a�� ����Ű�� ������� �����Ͱ� ������� ��Ÿ��.
	//const int* c, * d; // c�� ����Ű�� ������� �����Ͱ� ������� ��Ÿ��.
	//int* e, const* f; // f�� ����Ű�� ������� �����Ͱ� ������� ��Ÿ��.
	//int* const g = 0;  //g�� ����Ű�� �޸� �ּҴ� ������� ��Ÿ��.
	//static int* h; //������ p�� ���� Ÿ���̶� ����� ��Ÿ��.

	bool x = true;
	std::cout << x << "�� " << std::boolalpha << x << ", " << std::noboolalpha << !x << "�� " << std::boolalpha << !x << std::endl;

	std::boolalpha(std::cout);
	std::cout << x << std::endl;

	wchar_t wc[] = L"hello world!";

	std::wcout << wc << ", wchar_t ����Ʈ ũ��: " << sizeof(wchar_t) << ", ���� ����: " << wcslen(wc) << std::endl;

	std::wcin >> wc;

	return 0;
}