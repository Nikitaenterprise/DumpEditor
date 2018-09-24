#include "dump.h"

std::vector<std::vector<double>> dump::Snapshot::getAtomCoordsWithType(int type)
{
	std::vector<std::vector<double>> newAtomCoords;
	int i = 0;
	for (auto it = atomCoords.begin(); it != atomCoords.end(); it++, i++)
	{
		if (getTypeOfAtomById(iD.at(i)) == type)
		{
			newAtomCoords.push_back((*it));
		}
	}
	return newAtomCoords;
}

std::vector<double> dump::Snapshot::getAtomCoordsById(int id)
{
	std::vector<double> newAtomCoords;
	int place;
	int i = 0;
	for (auto it = iD.begin(); it != iD.end(); it++, i++)
	{
		if ((*it) == id) place = i;
	}
	newAtomCoords = atomCoords.at(place);
	return newAtomCoords;
}

void dump::Snapshot::showCoords(const std::vector<std::vector<double>> vec)
{
	for (auto it = vec.begin(); it != vec.end(); it++)
	{
		std::cout << (*it).at(0) << " ";
		std::cout << (*it).at(1) << " ";
		std::cout << (*it).at(2) << std::endl;
	}
}

int dump::Snapshot::getTypeOfAtomById(int id)
{
	int place;
	int i = 0;
	
	for (auto it = iD.begin(); it != iD.end(); it++, i++)
	{
		if ((*it) == id) place = i;
	}
	return type.at(place);
}

void dump::startScan()
{
	std::cout << "Loaded file " << fileName << std::endl;
	while (readSnapshot()) {}
	std::cout << "Reading complete\n";
	file.close();
	std::cout << "Number of snapshots is " << getNumberOfSnapshots() << std::endl;
}

dump::dump(std::string _fileName) : fileName(_fileName)
{
	std::cout << "Searching file " << fileName << std::endl;
	file.open(fileName);
	if (!file.good()) 
		std::cout << "NO " << fileName << " is founded!" << std::endl;
}


dump::~dump()
{
	std::cout << "dump deleted" << std::endl;
}


bool dump::readSnapshot() {

	std::string line;
	std::stringstream ss(line);
	std::string token;

	// ITEM: TIMESTEP
	std::getline(file, line);

	if (file.eof()) 
	{
		return false;
	}

	snapshots.push_back(Snapshot());
	std::vector<Snapshot>::iterator it = snapshots.end() - 1;
	
	

	// 18000000
	std::getline(file, line);
	ss << line;
	ss >> it->timestep;
	ss.str(std::string());
	ss.clear();

	// ITEM: NUMBER OF ATOMS
	std::getline(file, line);

	// 12288
	std::getline(file, line);
	ss << line;
	ss >> it->numberOfAtoms;
	ss.str(std::string());
	ss.clear();

	// ITEM: BOX BOUNDS pp pp pp
	std::getline(file, line);

	/* 0 93.5686
	   0 93.5686
	   0 93.5686 */
	it->box.resize(3);
	for (unsigned int i = 0; i < it->box.size(); i++)
	{
		std::getline(file, line);
		ss << line;
		std::getline(ss, token, ' ');
		it->box[i].push_back(std::stod(token));
		std::getline(ss, token, ' ');
		it->box[i].push_back(std::stod(token));
		ss.str(std::string());
		ss.clear();
		token.clear();
	}

	// ITEM: ATOMS id type xs ys zs q
	std::getline(file, line);
	
	it->atomCoords.resize(it->numberOfAtoms);
	// 1 1 1.46458 1.4138 1.39455 0.00533662 
	for (int i = 0; i < it->numberOfAtoms; i++) 
	{
		std::getline(file, line);
		ss << line;
		std::getline(ss, token, ' ');
		it->iD.push_back(std::stoi(token));
		std::getline(ss, token, ' ');
		it->type.push_back(std::stoi(token));
		std::getline(ss, token, ' ');
		it->atomCoords[i].push_back(std::stod(token));
		std::getline(ss, token, ' ');
		it->atomCoords[i].push_back(std::stod(token));
		std::getline(ss, token, ' ');
		it->atomCoords[i].push_back(std::stod(token));
		std::getline(ss, token, ' ');
		it->charge.push_back(std::stod(token));
		ss.str(std::string());
		ss.clear();
		token.clear();
	}
	return true;
}

dump::Snapshot::Snapshot()
{
}

dump::Snapshot::~Snapshot()
{
}
