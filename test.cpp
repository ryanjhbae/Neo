#include "matrix.hpp"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

void plusOne(char& c) {
	++c;
}

int main() {
	Matrix<int> B = {
		{1, 2, 0, 1},
		{2, 2, 1, 3},
		{1, -1, 2, 4}
	};

	Matrix<int> A = {
		{1, -2, 3},
		{2, 3, -4}
	};

	Matrix<int> C = A * B;
	cout << C << endl;

	Matrix<int> CTr = C.getTranspose();
	cout << CTr << endl;

	C.fill(5);

	cout << C << endl;

	Matrix<int> singleton;
	singleton.resize(1, 1);
	singleton[0][0] = 0;
	cout << singleton << endl;

	Matrix<int> D = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12}
	};

	cout << B + D << endl;

	Matrix<char> charMatrix = {
		{'A', 'B', 'C'},
		{'D', 'E', 'F'}
	};

	cout << charMatrix << endl;
	charMatrix.mapEntries(plusOne);
	cout << charMatrix << endl;
}