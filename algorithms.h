#pragma once
#include "dump.h"
#include "GaussNewton.h"
#include <algorithm>

namespace alg
{
	class algorithms
	{
	protected:

		std::vector<dump*> dumpSequence;

	public:

		algorithms(const std::string, int, int, const std::string);
		algorithms(const std::string &_fileName);
		~algorithms();

		void thickness(int atomType, int numberOfSnapshot, bool singleFrame = true);
		double findFWHM(const std::vector<std::vector<double>> &vec);
		void sortByZ(std::vector<std::vector<double>> &vec);
	};
}
int sayHi(int a); 

