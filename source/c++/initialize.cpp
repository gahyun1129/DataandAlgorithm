#include <iostream>

int main() {
	int a = 10;
	int b(20);
	int c{ 30 };
	int d = int(40);
	int f = int(); 
	//int()�� ����Ʈ �������̸� 0���� �ʱ�ȭ��.
	int g = { 50 };
	int* h = new int; 
	//new �����ڸ� �̿��� �޸� ����Ҹ� ������ ���� �Ҵ�.
	// int* h = (int *)malloc(sizeof(int));�� ����.
	int* i = new int();
	int* j = new int(60);
	//j �����Ͱ� ����Ű�� ����Ҵ� 60���� �ʱ�ȭ��.



}