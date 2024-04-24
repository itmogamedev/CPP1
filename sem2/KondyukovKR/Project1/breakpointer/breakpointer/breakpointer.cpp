// breakpointer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

int main()
{
	__asm int 0x0E;
	printf("Hello World\n");
	return 0;
}