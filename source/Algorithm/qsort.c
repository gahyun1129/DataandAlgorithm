#include <stdio.h>
#include <stdlib.h>

void qsort(
	void* base,			//���� ��� �迭�� �ּ� 
	size_t num,			//�迭�� ��� ����
	size_t width,		//������ ��� �ϳ��� ũ��
	int (cdecl* compare)(const void*, const void*) //�񱳸� ������ ����� ��ȯ�ϴ� �Լ��� ���� ������
);