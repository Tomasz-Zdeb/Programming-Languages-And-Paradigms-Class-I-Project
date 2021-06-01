#include "messages_errors.h"
#include "warning_disabler.h"
/*========================
I - user instruction
C - notification
E - fatal error (shutdown)
==========================*/
static const char *MESSAGER_MESSAGE_TEXT_TAB[] =
{
	"I 0 - push(add) object || 1 - pop(remove) object || 2 - print all objects\n3 - save all         || 4 - read saved         || 5 - remove all objects\n6 - >>>> EXIT << < ",//0
	"I Choose object type\n>STUDENT - 0",//1
	"I ELEMENT REMOVED FROM TOP OF THE STACK:",//2
	"E INTERFACE: Memory allocation error -> at data level",//3
	"C INTERFACE: ADD_OBJECT(...) -> Unknown object type",//4
	"E DATA_MY_STUDENT: Create -> memory allocation error",//5
	"E DATA_MY_STUDENT: Create -> memory initialization error",//6
	"C DATA_MY_STUDENT: Print -> null pointer passed",//7
	"E DATA_MY_STUDENT: Compare -> null pointer passed",//8
	"E DATA_MY_STUDENT: Save -> null file pointer passed",//9
	"E DATA_MY_STUDENT: Save -> null pointer passed",//10
	"E DATA_MY_STUDENT: Save -> file writing error",//11
	"E DATA_MY_STUDENT: Read -> null file pointer passed",//12
	"E DATA_MY_STUDENT: Read -> memory allocation error",//13
	"E DATA_MY_STUDENT: Read -> file reading error",//14
	"C INTERFACE: Menu -> unknown controll sequence",//15
	"E CONTAINER_MY_STACK: Init -> memory allocation error",//16
	"E CONTAINER_MY_STACK: Init -> memory initialization error",//17
	"E CONTAINER_MY_STACK: Push -> memory allocation error",//18
	"E CONTAINER_MY_STACK: Push -> memory initialization error",//19
	"C CONTAINER_MY_STACK: Pop -> STACK IS ALREADY EMPTY - Nothing to pop",//20
	"C CONTAINER_MY_STACK: Pop -> STACK IS EMPTY - Nothing to print",//21
	"E CONTAINER_MY_STACK: Save -> memory allocation error",//22
	"E CONTAINER_MY_STACK: Save -> file opening error",//23
	"E CONTAINER_MY_STACK: Save -> file writing error",//24
	"E CONTAINER_MY_STACK: Read -> file openning error",//25
	"E CONTAINER_MY_STACK: Read -> memory allocation error",//26
	"E CONTAINER_MY_STACK: Read -> memory initialization error",//27
	"E CONTAINER_MY_STACK: Read -> file reading error",//28
};

void MESSAGER_EXECUTE(enum MESSAGER_MESSAGES instruction, CONTAINER_MY_STACK** stack, CONTAINER_MY_STACK** temp, __int64** file_desc, FILE** file_ptr)
{
	puts(MESSAGER_MESSAGE_TEXT_TAB[instruction] + 2);
	if (MESSAGER_MESSAGE_TEXT_TAB[instruction][0] == 'E')
		INTERFACE_EXIT(stack,temp,file_desc,file_ptr);
}