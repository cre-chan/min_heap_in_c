#pragma once
/*
2018/2/18 cre-chan at home, Hangzhou, China

This is my first step on writing a whole set of libraries for data structures
in C. There're probably many defects remained unseen and it will be of great
help for you to find them for me. But anyway, I hope you can enjoy the library.

So, let me introduce the library for you. In the library lies our min_heap and 
his related functions:
-------------********------------------------
1.MIN_HEAP(
     int(*compare)(comparable_ptr, comparable_ptr),
	 void(*deconstruct)(comparable_ptr)
)
this function allocs memory for a min_heap and retrun a 
pointer to it. The function requires a pointer to a function
as parameter. The function is used to compare two elements in 
the heap. The min_heap has 2 capacity and 0 length. O(1) time
complexity.


2.del_MIN_HEAP(
     min_heap* heap
)
this function destroy a heap and free its memory. O(1) time
complexity.

3.insert_heap(
     min_heap* heap, 
     comparable_ptr key
)
this function insert a key into the heap according to the rule of
binary heap. Comparable_ptr is a void pointer. This function is of
O(lg n) time complexity.

4.decrease_key(
min_heap* heap, 
int rank,
comparable_ptr key
)
this function decrease a key value in the heap and keep the property
of binary heap. Rank is an interger starting from 1. And this rank
makes random access. So I recommend that when U implementing graph
or somthing, make an extra slot in your node to store this value so you
can access this quickly.(Support on this feature will be included later)
This function is of O(lg n) time complexity as well.

5.extract_min(
min_heap* heap
)
this function returns a pointer to the minimum key and delete it from
the heap. O(lg n) time complexity.
-------------*******--------------------

Also his properties:
1.arr:  this property is an array of comparable pointer (actually void pointers).
Any key in the heap is stored in this place as a binary tree.

2.capacity:  this property is an interger represents the maximum amount of
keys the heap can hold. It is always a power of 2. Updates automatically.

3.length:  the number of keys a heap really holds. Updates automatically.

4.compare:  a function used to compare two elements in a heap. This property
is aquired during initilization of a heap and should not be changed. The core
part of a heap.

5.deconstruct(optional): a function used to free elements from a heap. If this
is left as NIL during initialization, memory leakage may occur when calling
the del_MIN_HEAP function. If you don't want to destroy elements for some purpose,
set the second arguments of MIN_HEAP as NULL is OK.
--------------*******---------------------

*/



typedef void* comparable_ptr;

//definition for a min_heap and its methods
typedef struct {
	comparable_ptr* arr;
	int capacity;
	int length;
	int(*compare)(comparable_ptr,comparable_ptr);
	void(*deconstruct)(comparable_ptr);
}min_heap;

#ifdef _cplusplus
extern "C" {
#endif // _cplusplus

#ifdef _DEBUG
	void display(min_heap*, int(*get)(comparable_ptr));
#endif // DEBUG

    //this function is used to view the whole heap while debugging
	void display(min_heap*, int(*get)(comparable_ptr));

	min_heap* MIN_HEAP(
		int(*compare)(comparable_ptr, comparable_ptr),
		void(*deconstruct)(comparable_ptr)
	);

	void del_MIN_HEAP(min_heap* heap);

	void min_heap_insert(
		min_heap* heap, 
		comparable_ptr key
	);

	void decrease_key(
		min_heap* heap, 
		int rank,
		comparable_ptr key
	);

	comparable_ptr extract_min(min_heap* heap);

#ifdef _cplusplus
}
#endif // _cplusplus
