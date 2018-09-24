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

		void findThickness(int);

		algorithms(const std::string, int, int, const std::string);
		~algorithms();
	};
}

