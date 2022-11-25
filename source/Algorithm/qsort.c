#include <stdio.h>
#include <stdlib.h>

void qsort(
	void* base,			//정렬 대상 배열의 주소 
	size_t num,			//배열의 요소 개수
	size_t width,		//데이터 요소 하나의 크기
	int (cdecl* compare)(const void*, const void*) //비교를 수행한 결과를 반환하는 함수에 관한 포인터
);