#pragma once
#include <vector>
#include <iostream>
#include <string>

template <class T>
class matrix
{
private:
	int nrows = 0;
	int ncols = 0;
	std::vector<std::vector<T>> data;

public:
	matrix(std::vector<std::vector<T>> dat);
	matrix(int nrow, int ncol);
	~matrix();

	int getNrows() const;
	void setNrows(int nrows);
	int getNcols() const;
	void setNcols(int ncols);
	std::vector<std::vector<T>> getValues();
	void setValues(std::vector<std::vector<T>> values);
	void setValueAt(int row, int col, T value);
	bool isSquare() const;
	int size() const;

	void transpose();
	void inverse();

	T operator()(int row, int col) const;
	template<class T> friend std::ostream& operator<<(std::ostream &os, const matrix<T> &a);
};
int changeSign(int i);
template<class T> matrix<T> operator*(const matrix<T> &a, const matrix<T> &b);
template<class T> matrix<T> operator*(const matrix<T> &a, T value);
template<class T> matrix<T> operator+(const matrix<T> &a, const matrix<T> &b);
template<class T> matrix<T> operator-(const matrix<T> &a, const matrix<T> &b);
template<class T> matrix<T> createSubmatrix(const matrix<T> &a, int excluding_row, int excluding_col);
template<class T> matrix<T> transpose(const matrix<T> &a);
template<class T> T determinant(const matrix<T> &a);
template<class T> matrix<T> cofactor(const matrix<T> &a);

template<class T>
matrix<T>::matrix(std::vector<std::vector<T>> dat)
{
	this->data = dat;
	this->nrows = dat.size();
	this->ncols = dat[0].size();
}

template<class T>
matrix<T>::matrix(int nrow, int ncol)
{
	this->nrows = nrow;
	this->ncols = ncol;
	this->data.resize(nrows);
	for (int i = 0; i < nrows; i++) this->data[i].resize(ncols);
}

template<class T>
matrix<T>::~matrix()
{

}

template<class T>
int matrix<T>::getNrows() const
{
	return this->nrows;
}

template<class T>
void matrix<T>::setNrows(int nrows)
{
	this->nrows = nrows;
}

template<class T>
int matrix<T>::getNcols() const
{
	return this->ncols;
}

template<class T>
void matrix<T>::setNcols(int ncols)
{
	this->ncols = ncols;
}

template<class T>
std::vector<std::vector<T>> matrix<T>::getValues()
{
	return this->data;
}

template<class T>
void matrix<T>::setValues(std::vector<std::vector<T>> values)
{
	this->data = values;
}

template<class T>
void matrix<T>::setValueAt(int row, int col, T value)
{
	this->data[row][col] = value;
}

template<class T>
bool matrix<T>::isSquare() const
{
	return this->nrows == this->ncols;
}

template<class T>
int matrix<T>::size() const
{
	if (isSquare())
		return this->nrows;
	return -1;
}

template<class T>
inline std::ostream & operator<<(std::ostream &os, const matrix<T> &a)
{
	for (int i = 0; i < a.getNrows(); i++) 
	{
		for (int j = 0; j < a.getNcols(); j++)
			os << " " << a(i,j);
		os << std::endl;
	}
	return os;
}


inline int changeSign(int i)
{
	if (i % 2 == 0)
		return 1;
	return -1;
}

template<class T>
void matrix<T>::transpose()
{
	matrix<T> transposedMatrix(this->getNcols(), this->getNrows());
	for (int i = 0; i < this->getNrows(); i++)
	{
		for (int j = 0; j < this->getNcols(); j++)
			transposedMatrix.setValueAt(j, i, this->operator()(i, j));
	}
	this->data.clear();
	this->data.resize(transposedMatrix.getNrows());
	this->setNrows(transposedMatrix.getNrows());
	this->setNcols(transposedMatrix.getNcols());
	for (unsigned int i = 0; i < this->data.size(); i++)
	{
		this->data[i].resize(transposedMatrix.getNcols());
		for (unsigned j = 0; j < this->data[i].size(); j++)
			data[i][j] = transposedMatrix(i, j);
	}
}

template<class T>
void matrix<T>::inverse()
{
	matrix<T> temp = cofactor(*this);
	temp.transpose();
	*this = temp * (1.0 / determinant(*this));
}

template<class T>
inline T matrix<T>::operator()(int row, int col) const
{
	return this->data[row][col];
}

template<class T>
inline matrix<T> operator*(const matrix<T>& a, const matrix<T>& b)
{
	matrix<T> multipliedmatrix(a.getNrows(), b.getNcols());
	for (int i = 0; i < multipliedmatrix.getNrows(); i++)
	{
		for (int j = 0; j < multipliedmatrix.getNcols(); j++)
		{
			double sum = 0.0;

			for (int k = 0; k < a.getNcols(); k++)
				sum += a(i, k) * b(k, j);

			multipliedmatrix.setValueAt(i, j, sum);
		}
	}
	return multipliedmatrix;
}

template<class T>
inline matrix<T> operator*(const matrix<T>& a, T value)
{
	matrix<T> multipliedMatrix(a.getNrows(), a.getNcols());
	for (int i = 0; i < multipliedMatrix.getNrows(); i++)
	{
		for (int j = 0; j < multipliedMatrix.getNcols(); j++)
			multipliedMatrix.setValueAt(i, j, a(i, j) * value);
	}
	return multipliedMatrix;
}

template<class T>
inline matrix<T> operator+(const matrix<T>& a, const matrix<T>& b)
{
	matrix sumMatrix(a.getNrows(), a.getNcols());
	for (int i = 0; i < sumMatrix.getNrows(); i++)
	{
		for (int j = 0; j < sumMatrix.getNcols(); j++)
			sumMatrix.setValueAt(i, j, a(i, j) + b(i, j));
	}
	return sumMatrix;
}

template<class T>
inline matrix<T> operator-(const matrix<T>& a, const matrix<T>& b)
{
	return (a + b*(-1));
}

template<class T>
inline matrix<T> createSubmatrix(const matrix<T>& a, int excluding_row, int excluding_col)
{
	matrix<T> mat(a.getNrows() - 1, a.getNcols() - 1);
	int r = -1;
	for (int i = 0; i < a.getNrows(); i++)
	{
		if (i == excluding_row)
			continue;
		r++;
		int c = -1;
		for (int j = 0; j < a.getNcols(); j++)
		{
			if (j == excluding_col)
				continue;
			mat.setValueAt(r, ++c, a(i, j));
		}
	}
	return mat;
}

template<class T>
inline matrix<T> transpose(const matrix<T>& a)
{
	matrix<T> tempMatrix(a);
	tempMatrix.transpose();
	return tempMatrix;
}

template<class T>
inline T determinant(const matrix<T>& a)
{
	if (a.size() == 1)
		return a(0, 0);
	if (a.size() == 2)
		return (a(0, 0) * a(1, 1)) - (a(0, 1) * a(1, 0));
	double sum = 0.0;
	for (int i = 0; i < a.getNcols(); i++)
		sum += changeSign(i) * a(0, i) * determinant(createSubmatrix(a, 0, i));
	return sum;
}

template<class T>
inline matrix<T> cofactor(const matrix<T>& a)
{
	matrix<T> mat(a.getNrows(), a.getNcols());
	for (int i = 0; i < a.getNrows(); i++)
	{
		for (int j = 0; j < a.getNcols(); j++)
			mat.setValueAt(i, j, changeSign(i)*changeSign(j)*determinant(createSubmatrix(a, i, j)));
	}
	return mat;
}
