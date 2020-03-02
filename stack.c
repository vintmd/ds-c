/**
 * @file stack.c
 * @brief the arr form of the stack
 * also have another two way to realize the stack  is the list way and container
 * @author tmd
 * @version 1.0
 * @date 2016-11-20
 */
#include<stdio.h>
#include<stdlib.h>
#define STACK_LEN 10

typedef struct node{
	int top; //top index
	int size;
	int count;
	int *arr;
}Stack;
/**
 * @brief is_empty 
 *
 * @param stack
 *
 * @return -1 error
 * 0 is empty
 * else not empty
 */
int is_empty(Stack* stack){
	if(stack == NULL)
		return -1;
	if(stack->top == -1){
		return 0;
	}else{
		return 1;	
	}
}
void init(Stack* stack){
	if(stack == NULL)
		return;
	stack->top = -1;
	stack->count = 0;
	stack->size = STACK_LEN ;
	stack->arr = (int*)malloc(sizeof(int)*stack->size);
	return ;
}
int push(Stack* stack, int value){
	if(stack == NULL)	
		return -1;
	if(stack->top < stack->size){
		stack->top++;
		stack->arr[stack->top] = value;	
		stack->count++;
	}else{
		return -1;	
	}
	return -1;
	
}
int pop(Stack* stack){
	if(stack == NULL)
		return -1;
	if(is_empty(stack) == 0){
		return -1;	
	}
	int tmp = stack->top;
	stack->top--;
	stack->count--;
	return stack->arr[tmp];
}
void show(Stack* stack){
	int size = stack->count;	
	int i;
	for(i=0;i<size;i++){
		printf("%d\n",stack->arr[i]);
	}
	return ;
	printf("-------------------=n");
}

int main()
{
	int i;
	Stack *stack = (Stack*)malloc(sizeof(Stack));
	init(stack);
	push(stack,1);
	push(stack,2);
	push(stack,3);
	push(stack,4);
	show(stack);
	for(i=0;i<4;i++){
		printf("pop out %d\n",pop(stack))	;
	}

	
	
	return 0;
}

