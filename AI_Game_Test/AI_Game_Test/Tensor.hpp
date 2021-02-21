#pragma once
#include "Matrix.hpp"
//TODO: add more matrix functions
//TODO: tensors of uneven sizes

class Tensor
{
private:
	std::vector<Matrix> tensor;	//holds tensor products
	//std::vector<Tensor> tensor_sum;	//holds linear combinations of tensors of different dimensions
	std::size_t dim[2];

public:
	Tensor();
	Tensor(Matrix& matrix);
	~Tensor() {};

	std::size_t rank();	//fix this later
	void kron(Matrix& matrix);
	Matrix kron_result();
	
	//STATIC FUNCTIONS
	static Tensor kron(Tensor& tensor1, Tensor& tensor2);
	static Matrix eye(std::size_t N);

	//OPERATOR OVERLOAD
	void operator =(Matrix& matrix);
	void operator =(std::vector<double>& vec);
	void operator =(Row& row);
	void operator =(Col& col);
	Matrix operator [](std::size_t n);
};

Tensor::Tensor()
{
	this->dim[0] = 0;
	this->dim[1] = 0;
}

Tensor::Tensor(Matrix& matrix)
{
	this->tensor.push_back(matrix);
}

std::size_t Tensor::rank()
{
	//std::size_t rank = 0;
	return this->tensor.size();
}

void Tensor::kron(Matrix& matrix)
{
	this->tensor.push_back(matrix);
	this->dim[0] *= matrix.dimensions[0];
	this->dim[1] *= matrix.dimensions[1];
}

Matrix Tensor::kron_result()
{
	Matrix result = this->tensor[tensor.size()];
	for (std::size_t n = 0, count = this->tensor.size() - 2; n < this->tensor.size() - 1; ++n, --count)
	{
		result = this->tensor[count].kron(this->tensor[count], result);
	}
	return result;
}

Tensor Tensor::kron(Tensor& tensor1, Tensor& tensor2)
{
	Tensor kron_tensor = tensor1;

	for (std::size_t n = 0; n < tensor2.tensor.size(); ++n)
	{
		kron_tensor.tensor.push_back(tensor2[n]);
	}

	tensor1.dim[0] *= tensor2.dim[0];
	tensor1.dim[1] *= tensor2.dim[1];

	return kron_tensor;
}

Matrix Tensor::eye(std::size_t N)
{
	Matrix identity(N, N);
	for (std::size_t n = 0; n < N; ++n)
	{
		identity[n][n] = 1;
	}

	return identity;
}

void Tensor::operator =(Matrix& matrix)
{
	this->tensor.clear();
	this->tensor.push_back(matrix);
}

void Tensor::operator =(std::vector<double>& vec)
{
	this->tensor.clear();
	std::vector<std::vector<double>> m = { vec };
	Matrix mat = m;
	this->tensor.push_back(m);
}

void Tensor::operator =(Row& row)
{
	this->tensor.clear();
	this->tensor.push_back((Matrix)row);
}

void Tensor::operator =(Col& col)
{
	this->tensor.clear();
	this->tensor.push_back((Matrix)col);
}

Matrix Tensor::operator [](std::size_t n)
{
	return this->tensor[n];
}