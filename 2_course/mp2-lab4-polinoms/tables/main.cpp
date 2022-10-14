#include <iostream>

#include "menu.h"

int main() {
	try {
		other::c_menu menu;
		menu.init();
	}
	catch (const std::exception& ex) { std::cout << ex.what(); }
	system("pause");
	return 0;

}
