#pragma once
   
#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


class dump
{
private:
	class Snapshot
	{
	public:
		int timestep;
		int numberOfAtoms;
		
		std::vector<std::vector<double>> box;
		std::vector<short int> iD;
		std::vector<short int> type;
		std::vector<double> charge;
		std::vector<std::vector<double>> atomCoords;

		void showCoords(const std::vector<std::vector<double>>);

		int getTypeOfAtomById(int);
		std::vector<std::vector<double>> getAtomCoordsWithType(int);
		std::vector<double> getAtomCoordsById(int);

		Snapshot();
		~Snapshot();
	};
	bool readSnapshot();

	std::string fileName;
	std::fstream file;

public:
	
	std::string getFileName() { return fileName; };
	int getNumberOfSnapshots() { return static_cast<int>(snapshots.size()); };
	void startScan();

	std::vector<Snapshot> snapshots;

	dump(std::string);
	~dump();
};

