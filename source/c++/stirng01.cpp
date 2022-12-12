#include <iostream>
#include <string>

int main() {

	const char* cstr = "�ȳ��ϼ���. hello!";
	std::string str = cstr;

	std::cout << "str=" << str.data() << ", ���ڿ��� ũ���: " << str.length() << std::endl;

	str = "�ȳ��� ������.";
	str += " bye!";

	std::cout << "str=" << str.data() << ", ���ڿ��� ũ���: " << str.length() << std::endl;

	std::string s2(str);					//str ����
	std::string s3(str, 6, 5);				//str�� 7��° ���ں��� ������ 5���� ���ڸ� �߶�	 ����.
	std::string s4(str, 6);					//str�� 7��° ���ں��� ������ ������ ����.
	std::string s5(10, 'x');				//'x' ���ڸ� 10�� �ݺ�.

	std::cout << "str: " << str.data() << std::endl;
	std::cout << "s2: " << s2.data() << std::endl;
	std::cout << "s3: " << s3.data() << std::endl;
	std::cout << "s4: " << s4.data() << std::endl;
	std::cout << "s5: " << s5.data() << std::endl;
}