#ifndef __NEO_MATRIX_H__
#define __NEO_MATRIX_H__

#include <functional>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <vector>

using std::cout;
using std::endl;
using std::function;
using std::initializer_list;
using std::invalid_argument;
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

	bool sameSizeAs(const Matrix& other);
	void checkSameSize(const Matrix& other);
	void checkValidMult(const Matrix& other);
	void checkValidMult(const vector<T>& vec);	

public:

	// Overloaded constructor
	Matrix<T>(int width = 0, int height = 0);
	Matrix<T>(vector<vector<T>> m);
	Matrix<T>(initializer_list<initializer_list<T>> init_list);
	// Allows initialization like { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} }

	// Applies func to each entry
	void mapEntries(function<void(T&, int, int)> func);
	void mapEntries(function<void(T&)> func);

	// Unchecked accessors
	vector<T>& operator[](int i);
	const vector<T>& operator[](int i) const;

	// Checked accessors 
	vector<T>& at(int row);
	const vector<T>& at(int row) const;

	// Matrix Algebra

	// For Matrix operations and vector multiplication, an instance
	// of std::invalid_argument is thrown when the operations are not
	// defined
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