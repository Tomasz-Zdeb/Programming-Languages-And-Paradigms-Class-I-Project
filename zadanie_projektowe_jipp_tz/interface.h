#pragma once
#include "data.h"
#include "container.h"

void INTERFACE_MENU();
void INTERFACE_ADD_OBJECT(CONTAINER_MY_STACK** top);
void INTERFACE_PRINT_ALL_OBJECTS(CONTAINER_MY_STACK* top);
void INTERFACE_POP(CONTAINER_MY_STACK** top);
void INTERFACE_SAVE(CONTAINER_MY_STACK* top, char* filename);
void INTERFACE_READ(CONTAINER_MY_STACK** top, char* filename);
void INTERFACE_CLEAR_STACK(CONTAINER_MY_STACK** top);
void INTERFACE_DEALLOC(CONTAINER_MY_STACK** stack, CONTAINER_MY_STACK** temp, __int64** file_desc, FILE** file_ptr);
void INTERFACE_EXIT(CONTAINER_MY_STACK** stack, CONTAINER_MY_STACK** temp, __int64** file_desc, FILE** file_ptr);