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
		Snapshot();
		~Snapshot();

		int timestep = 0;
		int numberOfAtoms = 0;
		
		std::vector<std::vector<double>> box;
		std::vector<unsigned int> iD;
		std::vector<unsigned int> type;
		std::vector<double> charge;
		std::vector<std::vector<double>> atomCoordinates;
		std::vector<std::vector<double>> atomForces;
		std::vector<std::vector<double>> atomVelocities;

		unsigned int getTypeOfAtomById(int);
		std::vector<std::vector<double>> getAtomCoordsWithType(int);		
	};
	bool readSnapshot();

	std::string fileName;
	std::ifstream file;

public:
	dump(std::string);
	~dump();
	
	std::string getFileName() { return fileName; };
	int getNumberOfSnapshots() { return static_cast<int>(snapshots.size()); };
	void startScan();
	
	int findITEMInSnapshot(const std::string &_line, const std::string _token);

	std::vector<Snapshot> snapshots;

};

