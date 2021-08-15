#include "matrix.hpp"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

Matrix<int> myMatrix;
vector<int> myVector;

#define VECTOR_TESTING 0
#define MATRIX_TESTING 0
#define MATRIX_TESTING_2 1
bool vector_testing = true;
bool matrix_testing = false;

#if VECTOR_TESTING
const vector<vector<int>> myVector2 = { {1, 2}, {3, 4} };
cout << myVector2[0][0] << endl;
cout << 5 + myVector2[0][0] << endl;

int j = myVector2[1][1];

#endif 
#if MATRIX_TESTING

cout << "YET MORE TESTING STUFF " << endl;
myMatrix.setWidth(5);
myMatrix.setHeight(6);
cout << "myMatrix width: " << myMatrix.getWidth() << endl;
cout << "myMatrix height " << myMatrix.getHeight() << endl;
myMatrix.fill(1);

Matrix<int> myMatrix2;

myMatrix2.resize(5, 6);
myMatrix2.fill(2);
cout << myMatrix + myMatrix2 << endl;
myMatrix += myMatrix2;
cout << myMatrix << endl;

myMatrix[2][2] = 5;
cout << myMatrix << endl;

Matrix<float> floatMatrix;
floatMatrix.resize(5, 5);
floatMatrix.fill(3.14);
cout << floatMatrix << endl;

#endif

#if MATRIX_TESTING_2
Matrix<int> m{ {1, -1, 2},
				{0, -3, 1} };
vector<int> x = { 2, 1, 0 };

cout << m << endl;
vector<int> y = m * x;
for (int i = 0; i < y.size(); ++i) {
	cout << y[i] << endl;
}
#endif