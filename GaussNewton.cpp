#include "GaussNewton.h"

GaussNewton::GaussNewton()
{
}

GaussNewton::~GaussNewton()
{
}

std::vector<std::vector<double>> GaussNewton::calculateResiduals(std::vector<std::vector<double>> &x, std::vector<double> &y, std::vector<double> &b)
{
	std::vector<std::vector<double>> res(y.size(), std::vector<double>(2));

	for (unsigned int i = 0; i < res.size(); i++)
		res[i][0] = findY(x[i][0], b) - y[i];

	return res;
}

double GaussNewton::findY(double &x, std::vector<double> &b)
{
	// y = a*exp(-(x-b)^2/(2c^2))
	return b[0] * exp(-pow((x - b[1]), 2) / (2 * pow(b[2], 2)));
}

std::vector<std::vector<double>> GaussNewton::jacob(std::vector<double> &b, std::vector<std::vector<double>> &x, int numberOfObservations)
{
	int numberOfVariables = b.size();
	std::vector<std::vector<double>> jc(numberOfObservations, std::vector<double>(numberOfVariables));

	for (int i = 0; i < numberOfObservations; i++)
	{
		for (int j = 0; j < numberOfVariables; j++)
			jc[i][j] = derivative(x[i][0], b, j);
	}
	return jc;
}

double GaussNewton::derivative(double &x, std::vector<double> &b, int bIndex)
{
	double alpha = 1e-6;
	std::vector<double> bCopy = b;
	bCopy[bIndex] += alpha;
	double y1 = findY(x, bCopy);
	bCopy = b;
	bCopy[bIndex] -= alpha;
	double y2 = findY(x, bCopy);
	return (y1 - y2) / (2 * alpha);
}

std::vector<std::vector<double>> GaussNewton::transjacob(std::vector<std::vector<double>> &JArray, std::vector<std::vector<double>> &res)
{
	matrix<double> r(res); 
	matrix<double> J(JArray);
	matrix<double> JT = transpose(J);
	matrix<double> JTJ = JT * J; // JT * J
	JTJ.inverse(); // (JT * J)^-1
	matrix<double> JTJ_1JTr = JTJ * JT * r;// (JT * J)^-1 * JT * r
	return JTJ_1JTr.getValues();
}

std::vector<double> GaussNewton::optimise(std::vector<std::vector<double>> &x, std::vector<double> &y, std::vector<double> &b)
{
	int maxIteration = 5000;
	double oldError = 100;
	double precision = 1e-8;
	std::vector<double> b2 = b;
	double gamma = .01;
	for (int i = 0; i < maxIteration; i++)
	{
		std::vector<std::vector<double>> res = calculateResiduals(x, y, b2);
		double error = calculateError(res);
		
		//std::cout << "Iteration : " << i << ", Error-diff: " << abs(oldError - error) << ", b = ";
		//for (unsigned int k = 0; k < b2.size(); k++) { std::cout << std::to_string(b2[k]) << " "; }
		//std::cout << "\n";

		if (abs(oldError - error) <= precision)
			break;

		oldError = error;
		std::vector<std::vector<double>> jacobs = jacob(b2, x, y.size());
		std::vector<std::vector<double>> values = transjacob(jacobs, res);
		for (unsigned int j = 0; j < values.size(); j++)
			b2[j] -= gamma * values[j][0];

	}
	return b2;

}

std::vector<double> GaussNewton::optimise(std::vector<std::vector<double>> &x, std::vector<double> &y, int numberOfParameters)
{
	std::vector<double> b(numberOfParameters);

	for (unsigned int i = 0; i < b.size(); i++)
		b[i] = 200;
	
	return optimise(x, y, b);
}

double GaussNewton::calculateError(std::vector<std::vector<double>> &res)
{
	double sum = 0;

	for (unsigned int i = 0; i < res.size(); i++)
		sum += pow(res[i][0],2);

	return sqrt(sum);
}

