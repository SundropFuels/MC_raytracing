#include <iostream>
#include <cstdlib>
using namespace std;

#include "./cell.h"

Cell::Cell()
	:rand_gen(time(0))
{
	//default constructor
	//creates a non-attenuating cell at room temperature
	temperature = 298;
	abs_coeff = 0;
	scatt_coeff = 0;
	//rand_gen.RandomInit(time(0));
}

Cell::Cell(double temp, double a, double sigma)
	:rand_gen(time(0))
{
	//main constructor
	temperature = temp;
	abs_coeff = a;
	scatt_coeff = sigma;
	rand_gen.RandomInit(time(0));
}

Cell::~Cell()
{
	//destructor does nothing special yet -- nothing on the free store
}

double Cell::get_temperature() const
{
	return temperature;
}

double Cell::get_abs_coeff() const
{
	return abs_coeff;
}

double Cell::get_scatt_coeff() const
{
	return scatt_coeff;
}

int Cell::get_cell_number() const
{
	return cell_number;
}

void Cell::set_temperature(const double & temp)
{
	temperature = temp;
}

void Cell::set_abs_coeff(const double & a)
{
	abs_coeff = a;
}

void Cell::set_scatt_coeff(const double & sigma)
{
	scatt_coeff = sigma;
}

void Cell::set_cell_number(const int & cell_num)
{
	cell_number = cell_num;
}

double Cell::generate_random_number()
{
	return rand_gen.Random();
}

void Cell::set_volumetric_source(const double & source)
{
	volumetric_source = source;
}


