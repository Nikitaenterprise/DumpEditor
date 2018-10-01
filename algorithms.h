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

		void thickness(int atomType, int numberOfSnapshot);
		double findFWHM(const std::vector<std::vector<double>> &vec);
		algorithms(const std::string, int, int, const std::string);
		~algorithms();
	};
}

