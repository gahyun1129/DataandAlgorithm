#include <iostream>
#include <string>

int main() {

	const char* cstr = "안녕하세요. hello!";
	std::string str = cstr;

	std::cout << "str=" << str.data() << ", 문자열의 크기는: " << str.length() << std::endl;

	str = "안녕히 가세요.";
	str += " bye!";

	std::cout << "str=" << str.data() << ", 문자열의 크기는: " << str.length() << std::endl;

	std::string s2(str);					//str 복사
	std::string s3(str, 6, 5);				//str의 7번째 문자부터 시작해 5개의 문자를 잘라	 생성.
	std::string s4(str, 6);					//str의 7번째 문자부터 끝까지 복사해 생성.
	std::string s5(10, 'x');				//'x' 문자를 10번 반복.

	std::cout << "str: " << str.data() << std::endl;
	std::cout << "s2: " << s2.data() << std::endl;
	std::cout << "s3: " << s3.data() << std::endl;
	std::cout << "s4: " << s4.data() << std::endl;
	std::cout << "s5: " << s5.data() << std::endl;
}