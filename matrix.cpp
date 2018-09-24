#include "matrix.h"


matrix::matrix(std::vector<std::vector<double>> dat)
{
	this->data = dat;
	this->nrows = dat.size();
	this->ncols = dat[0].size();
	//for (int i=0;i<nrows;i++)
	//{
	//	for (int j = 0; j < ncols; j++)
	//		std::cout << data[i][j] << "	";
	//	std::cout << std::endl;
	//}

	//std::cout << "constructor " << data.size() << " " << data[0].size() << std::endl;
}

matrix::matrix(int nrow, int ncol)
{
	this->nrows = nrow;
	this->ncols = ncol;
	this->data.resize(nrows);
	for (int i = 0; i < nrows; i++) this->data[i].resize(ncols);
	//std::cout << "matrix " << nrows << " " << ncols << " " << data.size() << " " << data[0].size() <<std::endl;
}

int matrix::getNrows()
{
	return nrows;
}

void matrix::setNrows(int nrows)
{
	this->nrows = nrows;
}

int matrix::getNcols()
{
	return ncols;
}

void matrix::setNcols(int ncols)
{
	this->ncols = ncols;
}

std::vector<std::vector<double>> matrix::getValues()
{
	return data;
}

void matrix::setValues(std::vector<std::vector<double>> values)
{
	this->data = values;
}

void matrix::setValueAt(int row, int col, double value)
{
	//std::cout << "setValueAt " << data.size() << " " << data[0].size() << std::endl;
	//std::cout << nrows << " " << ncols << std::endl;
	this->data[row][col] = value;
}

double matrix::getValueAt(int row, int col)
{
	return data[row][col];
}

bool matrix::isSquare()
{
	return nrows == ncols;
}

int matrix::size()
{
	if (isSquare())
		return nrows;
	return -1;
}

matrix matrix::multiplyByConstant(double constant)
{
	matrix mat(nrows, ncols);
	for (int i = 0; i < nrows; i++)
	{
		for (int j = 0; j < ncols; j++)
		{
			mat.setValueAt(i, j, data[i][j] * constant);
		}
	}
	return mat;
}

matrix matrix::insertColumnWithValue1()
{
	matrix X_(this->getNrows(), this->getNcols() + 1);
	for (int i = 0; i < X_.getNrows(); i++) 
	{
		for (int j = 0; j < X_.getNcols(); j++) 
		{
			if (j == 0)
				X_.setValueAt(i, j, 1.0);
			else
				X_.setValueAt(i, j, this->getValueAt(i, j - 1));
		}
	}
	return X_;
}

std::string matrix::toString()
{
	std::string builder;
	builder = "nrows=" + std::to_string(nrows) + ", ncols=" + std::to_string(ncols) + "\ndata=\n";
	/*for (int i = 0; i < nrows; i++)
	{
		builder+=std::to_string(data[i])+"\n";
	}*/
	return builder;
}

matrixMath::matrixMath()
{
}

matrixMath::~matrixMath()
{
}

int matrixMath::changeSign(int i)
{
	if (i % 2 == 0)
		return 1;
	return -1;
}

matrix matrixMath::transpose(matrix _matrix)
{
	//std::cout << "transpose "<<_matrix.getNrows() << "	" << _matrix.getNcols() << std::endl;
	matrix transposedmatrix(_matrix.getNcols(), _matrix.getNrows());
	//std::cout << transposedmatrix.getNrows() << " " << transposedmatrix.getNcols() << std::endl;
	for (int i = 0; i < _matrix.getNrows(); i++)
	{
		for (int j = 0; j < _matrix.getNcols(); j++)
			transposedmatrix.setValueAt(j, i, _matrix.getValueAt(i, j));
	}
	return transposedmatrix;
}

matrix matrixMath::inverse(matrix matrix)
{
	return (transpose(cofactor(matrix)).multiplyByConstant(1.0 / determinant(matrix)));
}

double matrixMath::determinant(matrix matrix)
{
	if (matrix.size() == 1) {
		return matrix.getValueAt(0, 0);
	}

	if (matrix.size() == 2) {
		return (matrix.getValueAt(0, 0) * matrix.getValueAt(1, 1)) - (matrix.getValueAt(0, 1) * matrix.getValueAt(1, 0));
	}
	double sum = 0.0;
	for (int i = 0; i < matrix.getNcols(); i++) {
		sum += changeSign(i) * matrix.getValueAt(0, i) * determinant(createSubmatrix(matrix, 0, i));
	}
	return sum;
}

matrix matrixMath::createSubmatrix(matrix _matrix, int excluding_row, int excluding_col)
{
	matrix mat(_matrix.getNrows() - 1, _matrix.getNcols() - 1);
	int r = -1;
	for (int i = 0; i < _matrix.getNrows(); i++)
	{
		if (i == excluding_row)
			continue;
		r++;
		int c = -1;
		for (int j = 0; j < _matrix.getNcols(); j++)
		{
			if (j == excluding_col)
				continue;
			mat.setValueAt(r, ++c, _matrix.getValueAt(i, j));
		}
	}
	return mat;
}

matrix matrixMath::cofactor(matrix _matrix)
{
	matrix mat(_matrix.getNrows(), _matrix.getNcols());
	for (int i = 0; i < _matrix.getNrows(); i++)
	{
		for (int j = 0; j < _matrix.getNcols(); j++)
			mat.setValueAt(i, j, changeSign(i) * changeSign(j) * determinant(createSubmatrix(_matrix, i, j)));
	}
	return mat;
}

matrix matrixMath::add(matrix matrix1, matrix matrix2)
{
	matrix summatrix(matrix1.getNrows(), matrix1.getNcols());
	for (int i = 0; i < matrix1.getNrows(); i++)
	{
		for (int j = 0; j < matrix1.getNcols(); j++)
			summatrix.setValueAt(i, j, matrix1.getValueAt(i, j) + matrix2.getValueAt(i, j));
	}
	return summatrix;
}

matrix matrixMath::subtract(matrix matrix1, matrix matrix2)
{
	return add(matrix1, matrix2.multiplyByConstant(-1));
}

matrix matrixMath::multiply(matrix matrix1, matrix matrix2)
{
	matrix multipliedmatrix(matrix1.getNrows(), matrix2.getNcols());

	for (int i = 0; i < multipliedmatrix.getNrows(); i++)
	{
		for (int j = 0; j < multipliedmatrix.getNcols(); j++)
		{
			double sum = 0.0;

			for (int k = 0; k < matrix1.getNcols(); k++)
				sum += matrix1.getValueAt(i, k) * matrix2.getValueAt(k, j);

			multipliedmatrix.setValueAt(i, j, sum);
		}
	}
	return multipliedmatrix;
}
