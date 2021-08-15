#ifndef __NEO_MATRIX_H__
#define __NEO_MATRIX_H__

#include <vector>
#include <iostream>
#include "neo-exceptions.h"

using std::cout;
using std::endl;
using std::ostream;
using std::vector;

template <class T> class Matrix {

private:
	int width;
	int height;
	// Vector of height rows of width length each
	vector<vector<T>> theMatrix;

public:

	// Matrix<T> Matrix(int width, int height);
	// How to make a template constructor?

	
	

	bool sameSize(const Matrix<T>& other);

	// Matrix algebra
	Matrix<T> operator+(const Matrix<T>& rhs);
	Matrix<T>& operator+=(const Matrix<T>& rhs);
	Matrix<T> operator-(const Matrix<T>& rhs);
	Matrix<T>& operator-=(const Matrix<T>& rhs);
	Matrix<T> operator*(const Matrix<T>& rhs);
	Matrix<T>& operator*=(const Matrix<T>& rhs);	

	// Vector multiplication
	Matrix<T> operator*(const vector<T>& vec);
	Matrix<T>& operator*=(const vector<T>& vec);

	// Unchecked accessor for the i - 1 th row
	vector<T>& operator[](int i);

	void fill(T);

	bool operator==(const Matrix<T>& rhs) const;
	bool operator!=(const Matrix<T>& rhs) const;

	int getWidth() const;
	int getHeight() const;
	void setWidth(int w);
	void setHeight(int h);
	void resize(int w, int h);

	// Add scalar multiplication here

	// Very basic functionality for now, mostly for testing

	// Inline as per the approach suggested at 
	// https://stackoverflow.com/questions/4660123/overloading-friend-operator-for-template-class
	friend ostream& operator<<(ostream& out, const Matrix<T>& m) {

		for (int col = 0; col < m.height; ++col) {
			bool atLeastOne = false;
			for (int row = 0; row < m.width; ++row) {
				if (atLeastOne) {
					out << ' ';
				}
				else {
					atLeastOne = true;
				}
				out << m.theMatrix[col][row];
			}
			out << endl;
		}
		return out;
	}
};

#include "matrix.cc"

#endif