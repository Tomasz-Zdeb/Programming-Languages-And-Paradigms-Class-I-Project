#pragma once
#include<stdio.h>
#include<stdlib.h>
typedef void(*FREE_DATA_FUN)(void** data);
typedef void(*PRINT_DATA_FUN)(void* data);
typedef int(*COMPARE_DATA_FUN)(void* data_1, void* data_2);
typedef void(*SAVE_DATA_FUN)(void* ptr, FILE* file_ptr);
typedef void*(*READ_DATA_FUN)(FILE* file_ptr);

struct CONTAINER_MY_STACK
{
	void* data;
	void* lower_element;
	void* higher_element;
	FREE_DATA_FUN free_fun;
	PRINT_DATA_FUN print_fun;
	COMPARE_DATA_FUN compare_fun;
	SAVE_DATA_FUN save_fun;
	READ_DATA_FUN read_fun;
	static size_t no_elements;
};
CONTAINER_MY_STACK* CONTAINER_MY_STACK_INIT();
CONTAINER_MY_STACK* CONTAINER_MY_STACK_PUSH(CONTAINER_MY_STACK* top, CONTAINER_MY_STACK* to_add);
void CONTAINER_MY_STACK_FREE(CONTAINER_MY_STACK** top);
CONTAINER_MY_STACK* CONTAINER_MY_STACK_POP(CONTAINER_MY_STACK** top);
void CONTAINER_MY_STACK_PRINT(CONTAINER_MY_STACK* top);
void CONTAINER_MY_STACK_SAVE(CONTAINER_MY_STACK* top,char *filename);
CONTAINER_MY_STACK* CONTAINER_MY_STACK_READ(CONTAINER_MY_STACK** top,char* filename);
void CONTAINER_MY_STACK_SEARCH(CONTAINER_MY_STACK* top);