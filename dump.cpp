#include "dump.h"

dump::Snapshot::Snapshot()
{
}

dump::Snapshot::~Snapshot()
{
}

std::vector<std::vector<double>> dump::Snapshot::getAtomCoordsWithType(int type)
{
	std::vector<std::vector<double>> newAtomCoords;
	int i = 0;
	for (auto it = atomCoordinates.begin(); it != atomCoordinates.end(); it++, i++)
	{
		if (getTypeOfAtomById(iD[i]) == type)
			newAtomCoords.push_back(*it);
	}
	return newAtomCoords;
}

unsigned int dump::Snapshot::getTypeOfAtomById(int id)
{
	unsigned int i = 0;
	for (auto it = iD.begin(); it!= iD.end(); it++, i++)
		if (*it == id) return type[i];
	return NULL;
}

dump::dump(std::string _fileName) : fileName(_fileName)
{
	
}

dump::~dump()
{
}

void dump::startScan()
{
	file.open(fileName);
	if (!file.good())
		std::cout << "NO " << fileName << " is founded!" << std::endl;
	std::cout << "Loaded file " << fileName << std::endl;
	while (readSnapshot()) {}
	file.close();
}

int dump::findITEMInSnapshot(const std::string &_line, const std::string _token)
{
	return _line.find(_token);
}

bool dump::readSnapshot() 
{
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

	// There is some variants of dumps
	// Each dump can have id`s, types, coordinates
	// charges, velocities, forces, etc.
	// For example :
	// ITEM: ATOMS id type xs ys zs q ...
	// Next lines searchin for this keywords
	std::getline(file, line);
	if (findITEMInSnapshot(line, std::string("id")) > 0) it->iD.resize(it->numberOfAtoms);
	if (findITEMInSnapshot(line, std::string("type")) > 0) it->type.resize(it->numberOfAtoms);
	if ((findITEMInSnapshot(line, std::string("q")) > 0) ||
		(findITEMInSnapshot(line, std::string("Charge")) > 0)) it->charge.resize(it->numberOfAtoms);
	if ((findITEMInSnapshot(line, std::string("x")) > 0) ||
	    (findITEMInSnapshot(line, std::string("y")) > 0) ||
	    (findITEMInSnapshot(line, std::string("z")) > 0)) it->atomCoordinates.resize(it->numberOfAtoms);
	if ((findITEMInSnapshot(line, std::string("vx")) > 0) ||
		(findITEMInSnapshot(line, std::string("vy")) > 0) ||
		(findITEMInSnapshot(line, std::string("vz")) > 0)) it->atomVelocities.resize(it->numberOfAtoms);
	if ((findITEMInSnapshot(line, std::string("fx")) > 0) ||
		(findITEMInSnapshot(line, std::string("fy")) > 0) ||
		(findITEMInSnapshot(line, std::string("fz")) > 0)) it->atomForces.resize(it->numberOfAtoms);

	// 1 1 1.46458 1.4138 1.39455 0.00533662 
	for (int i = 0; i < it->numberOfAtoms; i++) 
	{
		std::getline(file, line);
		ss << line;

		if (!it->iD.empty())
		{
			std::getline(ss, token, ' ');
			it->iD[i] = (std::stoi(token));
		}
		if (!it->type.empty())
		{
			std::getline(ss, token, ' ');
			it->type[i] = (std::stoi(token));
		}
		if (!it->atomCoordinates.empty())
		{
			std::getline(ss, token, ' ');
			it->atomCoordinates[i].push_back(std::stod(token));
			std::getline(ss, token, ' ');
			it->atomCoordinates[i].push_back(std::stod(token));
			std::getline(ss, token, ' ');
			it->atomCoordinates[i].push_back(std::stod(token));
		}
		if (!it->charge.empty())
		{
			std::getline(ss, token, ' ');
			it->charge[i] = (std::stod(token));
		}
		if (!it->atomVelocities.empty())
		{
			std::getline(ss, token, ' ');
			it->atomVelocities[i].push_back(std::stod(token));
			std::getline(ss, token, ' ');
			it->atomVelocities[i].push_back(std::stod(token));
			std::getline(ss, token, ' ');
			it->atomVelocities[i].push_back(std::stod(token));
		}
		if (!it->atomForces.empty())
		{
			std::getline(ss, token, ' ');
			it->atomForces[i].push_back(std::stod(token));
			std::getline(ss, token, ' ');
			it->atomForces[i].push_back(std::stod(token));
			std::getline(ss, token, ' ');
			it->atomForces[i].push_back(std::stod(token));
		}
		
		ss.str(std::string());
		ss.clear();
		token.clear();
	}	
	return true;
}

