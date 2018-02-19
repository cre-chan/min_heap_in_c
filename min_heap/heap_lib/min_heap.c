#include "stdafx.h"
#include "min_heap.h"
#include "comparable.h"

//MACROS alloc memory
#define NEW_COMPTR(num) ((comparable_ptr*)malloc(sizeof(comparable_ptr)*num))
#define NEW_HEAP() ((min_heap*)malloc(sizeof(min_heap)))

//MACROS for conversion
#define VOID(ptr) ((void*)(ptr))

//MACROS related to heap operations
#define length(ptr) (heap->length)
#define empty(ptr) (!length(heap))
#define PARENT(id) (id/2)
#define left_child(parent) (parent*2)
#define right_child(parent) (parent*2+1)
#define content(heap,i) (heap->arr[i-1])

//MACROS for generics
#define COMPARE(heap,a,b) (heap->compare(content(heap,a),content(heap,b)))

typedef int index;

static void expand_heap(min_heap* heap);
static void shrink_heap(min_heap* heap);




min_heap* MIN_HEAP(
	int(*compare)(comparable_ptr, comparable_ptr),
	void(*deconstruct)(comparable_ptr)
){
	min_heap* temp;
	temp = NEW_HEAP();
	temp->arr = NEW_COMPTR(2);
	temp->capacity = 2;
	temp->length = 0;
	temp->compare = compare;
	temp->deconstruct = deconstruct;
	return temp;
}






void del_MIN_HEAP(min_heap* heap) {
	//if the deconstruct is not NIL, then use the deconstruct to
	//free the memory of every element in heap->arr
	if (heap->deconstruct != NULL)
	{
		for (int i = 0; i < heap->length; i++) heap->deconstruct(heap->arr[i]);
	};

	free(VOID(heap->arr));
	free(VOID(heap));
}






void min_heap_insert(min_heap* heap, comparable_ptr val) {

	//expand the heap if it's full
	if (heap->capacity <= heap->length) expand_heap(heap);
	//insert the val into the tail. if the heap is empty,
	//update the length and return
	heap->arr[length(heap)] = val;
	heap->length++;
	if (empty(heap)) {
		return;
	};

	//index starts from 1, the arr index is index minus one
	index child = length(heap), parent = PARENT(child);
	while (parent >= 1) {
		//if the child is smaller than the parent
		//swap child and parent
		if (COMPARE(heap,child,parent)==-1)
		{
			comparable_ptr inter = heap->arr[child - 1];
			heap->arr[child-1]= heap->arr[parent-1];
			heap->arr[parent - 1] = inter;
		}
		//if parent is smaller than the child,stop the loop
		else {
			break;
		};
		child = parent;
		parent = PARENT(child);
	};

	/*display(heap);*/
}






comparable_ptr extract_min(min_heap* heap) {
	//
	if (heap->length == 0) return NULL;

	//swap the first with the tail
	comparable_ptr inter = heap->arr[0],result=inter;
	heap->arr[0] = heap->arr[length(heap)-1];
	heap->arr[length(heap) - 1] = inter;
	heap->length--;
	

	if (heap->capacity / 4 >= heap->length) shrink_heap(heap);

	index parent = 1, left_child = left_child(parent), right_child = right_child(parent);
	while (left_child <= length(heap)
		|| right_child <= length(heap)) {
		//smaller child is the child having a less value
		index smaller_child;
		if (right_child < length(heap)&&COMPARE(heap,left_child,right_child)==-1)
		{
			smaller_child = left_child;
		}
		else {
			smaller_child = right_child;
		}

		if (right_child > length(heap)) smaller_child = left_child;

		if (COMPARE(heap,smaller_child,parent)==-1)
		{
			comparable_ptr temp = content(heap,smaller_child);
			content(heap, smaller_child) = content(heap,parent);
			content(heap, parent) = temp;
			parent = smaller_child;
			left_child = left_child(parent);
			right_child = right_child(parent);
		}
		else
		{
			break;
		}
	} ;

	return result;
}







void decrease_key(min_heap* heap,int rank, comparable_ptr key) {
	//if the rank is beyond range, return
	if (rank > length(heap)) return;
	//if the key is no less than the original, do nothing
	if (heap->compare(heap->arr[PARENT(rank)],key)<=0) return;

	if (heap->deconstruct != NULL) heap->deconstruct(heap->arr[rank - 1]);
	heap->arr[rank - 1] = key;
	index child = rank, parent = PARENT(rank);
	while (parent >= 1) {
		//if the child is smaller than the parent
		//swap child and parent
		if (COMPARE(heap,child,parent))
		{
			comparable_ptr inter = heap->arr[child - 1];
			heap->arr[child - 1] = heap->arr[parent - 1];
			heap->arr[parent - 1] = inter;
		}
		//if parent is smaller than the child,stop the loop
		else {
			break;
		};
		child = parent;
		parent = PARENT(child);
	};
}






void display(min_heap* heap,int (*get)(comparable_ptr)) {
	for (int i = 0; i < heap->length; i++)
	{
		printf("%d ", get(heap->arr[i]));
	}
	printf("\n");
}






static void expand_heap(min_heap* heap) {
	//alloc double a space as before
	comparable_ptr* temp;
	temp = NEW_COMPTR(heap->capacity * 2);
	//copy the memory into temp and delete the original heap
	for (int i = 0; i < heap->length; i++)temp[i] = heap->arr[i];
	free(VOID(heap->arr));
	heap->arr = temp;
	heap->capacity *= 2;
}





static void shrink_heap(min_heap* heap) {
	comparable_ptr* temp;
	temp = NEW_COMPTR(heap->capacity / 2);
	//copy the memory into temp and delete the original heap
	for (int i = 0; i < heap->length; i++)temp[i] = heap->arr[i];
	free(VOID(heap->arr));
	heap->arr = temp;
	heap->capacity /= 2;
}