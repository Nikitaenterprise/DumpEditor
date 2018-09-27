#include <iostream>
#include <windows.h>
#include <string>
#include "algorithms.h"

int main(int argv, char *argc[])
{
	//Для работы кириллицы при указании пути к файлу
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	std::cout << "You should put the .exe in folder in wich ";
	std::cout << "you store your dump sequence.\n";
	std::cout << "Now, please, type in dump name in a particular form.\n";
	std::cout << "If you have dump1.min,dump2.min,...,dumpN.min\n\n";
	std::cout << "Now, type in name of the file before each number\n";
	std::cout << "In example you should type : dump\n";
	std::string fileName = "d";
	//std::cin >> fileName;
	std::cout << "You typed : " << fileName << std::endl;
	std::cout << "Now, type in extension of the file\n";
	std::cout << "In example you should type : min\n";
	std::string extension = "min";
	//std::cin >> extension;
	std::cout << "You typed : " << extension << std::endl;
	std::cout << "Now, type in start number of the sequence\n";
	std::cout << "In example you should type : 1\n";
	int startSequence = 1;
	//std::cin >> startSequence;
	std::cout << "You typed : " << startSequence << std::endl;
	std::cout << "Now, type in number of files\n";
	std::cout << "In example you should type : N-1\n";
	int numberOfFiles = 0;
	//std::cin >> numberOfFiles;

	alg::algorithms algForThickness(fileName, startSequence, numberOfFiles, "." + extension);
	algForThickness.findThickness(3);

	system("pause");
	return 0;
}
