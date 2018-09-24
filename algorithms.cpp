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
		
		std::vector<std::vector<double>> x(precision, std::vector<double>(2)), _x(precision, std::vector<double>(2));
		std::vector<double> y(precision), _y(precision);

		/*for (const auto it : vec)
		{
			std::cout << it.at(0) << " ";
			std::cout << it.at(1) << " ";
			std::cout << it.at(2) << std::endl;
		}
*/
		std::cout << "number of atoms " << vec.size() << std::endl;

		std::ofstream out("out" + std::to_string(outputCounter) + ".txt");
		std::ofstream out1("out" + std::to_string(1) + ".txt");
		for (int i = 0; i < precision; i++)
		{
			int counter = 0;
			for (auto it : vec)
			{
				if ((smallestZ + i * step) < it.at(2) && (smallestZ + step + i * step) > it.at(2)) counter++;
			}
			x[i][0] = smallestZ + i * step;
			y[i] = counter;
			std::cout << x[i][0] << "	" << x[i][1] << "	" << y[i] << std::endl;
			out << x[i][0] << "	" << x[i][1] << "	" << y[i] << std::endl;
		}
		GaussNewton GN;
		std::vector<double> b = GN.optimise(x, y, 3);
		std::cout << "we are here\n";
		std::cout << b[0] << " " << b[1] << " " << b[2] << std::endl;
		for (int j = 0; j < precision; j++)
		{
			_x[j][0] = j;
			_y[j] = 2 * exp(-pow((_x[j][0] - 10), 2) / (2 * pow(1.3, 2)));
			out1 << _x[j][0] << "	" << _x[j][1] << "	" << _y[j] << std::endl;
		}

		GaussNewton GN1;
		std::vector<double> b1 = GN1.optimise(_x, _y, 3);
		std::cout << b1[0] << " " << b1[1] << " " << b1[2] << std::endl;
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