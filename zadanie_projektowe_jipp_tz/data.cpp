#include "data.h"
#include "messages_errors.h"
#include "warning_disabler.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

/*umo¿liwia dzialanie systemowi bledow i powiadomien*/
extern CONTAINER_MY_STACK** THE_STACK;

static const char* kierunki_studiow[] =
{
	"Informatyka",
	"Matematyka",
	"Fizyka"
};

DATA_MY_STUDENT* DATA_MY_STUDENT_CREATE(const char* nazwisko, int data_urodzenia, enum KIERUNEK_STUDIA kierunek)
{
	DATA_MY_STUDENT* student = (DATA_MY_STUDENT*)malloc(sizeof(DATA_MY_STUDENT));
	if (!student)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_DATA_MY_STUDENT_MEMORY_ALLOCATION_ERROR_AT_DATA_LEVEL, THE_STACK, NULL, NULL, NULL);
	student = (DATA_MY_STUDENT*)memset(student, 0, sizeof(DATA_MY_STUDENT));
	if (!student)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_DATA_MY_STUDENT_MEMORY_INITIALIZATION_ERROR_AT_DATA_LEVEL, THE_STACK, NULL, NULL, NULL);
	//ustawia wartosci zapisywane przez wartosc
	student->data_urodzenia = data_urodzenia;
	student->kierunek_studiow = kierunek;
	//funkcja ta zwraca dlugosc wiersza bez znacznika null
	//a nalezy zaalokowac miejsce tez na marker null na koncu stad +1
	student->dlugosc_nazwiska = strlen(nazwisko) + 1;

	student->nazwisko = (char*)malloc(student->dlugosc_nazwiska * sizeof(char));
	if (!student->nazwisko)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_DATA_MY_STUDENT_MEMORY_ALLOCATION_ERROR_AT_DATA_LEVEL, THE_STACK, NULL, NULL, NULL);
	student->nazwisko = (char*)memset(student->nazwisko, 0, student->dlugosc_nazwiska);
	if (!student->nazwisko)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_DATA_MY_STUDENT_MEMORY_INITIALIZATION_ERROR_AT_DATA_LEVEL, THE_STACK, NULL, NULL, NULL);
	strcpy_s(student->nazwisko, student->dlugosc_nazwiska, nazwisko);
	return student;
}

DATA_MY_STUDENT* DATA_MY_STUDENT_INPUT()
{
	/*======================================================
	* uwazam ze takie drobne fragmenty tekstu sa zbyt mala
	* rzecza zeby przenosic je do systemu obslugi bledow i
	* komunikatow, chociaz w niektorych przepadkach tak
	* wlasnie zrobilem (menu).
	======================================================*/
	char nazwisko[256];
	int rok_urodzenia;
	enum KIERUNEK_STUDIA kierunek_studiow;
	printf("Please input Nazwisko\n");
	scanf_s("%s", nazwisko, 256);
	printf("Please input Rok urodzenia\n");
	scanf_s("%d", &rok_urodzenia);
	printf("Please input Kierunek studiow\n%s - 0\n%s - 1\n%s - 2\n", kierunki_studiow[0], kierunki_studiow[1], kierunki_studiow[2]);
	scanf_s("%d", &kierunek_studiow);
	return DATA_MY_STUDENT_CREATE(nazwisko, rok_urodzenia, kierunek_studiow);
}

void DATA_MY_STUDENT_FREE(void** ptr)
{
	if (ptr)
	{
		if (*ptr)
		{
			DATA_MY_STUDENT** student = (DATA_MY_STUDENT**)ptr;
			if ((*student)->nazwisko)
			{
				free((*student)->nazwisko);
				(*student)->nazwisko = NULL;
			}
			free(*student);
			*student = NULL;
		}
	}
}

void DATA_MY_STUDENT_PRINT(void* ptr)
{
	if (ptr)
	{
		printf("----------\n");

		DATA_MY_STUDENT* student = (DATA_MY_STUDENT*)ptr;

		if (student->nazwisko)
		{
			printf("%s\n", student->nazwisko);
		}
		printf("%d\n%s\n----------\n\n", student->data_urodzenia, kierunki_studiow[student->kierunek_studiow]);
	}
	else
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_DATA_MY_STUDENT_PRINT_EMPTY_POINTER_PASSED_TO_THE_FUNCTION, THE_STACK, NULL, NULL, NULL);
}

int DATA_MY_STUDENT_COMPARE_NAZWISKO(void* ptr1, void* ptr2)
{
	if (!ptr1 || !ptr2)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_DATA_MY_STUDENT_COMPARE_ERROR_NULL_POINTER_PASSED, THE_STACK, NULL, NULL, NULL);
	DATA_MY_STUDENT* student1 = (DATA_MY_STUDENT*)ptr1;
	DATA_MY_STUDENT* student2 = (DATA_MY_STUDENT*)ptr2;
	if (!strcmp(student1->nazwisko, student2->nazwisko))
		return 1;
	return 0;
}
int DATA_MY_STUDENT_COMPARE_DATA_URODZENIA(void* ptr1, void* ptr2)
{
	if (!ptr1 || !ptr2)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_DATA_MY_STUDENT_COMPARE_ERROR_NULL_POINTER_PASSED, THE_STACK, NULL, NULL, NULL);
	DATA_MY_STUDENT* student1 = (DATA_MY_STUDENT*)ptr1;
	DATA_MY_STUDENT* student2 = (DATA_MY_STUDENT*)ptr2;
	if (student1->data_urodzenia == student2->data_urodzenia)
		return 1;
	return 0;
}
int DATA_MY_STUDENT_COMPARE_KIERUNEK_STUDIOW(void* ptr1, void* ptr2)
{
	if (!ptr1 || !ptr2)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_DATA_MY_STUDENT_COMPARE_ERROR_NULL_POINTER_PASSED, THE_STACK, NULL, NULL, NULL);
	DATA_MY_STUDENT* student1 = (DATA_MY_STUDENT*)ptr1;
	DATA_MY_STUDENT* student2 = (DATA_MY_STUDENT*)ptr2;
	if (student1->kierunek_studiow == student2->kierunek_studiow)
		return 1;
	return 0;
}

void DATA_MY_STUDENT_SAVE(void* ptr, FILE* file_ptr)
{
	if (!ptr)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_DATA_MY_STUDENT_SAVE_NULL_POINTER_PASSED, THE_STACK, NULL, NULL, &file_ptr);
	if (!file_ptr)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_DATA_MY_STUDENT_SAVE_NULL_FILE_POINTER_PASSED, THE_STACK, NULL, NULL, &file_ptr);
	DATA_MY_STUDENT* student = (DATA_MY_STUDENT*)ptr;
	if (fwrite(student, sizeof(DATA_MY_STUDENT), 1, file_ptr) != 1)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_DATA_MY_STUDENT_SAVE_FILE_WRITING_ERROR, THE_STACK, NULL, NULL, &file_ptr);
	if (fwrite(student->nazwisko, sizeof(char), student->dlugosc_nazwiska, file_ptr) != student->dlugosc_nazwiska)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_DATA_MY_STUDENT_SAVE_FILE_WRITING_ERROR, THE_STACK, NULL, NULL, &file_ptr);
}

void* DATA_MY_STUDENT_READ(FILE* file_ptr)
{
	if (!file_ptr)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_DATA_MY_STUDENT_READ_NULL_FILE_POINTER_PASSED, THE_STACK, NULL, NULL, &file_ptr);
	DATA_MY_STUDENT* student;
	student = (DATA_MY_STUDENT*)malloc(sizeof(DATA_MY_STUDENT));
	if (!student)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_DATA_MY_STUDENT_READ_MEMORY_ALLOCATION_ERROR, THE_STACK, NULL, NULL, &file_ptr);
	if (fread(student, sizeof(DATA_MY_STUDENT), 1, file_ptr) != 1)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_DATA_MY_STUDENT_READ_FILE_READING_ERROR, THE_STACK, NULL, NULL, &file_ptr);
	student->nazwisko = (char*)malloc((student->dlugosc_nazwiska) * sizeof(char));
	if (!student->nazwisko)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_DATA_MY_STUDENT_READ_MEMORY_ALLOCATION_ERROR, THE_STACK, NULL, NULL, &file_ptr);
	if (fread(student->nazwisko, sizeof(char), student->dlugosc_nazwiska, file_ptr) != student->dlugosc_nazwiska)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_DATA_MY_STUDENT_READ_FILE_READING_ERROR, THE_STACK, NULL, NULL, &file_ptr);
	return (void*)student;
}