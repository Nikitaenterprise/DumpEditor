#pragma once
   
#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>


class dump
{
private:
	class Snapshot
	{
	public:
		int timestep;
		int numberOfAtoms;
		
		std::vector<std::vector<double>> box;
		std::vector<unsigned int> iD;
		std::vector<unsigned int> type;
		std::vector<double> charge;
		std::vector<std::vector<double>> atomCoordinates;
		std::vector<std::vector<double>> atomForces;
		std::vector<std::vector<double>> atomVelocities;

		unsigned int getTypeOfAtomById(int);
		std::vector<std::vector<double>> getAtomCoordsWithType(int);

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
	
	int findITEMInSnapshot(const std::string &_line, const std::string _token);

	std::vector<Snapshot> snapshots;

	dump(std::string);
	~dump();
};

