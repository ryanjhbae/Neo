#include "matrix.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

int main() {
	Matrix<int> myMatrix;
	vector<int> myVector;
	cout << "myMatrix width: " << myMatrix.getWidth() << endl;
	cout << "myMatrix height " << myMatrix.getHeight() << endl;
	cout << "myVector size: " << myVector.size() << endl;

	cout << "NEW TESTING STUFF " << endl;
	myVector.resize(10);
	for (int i = 0; i < myVector.size(); ++i) {
		cout << myVector[i] << endl;
	}

	myMatrix.resize(10, 10);
	myMatrix.fill(2);
	cout << myMatrix << endl;
}