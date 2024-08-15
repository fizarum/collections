#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

#define STACK_INDEX_NONE UINT16_MAX

typedef struct Stack_t Stack_t;

Stack_t* StackCreate(_u16 capacity);
void StackDestroy(Stack_t* stack);

_u16 StackSize(const Stack_t* stack);
_u16 StackCapacity(const Stack_t* stack);

bool StackPush(Stack_t* stack, void* value);
void* StackPop(Stack_t* stack);
void StackClear(Stack_t* stack);

bool StackIsFull(const Stack_t* stack);
bool StackIsEmpty(const Stack_t* stack);

#ifdef __cplusplus
}
#endif

#endif  // STACK_H