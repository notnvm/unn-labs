#include <iostream>
#include "arithmetic.h"

void user_interface();

void main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "[!] Arithmetical expressions\n";
	user_interface();

	system("pause");
}
