#include <iostream>
#include "algorithms.h"

int main()
{
	enum atomTypes {Fe = 1, Cr = 2, O = 3};
	alg::algorithms algForThickness("d", 1, 0, ".min");
	algForThickness.findThickness(3);

	system("pause");
	return 0;
}
