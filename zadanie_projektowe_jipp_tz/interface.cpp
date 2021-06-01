#include "interface.h"
#include "messages_errors.h"
#include "warning_disabler.h"

CONTAINER_MY_STACK** THE_STACK;
void INTERFACE_MENU()
{
	int ops;
	CONTAINER_MY_STACK* stack  = CONTAINER_MY_STACK_INIT();
	THE_STACK = &stack;
	while (1)
	{
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_INTERFACE_MENU_USER_INSTRUCTION, &stack, NULL, NULL, NULL);
		scanf_s("%d", &ops);
		char filename[] = { "data.bin" };
		switch (ops)
		{
		case 0:
			if (!stack)
			{
				stack = CONTAINER_MY_STACK_INIT();
			}
			INTERFACE_ADD_OBJECT(&stack);
			break;
		case 1:
			INTERFACE_POP(&stack);
			break;
		case 2:
			INTERFACE_PRINT_ALL_OBJECTS(stack);
			break;
		case 3:
			INTERFACE_SAVE(stack,filename);
			break;
		case 4:
			INTERFACE_READ(&stack, filename);
			break;
		case 5:
			INTERFACE_CLEAR_STACK(&stack);
			break;
		case 6:
			INTERFACE_EXIT(&stack, NULL, NULL, NULL);
			break;
		//case 7:
			//CONTAINER_MY_STACK_SEARCH(stack);
			//break;
		default:
			MESSAGER_EXECUTE(MESSAGER_MESSAGES_INTERFACE_UNKNOWN_CONTROL_SEQUENCE, &stack, NULL, NULL, NULL);
			break;
		}
	}
}

void INTERFACE_ADD_OBJECT(CONTAINER_MY_STACK** top)
{
	int typ;
	DATA_MY_STUDENT* student = NULL;
	CONTAINER_MY_STACK temp;

	MESSAGER_EXECUTE(MESSAGER_MESSAGES_INTERFACE_ADD_OBJECT_USER_INSTRUCTION, top, NULL, NULL, NULL);
	scanf_s("%d", &typ);

	switch (typ)
	{
	case 0:
		student = (DATA_MY_STUDENT*)malloc(sizeof(DATA_MY_STUDENT));
		if (!student)
		{
			MESSAGER_EXECUTE(MESSAGER_MESSAGES_INTERFACE_MEMORY_ALLOCATION_ERROR_AT_DATA_LEVEL, top, NULL, NULL, NULL);
		}
		student = DATA_MY_STUDENT_INPUT();
		temp.data = (void*)student;
		temp.free_fun = DATA_MY_STUDENT_FREE;
		temp.compare_fun = DATA_MY_STUDENT_COMPARE_NAZWISKO; /* ADNOTACJA do: CONTAINER_MY_STACK_SEARCH(...)
															 ======================================================================================================
															 nie wiedzialem jak to rozwiazac: czy stworzyc trzy oddzielne pola na kazdy rodzaj funkcji porownawczej
															 ale to mogloby naruszyc przeciez niezaleznosc kontenera od danych. Ale z drugiej strony kazdy element
															 stosu moglby miec miejsce na trzy funkcje porownawce i nie koniecznie korzystac ze wszystkich
															 ====================================================================================================*/
		temp.print_fun = DATA_MY_STUDENT_PRINT;
		temp.save_fun = DATA_MY_STUDENT_SAVE;
		temp.read_fun = DATA_MY_STUDENT_READ;
		temp.lower_element = NULL;
		temp.higher_element = NULL;
		(*top) = CONTAINER_MY_STACK_PUSH((*top),&temp);
		break;
	default:
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_INTERFACE_ADD_OBJECT_UNKNOWN_OBJECT_TYPE, top, NULL, NULL, NULL);
		return;
	}
}

void INTERFACE_PRINT_ALL_OBJECTS(CONTAINER_MY_STACK* top)
{
	CONTAINER_MY_STACK_PRINT(top);
}

void INTERFACE_POP(CONTAINER_MY_STACK** top)
{
	/* =================================================================================
	* Gdyby chcialo sie jakos wykorzystac ten obiekt to mozna zrobic to tutaj w interfejsie
	* domyslnie wypisuje sie tylko ten ususniety element do stoud a nastepnie go zwalnie
	====================================================================================*/
	CONTAINER_MY_STACK* temp = CONTAINER_MY_STACK_POP(top);
	if (temp)
	{
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_INTERFACE_POP_USER_INSTRUCTION,top,NULL,NULL,NULL);
		temp->print_fun(temp->data);
		temp->free_fun(&temp->data);
		free(temp);
		temp = NULL;
	}
}

void INTERFACE_SAVE(CONTAINER_MY_STACK* top, char* filename)
{
	CONTAINER_MY_STACK_SAVE(top, filename);
}

void INTERFACE_READ(CONTAINER_MY_STACK** top, char* filename)
{
	*top = CONTAINER_MY_STACK_READ(top, filename);
}

void INTERFACE_CLEAR_STACK(CONTAINER_MY_STACK** top)
{
	CONTAINER_MY_STACK_FREE(top);
}

void INTERFACE_DEALLOC(CONTAINER_MY_STACK** stack, CONTAINER_MY_STACK** temp, __int64** file_desc, FILE** file_ptr)
{
	CONTAINER_MY_STACK_FREE(stack);
	CONTAINER_MY_STACK_FREE(temp);
	if (file_desc)
	{
		if (*file_desc)
		{
			free(*file_desc);
		}
		*file_desc = NULL;
	}
	if (file_ptr)
	{
		if (*file_ptr)
		{
			fclose(*file_ptr);
		}
		*file_ptr = NULL;
	}
}

void INTERFACE_EXIT(CONTAINER_MY_STACK** stack, CONTAINER_MY_STACK** temp, __int64** file_desc, FILE** file_ptr)
{
	INTERFACE_DEALLOC(stack, temp, file_desc, file_ptr);
	exit(1);
}