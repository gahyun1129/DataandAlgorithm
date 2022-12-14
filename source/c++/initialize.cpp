#include <iostream>

int main() {
	int a = 10;
	int b(20);
	int c{ 30 };
	int d = int(40);
	int f = int(); 
	//int()는 디폴트 생성자이며 0으로 초기화됨.
	int g = { 50 };
	int* h = new int; 
	//new 연산자를 이용해 메모리 저장소를 생성해 변수 할당.
	// int* h = (int *)malloc(sizeof(int));와 같음.
	int* i = new int();
	int* j = new int(60);
	//j 포인터가 가리키는 저장소는 60으로 초기화됨.



}