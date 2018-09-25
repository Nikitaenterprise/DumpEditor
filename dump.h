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
		std::vector<int> iD;
		std::vector<int> type;
		std::vector<double> charge;
		std::vector<std::vector<double>> atomCoordinates;
		std::vector<std::vector<double>> atomForces;
		std::vector<std::vector<double>> atomVelocities;


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
	
	int findITEMInSnapshot(const std::string &_line, const std::string _token);

	std::vector<Snapshot> snapshots;

	dump(std::string);
	~dump();
};

