#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "container.h"
#include "messages_errors.h"
#include "warning_disabler.h"

/*umo¿liwia dzialanie systemowi bledow i powiadomien
chociaz na poziomie kontenera wiekszosc funkcji ma
dostep do wskaznika do stosu*/
extern CONTAINER_MY_STACK** THE_STACK;

size_t CONTAINER_MY_STACK::no_elements = 0;

CONTAINER_MY_STACK* CONTAINER_MY_STACK_INIT()
{
	CONTAINER_MY_STACK::no_elements = 0;
	CONTAINER_MY_STACK* base = (CONTAINER_MY_STACK*)malloc(sizeof(CONTAINER_MY_STACK));
	if (!base)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_INIT_MEMORY_ALLOCATION_ERROR, &base, NULL, NULL, NULL);
	memset((void*)base, 0, sizeof(CONTAINER_MY_STACK));
	if (!base)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_INIT_MEMORY_INITIALIZATION_ERROR, &base, NULL, NULL, NULL);
	return base;
}

CONTAINER_MY_STACK* CONTAINER_MY_STACK_PUSH(CONTAINER_MY_STACK* top, CONTAINER_MY_STACK* to_add)
{
	if (top->data == NULL)
	{
		top->data = to_add->data;
		top->free_fun = to_add->free_fun;
		top->print_fun = to_add->print_fun;
		top->compare_fun = to_add->compare_fun;
		top->save_fun = to_add->save_fun;
		top->read_fun = to_add->read_fun;
		top->no_elements++;
		return top;
	}
	else
	{
		CONTAINER_MY_STACK* on_top = (CONTAINER_MY_STACK*)malloc(sizeof(CONTAINER_MY_STACK));
		if (!on_top)
			MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_PUSH_MEMORY_ALLOCATION_ERROR, THE_STACK, &to_add, NULL, NULL);
		memset((void*)on_top, 0, sizeof(CONTAINER_MY_STACK));
		if (!on_top)
			MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_PUSH_MEMORY_INITIALIZATION_ERROR, THE_STACK, &to_add, NULL, NULL);
		top->higher_element = (void*)on_top;
		on_top->lower_element = (void*)top;

		on_top->data = to_add->data;
		on_top->free_fun = to_add->free_fun;
		on_top->print_fun = to_add->print_fun;
		on_top->compare_fun = to_add->compare_fun;
		on_top->save_fun = to_add->save_fun;
		on_top->read_fun = to_add->read_fun;

		on_top->no_elements++;

		return on_top;
	}
}

void CONTAINER_MY_STACK_FREE(CONTAINER_MY_STACK** top)
{
	if (top)
	{
		if (*top)
		{
			CONTAINER_MY_STACK* next, * to_free = *top;
			for (; CONTAINER_MY_STACK::no_elements > 0; CONTAINER_MY_STACK::no_elements--)
			{
				if (to_free)
				{
					if ((to_free)->data)
						(to_free)->free_fun((void**)&(to_free)->data);
					next = (CONTAINER_MY_STACK*)to_free->lower_element;
					free(to_free);
					to_free = next;
					next = NULL;
				}
			}
			*top = NULL;
		}
	}
}

CONTAINER_MY_STACK* CONTAINER_MY_STACK_POP(CONTAINER_MY_STACK** top)
{
	if (*top)
	{
		CONTAINER_MY_STACK* to_return = *top;
		*top = (CONTAINER_MY_STACK*)to_return->lower_element;
		if (*top)
		{
			(*top)->higher_element = NULL;

		}
		(to_return)->no_elements--;
		if (!to_return->data)
		{
			MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_POP_STACK_IS_EMPY_COMUNICATE, top, NULL, NULL, NULL);
			return NULL;
		}
		to_return->higher_element = NULL;
		to_return->lower_element = NULL;

		return to_return;
	}
	else
	{
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_POP_STACK_IS_EMPY_COMUNICATE, top, NULL, NULL, NULL);
		return NULL;
	}
}

void CONTAINER_MY_STACK_PRINT(CONTAINER_MY_STACK* top)
{
	if (top)
	{
		CONTAINER_MY_STACK* element = top;
		size_t iterator = CONTAINER_MY_STACK::no_elements;
		for (; iterator > 0; iterator--)
		{
			if (element->data)
			{
				element->print_fun((void*)element->data);
			}
			element = (CONTAINER_MY_STACK*)element->lower_element;
		}
		if (CONTAINER_MY_STACK::no_elements == 0)
		{
			MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_PRINT_STACK_IS_EMPY_COMUNICATE, THE_STACK, NULL, NULL, NULL);
		}
	}
	else
	{
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_PRINT_STACK_IS_EMPY_COMUNICATE,THE_STACK, NULL, NULL, NULL);
	}
}

void CONTAINER_MY_STACK_SAVE(CONTAINER_MY_STACK* top, char* filename)
{
	size_t iterator;
	CONTAINER_MY_STACK* stack_element = (CONTAINER_MY_STACK*)top;
	unsigned int no_items = CONTAINER_MY_STACK::no_elements;
	__int64 filepos = 0, * file_desc = (__int64*)malloc((no_items + 1) * sizeof(__int64));
	if (!file_desc)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_SAVE_MEMORY_ALLOCATION_ERROR, THE_STACK, NULL, &file_desc, NULL);
	FILE* file_ptr = fopen(filename, "wb");
	if (!file_ptr)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_SAVE_FILE_OPENING_ERROR, THE_STACK, NULL, &file_desc, &file_ptr);
	if (fwrite(&no_items, sizeof(unsigned int), 1, file_ptr) != 1)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_SAVE_FILE_WRITING_ERROR, THE_STACK, NULL, &file_desc, &file_ptr);
	_fseeki64(file_ptr, (no_items + 1) * sizeof(__int64), SEEK_CUR);

	for (iterator = no_items; iterator > 0; iterator--)
	{
		file_desc[no_items - iterator] = ftell(file_ptr);
		if (fwrite(stack_element, sizeof(CONTAINER_MY_STACK), 1, file_ptr) != 1)
			MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_SAVE_FILE_WRITING_ERROR, THE_STACK, NULL, &file_desc, &file_ptr);
		stack_element->save_fun(stack_element->data, file_ptr);
		stack_element = (CONTAINER_MY_STACK*)stack_element->lower_element;
	}
	file_desc[no_items] = ftell(file_ptr);

	_fseeki64(file_ptr, sizeof(unsigned int), SEEK_SET);
	if (fwrite(file_desc, sizeof(__int64), no_items + 1, file_ptr) != no_items + 1)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_SAVE_FILE_WRITING_ERROR, THE_STACK, NULL, &file_desc, &file_ptr);
	if (file_ptr)
		fclose(file_ptr);
	file_ptr = NULL;
	if (file_desc)
		free(file_desc);
	file_desc = NULL;
}

CONTAINER_MY_STACK* CONTAINER_MY_STACK_READ(CONTAINER_MY_STACK** top, char* filename)
{
	if (*top)
		CONTAINER_MY_STACK_FREE(top);
	CONTAINER_MY_STACK::no_elements = 0;
	size_t iterator, rec, no_items;
	__int64* file_desc = NULL;

	FILE* file_ptr = fopen(filename, "rb");
	if (!file_ptr)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_READ_FILE_OPENING_ERROR, THE_STACK, NULL, &file_desc, &file_ptr);
	*top = CONTAINER_MY_STACK_INIT();
	if (fread(&no_items, sizeof(unsigned int), 1, file_ptr) != 1)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_READ_FILE_READING_ERROR, THE_STACK, NULL, &file_desc, &file_ptr);
	file_desc = (__int64*)malloc((no_items) * sizeof(__int64));
	if (!file_desc)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_READ_MEMORY_ALLOCATION_ERROR, THE_STACK, NULL, &file_desc, &file_ptr);
	if (fread(file_desc, sizeof(__int64), no_items + 1, file_ptr) != no_items + 1)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_READ_FILE_READING_ERROR, THE_STACK, NULL, &file_desc, &file_ptr);
	CONTAINER_MY_STACK* stack_element = (CONTAINER_MY_STACK*)malloc(sizeof(CONTAINER_MY_STACK));
	if (!stack_element)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_READ_MEMORY_ALLOCATION_ERROR, THE_STACK,&stack_element, &file_desc,&file_ptr);
	memset((void*)stack_element, 0, sizeof(CONTAINER_MY_STACK));
	if (!stack_element)
		MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_READ_MEMORY_INITIALIZATION_ERROR, THE_STACK, &stack_element, &file_desc, &file_ptr);
	for (iterator = 0; iterator < no_items; iterator++)
	{
		//stosujemy taka operacje aby iterowac po rekordach od konca pliku, wtedy uzyskamy odpowiedna kolejnosc odczytu
		rec = no_items - iterator - 1;
		_fseeki64(file_ptr, file_desc[rec], SEEK_SET);
		if (fread((void*)stack_element, sizeof(CONTAINER_MY_STACK), 1, file_ptr) != 1)
			MESSAGER_EXECUTE(MESSAGER_MESSAGES_CONTAINER_MY_STACK_READ_FILE_READING_ERROR, THE_STACK, &stack_element, &file_desc, &file_ptr);
		stack_element->data = stack_element->read_fun(file_ptr);
		(*top) = CONTAINER_MY_STACK_PUSH(*top, stack_element);
	}
	free(stack_element);
	stack_element = NULL;
	return *top;
}

void CONTAINER_MY_STACK_SEARCH(CONTAINER_MY_STACK* top)
{
	/*=============================================================================================
	* Usunalem caly kod tej metody poniewaz nie potrafie zaimplementowac jej tak aby kontener
	* i dane pozosaly rozdzielone.Jedynie w implementacji danych wprowadzilem trzy metody porownawcze
	* o wspolnym interfejsie wywolania - Bardzo przepraszam za niezrealizowanie tej funkcjonalnosci.
	===============================================================================================*/
}