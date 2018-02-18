#include "stdafx.h"
#include "min_heap.h"
#include "comparable.h"

#define size 16

int main() {
	min_heap* temp = MIN_HEAP(compare_temperature);
	temperature seq[size];
	srand(time(0));
	for (int i = 0; i < size; i++)
	{
		int number = rand() % 499-269;
		seq[i].degrees = number;
		//printf("%d\n",number);
		insert_heap(temp,seq+i);
	}
	for (int i = 0; i < size/2; i++)
	{
		display(temp,get_temperature);
		printf("the min is %d\n", TEM(extract_min(temp))->degrees);
		/*printf("which rank and which key do u want to decrease?(example:rank=4,key=123)\n");
		scanf_s("rank=%d,key=%d",&rank,&key);
		system("pause");*/
		/*decrease_key(temp,rank,key);*/
		/*display(temp);*/
		/*printf("the min is %d\n", extract_min(temp));*/
	}
	
	printf("a heap of %d capacity has been created\n", temp->capacity);
	del_MIN_HEAP(temp);
	system("pause");
	return 0;
}