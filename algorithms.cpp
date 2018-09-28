#include "algorithms.h"


void alg::algorithms::findThickness(int atomType, int numberOfSnapshot)
{
	int outputCounter = 0;
	std::ofstream out("out.txt");
	for (auto &dump : dumpSequence)
	{
		try
		{
			(*dump).startScan();
			auto vec = (*dump).snapshots.at(numberOfSnapshot).getAtomCoordsWithType(atomType);
			
			//Sorting with lambda
			std::sort(vec.begin(), vec.end(), [](const std::vector<double>& a, const std::vector<double>& b) {
				return a.at(2) < b.at(2);
			});

			double smallestZ = 0, biggestZ = vec[vec.size() - 1][2];
			int precision = 100;
			double step = (biggestZ - smallestZ) / precision;
		
			std::vector<double> x(precision);
			std::vector<double> y(precision);

			for (int i = 0; i < precision; i++)
			{
				int counter = 0;
				
				for (auto it : vec)
					if ((smallestZ + i * step) < it.at(2) && (smallestZ + step + i * step) > it.at(2)) counter++;

				x[i] = smallestZ + i * step;
				y[i] = counter;
			}
			GaussNewton GN;
			std::vector<double> b = GN.optimise(x, y, 3);
			std::cout << b[0] << " " << b[1] << " " << b[2] << std::endl;
			double FWHM = 2 * sqrt(2 * log(2))*b[2];
			std::cout << "FWHM = " << FWHM << std::endl;
			out << outputCounter << "	" << FWHM << std::endl;
			outputCounter++;
		}
		catch (const std::exception *ex)
		{
			std::cout << ex->what() << std::endl;
		}
		catch (...) { std::cout << "Something went wrong\n"; }
		(*dump).~dump();
	}
	out.close();
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