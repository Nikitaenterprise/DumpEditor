#include "algorithms.h"


void alg::algorithms::findThickness(int atomType)
{
	int numberOfSnapshot = 0;
	int outputCounter = 0;
	for (auto &dump : dumpSequence)
	{
		(*dump).startScan();
		std::vector<std::vector<double>> vec = (*dump).snapshots.at(numberOfSnapshot).getAtomCoordsWithType(atomType);

		//Sorting with lambda
		std::sort(vec.begin(), vec.end(), [](const std::vector<double>& a, const std::vector<double>& b) {
			return a.at(2) < b.at(2);
		});

		double smallestZ = vec.at(0).at(2), biggestZ = vec.at(vec.size() - 1).at(2);
		smallestZ = 0;
		int precision = 100;
		double step = (biggestZ - smallestZ) / precision;
		std::cout << smallestZ << " " << biggestZ << " " << step << std::endl;
		
		std::vector<std::vector<double>> x(precision, std::vector<double>(2));
		std::vector<double> y(precision);

		std::ofstream out("out" + std::to_string(outputCounter) + ".txt");
		for (int i = 0; i < precision; i++)
		{
			int counter = 0;
			for (auto it : vec)
			{
				if ((smallestZ + i * step) < it.at(2) && (smallestZ + step + i * step) > it.at(2)) counter++;
			}
			x[i][0] = smallestZ + i * step;
			y[i] = counter;
			out << x[i][0] << "	" << x[i][1] << "	" << y[i] << std::endl;
		}
		GaussNewton GN;
		std::vector<double> b = GN.optimise(x, y, 3);
		std::cout << b[0] << " " << b[1] << " " << b[2] << std::endl;
		
		(*dump).~dump();
		outputCounter++;
	}
	
}


alg::algorithms::algorithms(const std::string _fileName, int startNumber, int endNumber, const std::string fileExtension)
{
	for (int i = startNumber; i <= startNumber + endNumber; i++)
	{
		dumpSequence.push_back(new dump(_fileName + std::to_string(i) + fileExtension));
		dumpSequence.begin();
	}
}


alg::algorithms::~algorithms()
{
}