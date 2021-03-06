#pragma once

#include <iostream>
#include <windows.h>
#include <string>
#include "algorithms.h"

void start(std::string &_fileName, std::string &_extension, int &_startSequence, int &_numberOfFiles)
{
	std::cout << "You should put the .exe in folder in wich ";
	std::cout << "you store your dump sequence.\n";
	std::cout << "Now, please, type in dump name in a particular form.\n";
	std::cout << "If you have dump1.min,dump2.min,...,dumpN.min\n\n";
	std::cout << "Now, type in name of the file before each number\n";
	std::cout << "In example you should type : dump\n";

	std::cin >> _fileName;
	if(_fileName.empty()) 
		throw new std::exception(std::string("You didnt type anything").c_str());
	std::cout << "Now, type in extension of the file\n";
	std::cout << "In example you should type : min\n";

	std::cin >> _extension;
	if (_extension.empty())
		throw new std::exception(std::string("You didnt type anything").c_str());
	std::cout << "Now, type in start number of the sequence\n";
	std::cout << "In example you should type : 1\n";

	std::cin >> _startSequence;
	std::cout << "Now, type in number of files\n";
	std::cout << "In example you should type : N-1\n";

	std::cin >> _numberOfFiles;
	if(_numberOfFiles<0)
		throw new std::exception(std::string("You typed mess").c_str());
}

void params(int &_typeOfAtom, int &_numberOfSnapshot)
{
	std::cout << "Type in atom type with what you want work with\n";
	std::cin >> _typeOfAtom;
	if (_typeOfAtom < 0)
		throw new std::exception(std::string("You typed mess").c_str());

	std::cout << "Type in number of snapshot in every dump wich will be analised\n";
	std::cout << "For example, if you have 4 snapshots in every dump and you will\n";
	std::cout << "type 2, then only third snapshot from every dump will be analised\n";
	std::cin >> _numberOfSnapshot;
	if (_numberOfSnapshot < 0)
		throw new std::exception(std::string("You typed mess").c_str());
}

int main(int argv, char *argc[])
{
	//Для работы кириллицы при указании пути к файлу
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	std::string fileName;
	std::string extension;
	int startSequence;
	int numberOfFiles;
	int typeOfAtom = 3;
	int numberOfSnapshot = 0;
	
	try
	{
		start(fileName, extension, startSequence, numberOfFiles);
		params(typeOfAtom, numberOfSnapshot);
		alg::algorithms algForThickness(fileName, startSequence, numberOfFiles, "." + extension);
		algForThickness.thickness(typeOfAtom, numberOfSnapshot);
	}
	catch (const std::exception *ex) { std::cout << ex->what() << std::endl; }
	catch (...) { std::cout << "Something went wrong\n"; };


	system("pause");
	return 0;
}
