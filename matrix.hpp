#ifndef __NEO_MATRIX_H__
#define __NEO_MATRIX_H__

#include <vector>
#include <iostream>
#include <initializer_list>
#include "neo-exceptions.hpp"

using std::cout;
using std::endl;
using std::initializer_list;
using std::ostream;
using std::vector;


// Important Note: the current implementation counts
// rows and columns from 0. That is, if we had the Matrix below,

// 1 2 3 4 5
// 6 7 8 9 10
// 11 12 13 14 15
// 16 17 18 19 20
//

template <class T> class Matrix {

private:

	int width;
	int height;
	// Vector of height rows of width length each
	vector<vector<T>> theMatrix;

	// Generalize the + and - methods (probably more work than it's worth)
	// Matrix<T> mapEntryWise(const Matrix<T>& rhs, operator);

public:

	// Overloaded constructor

	Matrix<T>(int width = 0, int height = 0) : width{ width }, height{ height } {
		theMatrix.resize(height);
		for (int i = 0; i < height; ++i) {
			theMatrix[i].resize(width);
		}
	}

	Matrix<T>(vector<vector<T>> m) : theMatrix{ m } {
		// Throw an error if incomplete (size doesn't align)
		height = m.size();
		width = 0;
		if (height > 0) {
			width = m[0].size();
		}
	}

	// Allows initialization like { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} }

	Matrix<T>(initializer_list<initializer_list<T>> init_list) {
		// Throw an error if incomplete (size doesn't align)
		height = static_cast<int>(init_list.size());
		width = static_cast<int>((init_list.begin())->size());
		
		theMatrix.resize(height);
		for (int rowNum = 0; rowNum < height; ++rowNum) {
			vector<T>& row = theMatrix[rowNum];
			row.resize(width);
			for (int colNum = 0; colNum < width; ++colNum) {
				row[colNum] = ((init_list.begin() + rowNum)->begin())[colNum];
			}
		}
		
	}

	// Matrix<T> Matrix(int width, int height);
	// How to make a template constructor?

	// Unchecked accessors

	vector<T>& operator[](int i);
	const vector<T>& operator[](int i) const;

	// Checked accessors 

	T& at(int row, int col);
	const T& at(int row, int col) const;

	// Matrix Algebra

	// Ensure to add exceptions for when the operations are not
	// valid (matrix sizes don't align)
	Matrix<T> operator+(const Matrix<T>& rhs);
	Matrix<T>& operator+=(const Matrix<T>& rhs);
	Matrix<T> operator-(const Matrix<T>& rhs);
	Matrix<T>& operator-=(const Matrix<T>& rhs);
	Matrix<T> operator*(const Matrix<T>& rhs);
	Matrix<T>& operator*=(const Matrix<T>& rhs);	

	// Vector multiplication
	vector<T> operator*(const vector<T>& vec);
	vector<T>& operator*=(const vector<T>& vec);

	// Scalar multiplication (Matrix * scalar)
	Matrix<T> operator*(const T& scalar);
	Matrix<T>& operator*=(const T& scalar);
	
	// Scalar multiplication (scalar * Matrix)
	friend Matrix<T> operator*(const T& scalar, const Matrix<T>& rhs) {

	}
	friend Matrix<T>& operator*=(T& scalar, const Matrix<T>& rhs) {

	}

	// 

	void fill(T);

	bool operator==(const Matrix<T>& rhs) const;
	bool operator!=(const Matrix<T>& rhs) const;

	int getWidth() const;
	int getHeight() const;
	void setWidth(int w);
	void setHeight(int h);
	void resize(int w, int h);

	Matrix<T> getTranspose();

	// Output operator: very basic functionality for now, mostly for testing

	// Inline as per the approach suggested at 
	// https://stackoverflow.com/questions/4660123/overloading-friend-operator-for-template-class
	friend ostream& operator<<(ostream& out, const Matrix<T>& m) {

		for (int row = 0; row < m.height; ++row) {
			out << "{ ";
			for (int col = 0; col < m.width; ++col) {
				if (col > 0) {
					out << ",\t";
				}
				out << m.theMatrix[row][col];
			}
			out << " }" << endl;
		}
		return out;
	}
};

#include "matrix.cpp"

#endif