#include "matrix.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

int main() {
	Matrix<int> myMatrix;
	vector<int> myVector;
#if 0
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
	
#endif
	
	cout << "YET MORE TESTING STUFF " << endl;
	myMatrix.setWidth(5);
	cout << "myMatrix width: " << myMatrix.getWidth() << endl;
	cout << "myMatrix height " << myMatrix.getHeight() << endl;

	myMatrix.setHeight(6);
	myMatrix.fill(1);

	Matrix<int> myMatrix2;

	myMatrix2.resize(5, 6);
	myMatrix2.fill(2);
	cout << myMatrix + myMatrix2 << endl;
}