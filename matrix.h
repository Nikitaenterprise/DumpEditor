#pragma once
#include <vector>
#include <iostream>
#include <string>

class matrix
{
private:
	int nrows;
	int ncols;
	std::vector<std::vector<double>> data;

public:
	matrix(std::vector<std::vector<double>> dat);
	matrix(int nrow, int ncol);

	int getNrows();
	void setNrows(int nrows);
	int getNcols();
	void setNcols(int ncols);
	std::vector<std::vector<double>> getValues();
	void setValues(std::vector<std::vector<double>> values);
	void setValueAt(int row, int col, double value);
	double getValueAt(int row, int col);
	bool isSquare();
	int size();
	matrix multiplyByConstant(double constant);
	matrix insertColumnWithValue1();
	std::string toString();
};

class matrixMath
{

private:
	static int changeSign(int i);

public:
	matrixMath();
	~matrixMath();

	matrix transpose(matrix _matrix);
	matrix inverse(matrix matrix);
	double determinant(matrix matrix);
	matrix createSubmatrix(matrix _matrix, int excluding_row, int excluding_col);
	matrix cofactor(matrix _matrix);
	matrix add(matrix matrix1, matrix matrix2);
	matrix subtract(matrix matrix1, matrix matrix2);
	matrix multiply(matrix matrix1, matrix matrix2);
};