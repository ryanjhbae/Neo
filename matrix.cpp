
// Check for valid operations

template <class T> bool Matrix<T>::sameSizeAs(const Matrix& other) {
	return (height == other.getHeight()) &&
		(width == other.getWidth());
}

template <class T> void Matrix<T>::checkSameSize(const Matrix& other) {
	if (!sameSizeAs(other)) {
		throw invalid_argument(
			"Entrywise operation undefined: matrices are of different sizes."
		);
	}
}

template <class T> void Matrix<T>::checkValidMult(const Matrix& other) {
	if (width != other.getHeight()) {
		throw invalid_argument(
			"Undefined Matrix multiplication: the number of columns in the left Matrix does not match the number of rows in the right Matrix."
		);
	}
}

template <class T> void Matrix<T>::checkValidMult(const vector<T>& vec) {
	if (width != vec.size()) {
		throw invalid_argument(
			"Undefined vector multiplication. The width of the Matrix does not match the height of the vector."
		);
	}
}

// ****************************************************************************

// Apply func to each entry

template <class T> void Matrix<T>::mapEntries(function<void(T&, int, int)> func) {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			func(theMatrix[i][j], i, j);
		}
	}
}

template <class T> void Matrix<T>::mapEntries(function<void(T&)> func) {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			func(theMatrix[i][j]);
		}
	}
}

// ****************************************************************************

// OVERLOADED CONSTRUCTORS

template <class T> Matrix<T>::Matrix(int width, int height) 
	: width{ width }, height{ height } {
	theMatrix.resize(height);
	for (int i = 0; i < height; ++i) {
		theMatrix[i].resize(width);
	}
}

template <class T> Matrix<T>::Matrix(vector<vector<T>> m) : theMatrix{ m } {
	for (int i = 1; i < m.size(); ++i) {
		if (m[i].size() != m[i - 1].size()) {
			throw invalid_argument(
				"Incomplete Matrix. Check that all rows are the same size."
			);
		}
	}
	height = m.size();
	width = 0;
	if (height > 0) {
		width = m[0].size();
	}
}

template <class T> Matrix<T>::Matrix(initializer_list<initializer_list<T>> init_list) {
	int prevSize = init_list.begin()->size();
	int curSize;
	// Refactor to do all this in one loop
	for (int i = 1; i < init_list.size(); ++i) {
		curSize = (init_list.begin() + i)->size();
		if (curSize != prevSize) {
			throw invalid_argument(
				"Incomplete Matrix initialization. Check that all rows are the same size."
			);
		}
		prevSize = curSize;
	}
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

// ****************************************************************************

// UNCHECKED ELEMENT ACCESSORS

template <class T> vector<T>& Matrix<T>::operator[](int i) {
	return theMatrix[i];
}

template <class T> const vector<T>& Matrix<T>::operator[](int i) const {
	return theMatrix[i];
}

// CHECKED ELEMENT ACCESSORS

template <class T> vector<T>& Matrix<T>::at(int row) {
	return theMatrix.at(row);
}

template <class T> const vector<T>& Matrix<T>::at(int row) const {
	return theMatrix.at(row);
}

// ****************************************************************************

// MATRIX ALGEBRA

template <class T> Matrix<T> Matrix<T>::operator+(const Matrix <T>& rhs) {
	checkSameSize(rhs);
	Matrix<T> sum;
	sum.resize(width, height);

	sum.mapEntries([ this, rhs ](T& entry, int row, int col) -> 
		void { entry = theMatrix[row][col] + rhs[row][col]; });
	
	return sum;
}

template <class T> Matrix<T>& Matrix<T>::operator+=(const Matrix <T>& rhs) {
	checkSameSize(rhs);
	this->mapEntries([rhs](T& entry, int row, int col) ->
		void { entry += rhs[row][col]; });
	return *this;
}

template <class T> Matrix<T> Matrix<T>::operator-(const Matrix <T>& rhs) {
	checkSameSize(rhs);
	Matrix<T> diff;
	diff.resize(width, height);
	diff.mapEntries([this, rhs](T& entry, int row, int col) ->
		void { entry = theMatrix[row][col] - rhs[row][col]; });
	return diff;
}

template <class T> Matrix<T>& Matrix<T>::operator-=(const Matrix <T>& rhs) {
	checkSameSize(rhs);
	this->mapEntries([rhs](T& entry, int row, int col) ->
		void { entry -= rhs[row][col]; });
	return *this;
}

// MATRIX MULTIPLICATION

template <class T> Matrix<T> Matrix<T>::operator*(const Matrix <T>& rhs) {
	checkValidMult(rhs);

	int m = height;
	int n = width;
	int p = rhs.getWidth();
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
	checkValidMult(rhs);
	Matrix<T> temp = *this * rhs; // inefficient but what we're going with for now
	*this = temp;
	return *this;
}

// VECTOR MULTIPLICATION

template <class T> vector<T> Matrix<T>::operator*(const vector<T>& vec) {
	checkValidMult(vec);
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
	checkValidMult(vec);
	Matrix<T> temp = *this * vec; // inefficient but what we're going with for now
	*this = temp;
	return *this;
}

// ****************************************************************************

// SCALAR MULTIPLICATION

template <class T> Matrix<T> Matrix<T>::operator*(const T& scalar) {
	Matrix<T> temp = *this;
	temp.mapEntryWise([scalar](T& entry) -> void { entry *= scalar; });
	return temp;
}
template <class T> Matrix<T>& Matrix<T>::operator*=(const T& scalar) {
	this->mapEntryWise([scalar](T& entry) -> void { entry *= scalar; });
	return *this;
}

// ****************************************************************************

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

// ****************************************************************************

template <class T> void Matrix<T>::fill(T val) {
	// For now this is fine since fill is the only method not using the row
	// and col params
	this->mapEntries([&val](T& entry) -> void { entry = val; });
}

// MANIPULATE SIZE

template <class T> int Matrix<T>::getWidth() const { return width; }
template <class T> int Matrix<T>::getHeight() const { return height; }

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

// ****************************************************************************

template <class T> Matrix<T> Matrix<T>::getTranspose() {
	Matrix<T> Tr;
	Tr.resize(height, width);

	Tr.mapEntries([this](T& entry, int row, int col) ->
		void { entry = theMatrix[col][row]; }); 
	// flip col and row since it's the transpose

	/*
	* for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			Tr[j][i] = theMatrix[i][j];
		}
	}
	*/
	
	return Tr;
}