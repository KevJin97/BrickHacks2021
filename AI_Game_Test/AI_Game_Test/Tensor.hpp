#pragma once
#include "Matrix.hpp"

class Tensor
{
private:
	std::vector<Matrix> tensor;

public:
	Tensor();
	~Tensor();
};
