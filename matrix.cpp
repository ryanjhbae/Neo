
// Matrix Template Class: Implementation

// UNCHECKED ELEMENT ACCESSORS

template <class T> vector<T>& Matrix<T>::operator[](int i) {
	return theMatrix[i];
}

template <class T> const vector<T>& Matrix<T>::operator[](int i) const {
	return theMatrix[i];
}

// CHECKED ELEMENT ACCESSORS

template <class T> T& Matrix<T>::at(int row, int col) {
	return theMatrix.at(row).at(col);
}

template <class T> const T& Matrix<T>::at(int row, int col) const {
	return theMatrix.at(row).at(col);
}

// MATRIX ALGEBRA

template <class T> Matrix<T> Matrix<T>::operator+(const Matrix <T>& rhs) {
	// throw error if they're not the same size
	Matrix<T> sum;
	sum.resize(width, height);
	for (int row = 0; row < height; ++row) {
		for (int col = 0; col < width; ++col) {
			sum[row][col] = theMatrix[row][col] + rhs[row][col];
		}
	}
	return sum;
}

template <class T> Matrix<T>& Matrix<T>::operator+=(const Matrix <T>& rhs) {

	for (int row = 0; row < height; ++row) {
		for (int col = 0; col < width; ++col) {
			theMatrix[row][col] += rhs[row][col];
		}
	}
	// The solution below works fine, it's just less optimal in terms of 
	// performance since we have to copy the object
	// *this = *this + rhs;
	return *this;
}

template <class T> Matrix<T> Matrix<T>::operator-(const Matrix <T>& rhs) {
	// throw error if they're not the same size
	Matrix<T> diff;
	diff.resize(width, height);
	for (int row = 0; row < height; ++row) {
		for (int col = 0; col < width; ++col) {
			diff[row][col] = theMatrix[row][col] - rhs[row][col];
		}
	}
	return diff;
}

template <class T> Matrix<T>& Matrix<T>::operator-=(const Matrix <T>& rhs) {
	for (int row = 0; row < height; ++row) {
		for (int col = 0; col < width; ++col) {
			theMatrix[row][col] -= rhs[row][col];
		}
	}
	return *this;
}

// MATRIX MULTIPLICATION

template <class T> Matrix<T> Matrix<T>::operator*(const Matrix <T>& rhs) {

	int m = height;
	int n = width;
	int p = rhs.getWidth();
	
	if (n != rhs.getHeight()) { // throw error if multiplication isn't defined
		
	}

	Matrix<T> prod;

	// multiplying a Matrix with m rows and n columns
	// by a Matrix with n rows and p columns produces
	// a Matrix with m rows and p columns
	
	prod.resize(p, m);

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < p; ++j) {
			prod[i][j] = theMatrix[i][0] * rhs[0][j];
			for (int k = 1; k < n; ++k) {
				prod[i][j] += theMatrix[i][k] * rhs[k][j];
			}
		}
	}

	return prod;
}

template <class T> Matrix<T>& Matrix<T>::operator*=(const Matrix <T>& rhs) {
	// throw error if multiplication isn't defined

}

// VECTOR MULTIPLICATION

template <class T> vector<T> Matrix<T>::operator*(const vector<T>& vec) {
	// throw error if multiplication isn't defined
	vector<T> product;
	product.resize(height);
	for (int rowNum = 0; rowNum < height; ++rowNum) {
		product[rowNum] = theMatrix[rowNum][0] * vec[0]; // initial value
		for (int colNum = 1; colNum < width; ++colNum) {
			product[rowNum] += theMatrix[rowNum][colNum] * vec[colNum];
		}
	}
	return product;
}

template <class T> vector<T>& Matrix<T>::operator*=(const vector<T>& vec) {

}

template <class T> void Matrix<T>::fill(T val) {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			theMatrix[i][j] = val;
		}
	}
}

template <class T> bool Matrix<T>::operator==(const Matrix<T>& rhs) const {
	if (width != rhs.width) return false;
	if (height != rhs.height) return false;

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (theMatrix[i][j] != rhs[i][j]) {
				return false;
			}
		}
	}
	return true;
}

template <class T> bool Matrix<T>::operator!=(const Matrix<T>& rhs) const {
	return !(*this == rhs);
}

// MANIPULATE SIZE

template <class T> int Matrix<T>::getWidth() const {
	return width;
}
template <class T> int Matrix<T>::getHeight() const {
	return height;
}

template <class T> void Matrix<T>::setWidth(int w) {
	for (int i = 0; i < height; ++i) {
		vector<T>& row = theMatrix[i];
		row.resize(w);
	}
	width = w;
}

template <class T> void Matrix<T>::setHeight(int h) {
	theMatrix.resize(h);
	// an easy refactor would be to only resize the rows
	// that need to be resized
	
	// This loop is essential since resizing the outer vector does not 
	// resize the inner vectors.
	
	for (int i = 0; i < h; ++i) {
		vector<T>& row = theMatrix[i];
		row.resize(width);
	}
	
	height = h;
}

template <class T> void Matrix<T>::resize(int w, int h) {
	setHeight(h);
	setWidth(w);
}

template <class T> Matrix<T> Matrix<T>::getTranspose() {
	Matrix<T> Tr;
	Tr.resize(height, width);
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			Tr[j][i] = theMatrix[i][j];
		}
	}
	return Tr;
}