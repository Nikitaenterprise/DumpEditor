#pragma once
#include "matrix.h"
#include <vector>
#include <string>
#include <iostream>

class GaussNewton
{
public:

	GaussNewton();
	~GaussNewton();

	std::vector<std::vector<double>> calculateResiduals(std::vector<std::vector<double>> &x, std::vector<double> &y, std::vector<double> &b);
	double findY(double &x, std::vector<double> &b);
	std::vector<std::vector<double>> jacob(std::vector<double> &b, std::vector<std::vector<double>> &x, int numberOfObservations);
	double derivative(double &x, std::vector<double> &b, int bIndex);
	std::vector<std::vector<double>> transjacob(std::vector<std::vector<double>> &JArray, std::vector<std::vector<double>> &res);
	std::vector<double> optimise(std::vector<std::vector<double>> &x, std::vector<double> &y, std::vector<double> &b);
	std::vector<double> optimise(std::vector<std::vector<double>> &x, std::vector<double>  &y, int numberOfParameters);
	double calculateError(std::vector<std::vector<double>> &res);
};