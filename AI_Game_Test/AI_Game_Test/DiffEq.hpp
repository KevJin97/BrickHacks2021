#pragma once
#include <vector>

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
	DiffEq(std::vector<double> function, double start_point, double step_size, std::size_t num_steps);
	DiffEq(std::vector<double> function, double start_point, double end_point, std::size_t num_steps);
	~DiffEq();

	void add_init_vals(std::vector<data> cond);
	void add_start_point(double start_point);
	void add_step_size(double step_size);
	void add_num_steps(double num_steps);
	std::vector<data> RK4();
};

DiffEq::DiffEq()
{
	this->cond = NULL;
	this->num_steps = 0;
	this->step_size = 0;
	this->start_point = 0;
}

DiffEq::DiffEq(std::vector<double> function, double start_point, double step_size, std::size_t num_steps)
{
	this->cond = NULL;
	this->num_steps = 0;
	this->step_size = 0;
	this->start_point = 0;
}

DiffEq(std::vector<double> function, double start_point, double end_point, std::size_t num_steps);
~DiffEq();

void add_init_vals(std::vector<data> cond);
void add_start_point(double start_point);
void add_step_size(double step_size);
void add_num_steps(double num_steps);
std::vector<data> RK4();