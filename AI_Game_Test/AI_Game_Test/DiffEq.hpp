#pragma once
#include <vector>
//TODO: Write full DiffEq library with function pointers for weird diff eq's


struct data
{
	double variable;
	double function;
};

//index value of function will refer to order of derivative
//function vector contains constants of the equation
class DiffEq
{
private:
	std::vector<double> function;
	data* cond;
	std::size_t num_steps;
	double step_size;
	double start_point;

public:
	DiffEq();
	DiffEq(std::vector<double> function, data* cond, double start_point, double step_size, std::size_t num_steps);
	//DiffEq(std::vector<double> function, data* cond, double start_point, double end_point, std::size_t num_steps);
	~DiffEq();

	void add_conditions(std::vector<data> cond);
	void add_start_point(double start_point);
	void add_step_size(double step_size);
	void add_num_steps(double num_steps);
	std::vector<data> euler();
	std::vector<data> RK4();
};

DiffEq::DiffEq()
{
	this->cond = NULL;
	this->num_steps = 0;
	this->step_size = 0;
	this->start_point = 0;
}

DiffEq::DiffEq(std::vector<double> function, data* cond, double start_point, double step_size, std::size_t num_steps)
{
	this->function = function;
	this->num_steps = 0;
	this->step_size = 0;
	this->start_point = 0;
	this->cond = new data[function.size()];
	for (std::size_t n = 0; n < function.size(); ++n)
	{
		this->cond[n] = cond[n];
	}
}

//DiffEq::DiffEq(std::vector<double> function, data* cond, double start_point, double end_point, std::size_t num_steps)
//{
//	this->function = function;
//	this->start_point = start_point;
//	this->step_size = (end_point - start_point) / num_steps;
//	this->num_steps = num_steps;
//	this->cond = new data[function.size()];
//	for (std::size_t n = 0; n < function.size(); ++n)
//	{
//		this->cond[n] = cond[n];
//	}
//}

DiffEq::~DiffEq()
{
	delete[] this->cond;
}

void DiffEq::add_conditions(std::vector<data> cond)
{
	this->cond = new data[cond.size()];

	for (std::size_t i = 0; i < cond.size(); ++i)
	{
		this->cond[i] = cond[i];
	}
}

void DiffEq::add_start_point(double start_point)
{
	this->start_point = start_point;
}

void DiffEq::add_step_size(double step_size)
{
	this->step_size = step_size;
}

void DiffEq::add_num_steps(double num_steps)
{
	this->num_steps = num_steps;
}

std::vector<data> DiffEq::RK4()
{
	//bool* terms = new bool[this->function.size()]
	/*
	for (std::size_t i = 0; i < this->function.size(); ++i)
	{
		if (this->function[i] != 0)
		{
			terms[i] = true;
		}
	}
	*/

	double k1 = 0, k2 = 0, k3 = 0, k4 = 0;
}

std::vector<data> DiffEq::euler()
{
	std::vector<data> output(this->num_steps);
	output[0].variable = this->start_point;
	output[0].function = this->cond[0].function;
	double first_deriv;
	/*
	for (std::size_t n = 1; n < this->num_steps; ++n)
	{
		
	}
	*/
}