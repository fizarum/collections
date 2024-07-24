#include "stack.h"

#include <stdlib.h>
#include <string.h>

typedef struct Stack_t {
	// pointer on pointers of data
	_ptr* values;
	// count of added items in array
	_u16 size;
	// total capacity
	_u16 capacity;
} Stack_t;

Stack_t* StackCreate(_u16 capacity) {
	Stack_t* stack = (Stack_t*)malloc(sizeof(Stack_t));

	if (stack == NULL) return NULL;

	stack->capacity = capacity;
	stack->size = 0;
	stack->values = (_ptr*)calloc(capacity, sizeof(_ptr));
	return stack;
}

void StackDestroy(Stack_t* stack) {
	if (stack == NULL) return;

	free(stack->values);
	free(stack);
}

void StackClear(Stack_t* stack) {
	memset(stack->values, 0, sizeof(_ptr) * (stack->capacity));
	stack->size = 0;
}

_u16 StackSize(const Stack_t* stack) {
	return stack->size;
}

_u16 StackCapacity(const Stack_t* stack) {
	return stack->capacity;
}

bool StackPush(Stack_t* stack, void* value) {
	if (StackIsFull(stack) == true) return false;

	stack->values[stack->size] = (_ptr)value;
	stack->size++;
	return true;
}

void* StackPop(Stack_t* stack) {
	if (StackIsEmpty(stack) == true) return NULL;

	_u16 indexToPop = stack->size - 1;
	_ptr value = stack->values[indexToPop];

	stack->values[indexToPop] = 0;
	stack->size--;

	return (void*)value;
}

bool StackIsFull(const Stack_t* stack) {
	return stack->size == stack->capacity;
}

bool StackIsEmpty(const Stack_t* stack) {
	return stack->size == 0;
}