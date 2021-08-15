
// Matrix Template Class: Implementation


#if 0
template <class T> Matrix<T>::Matrix(int width, int height) 
	: width{ width }, height{ height } {

	theMatrix.resize(height);
	for (int i = 0; i < height; ++i) {
		vector<T>& row = theMatrix[i];
		row.resize(width);

		for (int j = 0; j < width; ++j) {
			row[j] = 0;
		}

// want to initialize to the identity matrix but not sure 
// how to do that with templates
	}
}
#endif 

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

}

template <class T> Matrix<T> Matrix<T>::operator*(const Matrix <T>& rhs) {

}

template <class T> Matrix<T>& Matrix<T>::operator*=(const Matrix <T>& rhs) {

}

// VECTOR MULTIPLICATION

template <class T> Matrix<T> Matrix<T>::operator*(const vector<T>& vec) {

}

template <class T> Matrix<T>& Matrix<T>::operator*=(const vector<T>& vec) {

}

template <class T> vector<T>& Matrix<T>::operator[](int i) {
	return theMatrix[i];
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
