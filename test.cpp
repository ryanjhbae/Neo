#include "matrix.hpp"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

int main() {
	Matrix<int> A = { 
		{1, -2, 3},
		{2, 3, -4} 
	};

	Matrix<int> B = { 
		{1, 2, 0, 1}, 	    
		{2, 2, 1, 3}, 
		{1, -1, 2, 4} 
	};

	Matrix<int> C = A * B;
	cout << C << endl; 

	Matrix<int> CTr = C.getTranspose();
	cout << CTr << endl;

	C.fill(5);

	cout << C << endl;

	
}
