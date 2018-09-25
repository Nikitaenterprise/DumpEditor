#include <iostream>
#include <windows.h>
#include "algorithms.h"

int main(int argv, char *argc[])
{
	//Для работы кириллицы при указании пути к файлу
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	alg::algorithms algForThickness("dump_", 4, 0, ".min");
	algForThickness.findThickness(3);

	system("pause");
	return 0;
}
