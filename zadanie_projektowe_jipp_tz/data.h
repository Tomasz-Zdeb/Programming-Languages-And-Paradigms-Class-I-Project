#pragma once
#include <stdio.h>
#include <stdlib.h>

enum KIERUNEK_STUDIA
{
	KIERUNEK_INFORMATYKA,
	KIERUNEK_MATEMATYKA,
	KIERUNEK_FIZYKA
};

struct DATA_MY_STUDENT
{
	char* nazwisko;
	int dlugosc_nazwiska;
	int data_urodzenia;
	KIERUNEK_STUDIA kierunek_studiow;
};


DATA_MY_STUDENT* DATA_MY_STUDENT_CREATE(const char* nazwisko, int data_urodzenia, enum KIERUNEK_STUDIA kierunek);
DATA_MY_STUDENT* DATA_MY_STUDENT_INPUT();
void DATA_MY_STUDENT_FREE(void** ptr);
void DATA_MY_STUDENT_PRINT(void* ptr);
void DATA_MY_STUDENT_SAVE(void* ptr, FILE* file_ptr);
void* DATA_MY_STUDENT_READ(FILE* file_ptr);
int DATA_MY_STUDENT_COMPARE_NAZWISKO(void* ptr1, void* ptr2);
int DATA_MY_STUDENT_COMPARE_DATA_URODZENIA(void* ptr1, void* ptr2);
int DATA_MY_STUDENT_COMPARE_KIERUNEK_STUDIOW(void* ptr1, void* ptr2);