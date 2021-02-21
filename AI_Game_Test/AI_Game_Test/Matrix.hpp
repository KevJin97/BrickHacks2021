#include <vector>
//TODO: eigval, eigvec, det diag, (row reduce?)

class Matrix
{
protected:
	std::vector<std::vector<double>> matrix;
	std::size_t dimensions[2];	//(x, y) or (Y x X)

public:
	//CONSTRUCTORS
	Matrix();
	Matrix(std::vector<std::vector<double>>& matrix);
	Matrix(std::size_t x, std::size_t y);
	Matrix(std::size_t* dimensions);
	~Matrix();

	Matrix eigval(Matrix& matrix);	//find eigenvalues
	Matrix eigvec(Matrix& matrix);	//find eigenvectors
	double det(Matrix& matrix);	//determinant of matrix
	double trace(Matrix& matrix);	//trace of matrix
	Matrix T();	//transpose
	Matrix inverse();	//matrix inverse
	Matrix kron(Matrix& matrix1, Matrix& matrix2);	//Kronecker product
	Matrix hadamard(Matrix& matrix);	//Hadamard product
	std::vector<double> vectorize();	//vectorize the matrix
	Matrix diag(Matrix& matrix);	//diagonalize matrix
	Matrix dot(std::vector<std::vector<double>>& matrix1, std::vector<std::vector<double>>& matrix2);

	//STATIC FUNCTIONS
	static Matrix dot(Matrix mat1, Matrix mat2);
	static Matrix transpose(Matrix& matrix);

	//OPERATOR OVERLOADS
	Matrix operator *(std::vector<double>& vec);	//dot product
	Matrix operator *(Matrix& matrix);	//dot product
	Matrix operator *(double scale);	//scalar
	void operator *=(Matrix& matrix);	//dot-equals overload
	std::vector<double> operator [](std::size_t n);	//array index
};

Matrix::Matrix()
{
	this->dimensions[0] = 0;
	this->dimensions[1] = 0;
}

Matrix::Matrix(std::vector<std::vector<double>>& matrix)
{
	this->dimensions[0] = matrix.size();
	this->dimensions[1] = matrix[0].size();
}

Matrix::Matrix(std::size_t x, std::size_t y)
{
	this->dimensions[0] = x;
	this->dimensions[1] = y;
	this->matrix.resize(x);
	for (std::size_t n = 0; n < x; ++n)
	{
		matrix[n].resize(y);
	}
}

Matrix::Matrix(std::size_t* dimensions)
{
	this->dimensions[0] = dimensions[0];
	this->dimensions[1] = dimensions[1];
	this->matrix.resize(dimensions[0]);
	for (std::size_t n = 0; n < dimensions[0]; ++n)
	{
		matrix[n].resize(dimensions[1]);
	}
}

Matrix::~Matrix()
{

}

Matrix Matrix::eigval(Matrix& matrix)
{

}

Matrix Matrix::eigvec(Matrix& matrix)
{

}

double Matrix::det(Matrix& matrix)
{

}

double Matrix::trace(Matrix& matrix)
{
	double trace = 0;
	if ((this->dimensions[0] == this->dimensions[1]) && (this->dimensions != 0))	//check if square
	{
		for (std::size_t n = 0; n < this->dimensions[0]; ++n)
		{
			trace += this->matrix[n][n];
		}
	}
	else
	{
		//throw an error
	}
	return trace;
}

Matrix Matrix::T()
{
	Matrix matrix(this->dimensions[1], this->dimensions[0]);
	for (std::size_t x = 0; x < this->dimensions[0]; ++x)
	{
		for (std::size_t y = 0; y < this->dimensions[1]; ++y)
		{
			matrix[y][x] = this->matrix[x][y];
		}
	}
	return matrix;
}

Matrix Matrix::inverse()
{

}

Matrix Matrix::kron(Matrix& matrix)
{
	
}

Matrix Matrix::hadamard(Matrix& matrix)
{
	Matrix hadamard(matrix.dimensions);
	if ((this->dimensions[0] == matrix.dimensions[0]) && (this->dimensions[1] == this->dimensions[1]))
	{
		for (std::size_t x = 0; x < this->dimensions[0]; ++x)
		{
			for (std::size_t y = 0; y < this->dimensions[1]; ++y)
			{
				hadamard[x][y] = this->matrix[x][y] * matrix.matrix[x][y];
			}
		}
	}
	else
	{
		//throw an error
	}
	return hadamard;
}

std::vector<double> Matrix::vectorize()
{
	std::vector<double> vectorized;
	vectorized.resize(this->dimensions[0] * this->dimensions[1]);

	for (std::size_t x = 0, n = 0; x < this->dimensions[0]; ++x, ++n)
	{
		for (std::size_t y = 0; y < this->dimensions[1]; ++y)
		{
			vectorized[n] = this->matrix[x][y];
		}
	}
	return vectorized;
}

Matrix Matrix::diag(Matrix& matrix)
{

}

Matrix Matrix::dot(std::vector<std::vector<double>>& matrix1, std::vector<std::vector<double>>& matrix2)
{
	std::size_t dimensions1[2] = { matrix1.size(), matrix1[0].size() };
	std::size_t dimensions2[2] = { matrix2.size(), matrix2[0].size() };

	Matrix dot(dimensions2[0], dimensions1[1]);

	if (dimensions1[1] == dimensions2[0])
	{
		for (std::size_t y1 = 0; y1 < dimensions1[1]; ++y1)	//x1 == y2
		{
			for (std::size_t x2 = 0; x2 < dimensions2[0]; ++x2)
			{
				double sum = 0;

				for (std::size_t x1 = 0; x1 < dimensions1[0]; ++x1)	//dot product of column1 with row2
				{
					sum = matrix1[x1][y1] * matrix2[x2][x1];
				}

				dot[x2][y1] = sum;
			}
		}
	}
	else
	{
		//throw errors
	}
	return dot;
}

Matrix Matrix::transpose(Matrix& matrix)
{
	return matrix.T();
}

//TODO: This can be improved
Matrix Matrix::dot(Matrix matrix1, Matrix matrix2)	// (x1, y1) & (x2, y2) == (x2, y1)
{
	Matrix dot(matrix2.dimensions[0], matrix1.dimensions[1]);

	if (matrix1.dimensions[1] == matrix2.dimensions[0])
	{
		for (std::size_t y1 = 0; y1 < matrix1.dimensions[1]; ++y1)	//x1 == y2
		{
			for (std::size_t x2 = 0; x2 < matrix2.dimensions[0]; ++x2)
			{
				double sum = 0;

				for (std::size_t x1 = 0; x1 < matrix1.dimensions[0]; ++x1)	//dot product of column1 with row2
				{
					sum = matrix1[x1][y1] * matrix2[x2][x1];
				}
				
				dot[x2][y1] = sum;
			}
		}
	}
	else
	{
		//throw errors
	}
	return dot;
}

Matrix Matrix::operator *(std::vector<double>& vec)
{
	Matrix dot(1, vec.size());

	if (vec.size() == this->dimensions[0])
	{
		for (std::size_t y = 0; y < this->dimensions[0]; ++y)
		{
			for (std::size_t x = 0; x < this->dimensions[0]; ++x)
			{
				dot[0][y] = this->matrix[x][y] * vec[x];
			}
		}
	}
	else
	{
		//throw error
	}
	return dot;
}

Matrix Matrix::operator *(Matrix& matrix)
{
	return this->dot(this->matrix, matrix.matrix);
}

Matrix Matrix::operator *(double scalar)
{
	Matrix mat(this->dimensions);

	for (std::size_t x = 0; x < this->dimensions[0]; ++x)
	{
		for (std::size_t y = 0; y < this->dimensions[1]; ++y)
		{
			mat[x][y] = this->matrix[x][y] * scalar;
		}
	}
	return mat;
}

void Matrix::operator *=(Matrix& matrix)
{
	*this = *this * matrix;
}

std::vector<double> Matrix::operator [](std::size_t n)
{
	return this->matrix[n];
}


class Row
{
private:
	std::vector<double> row;

public:
	Row() {}
	Row(std::vector<double>& row);
	~Row() {}
	friend Col;

	double vdot(Col col)
	{
		double dot = 0;
		if (this->row.size() == col.size())
		{
			for (std::size_t n = 0; n < this->row.size(); ++n)
			{
				dot += row[n] * col[n];
			}
		}
		else
		{
			//throw errors
		}
		return dot;
	}
	std::size_t size() { return this->row.size(); }

	void operator =(std::vector<double>& row) { this->row = row; }
	double operator *(Col col) { return vdot(col.col); }
	double operator [](std::size_t n) { return this->row[n]; }
};

class Col
{
private:
	std::vector<double> col;

public:
	Col() {}
	Col(std::vector<double>& col);
	~Col() {}
	friend Row;

	double vdot(Row& row)
	{
		double dot = 0;
		if (this->col.size() == row.size())
		{
			for (std::size_t n = 0; n < this->col.size(); ++n)
			{
				dot += row[n] * col[n];
			}
		}
		else
		{
			//throw errors
		}
		return dot;
	}
	std::size_t size() { return this->col.size(); }

	void operator =(std::vector<double>& col) { this->col = col;  }
	double operator *(Row row) { return vdot(row); }
	double operator [](std::size_t n) { return this->col[n]; }
};