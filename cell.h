#ifndef CELL
#define CELL


#include "cvector.cpp"
#include "randomc.h"
#include <cstdlib>

class Cell
{
	//This is the unit discretization cell for the Monte Carlo model
	//This is currently a TOTAL model, so no wavelength effects

	public:

	//constructors
	Cell();
	Cell(double temp, double a, double s);	//add member function pointer later
	~Cell();

	//accessors
	double get_temperature() const;
	double get_abs_coeff() const;
	double get_scatt_coeff() const;
	int get_cell_number() const;
	double generate_random_number();
	

	//mutators
	void set_temperature(const double & temp);
	void set_abs_coeff(const double & abs_coeff);
	void set_scatt_coeff(const double & scatt_coeff);
	void set_cell_number(const int & cell_num);
	void set_volumetric_source(const double & source);
	
	protected:

	//****data members******//

	//radiation members
	double temperature;	//temperature, K
	double abs_coeff;	//absorption coefficient, m^-1
	double scatt_coeff;	//scattering coefficient, m^-1

	//geometry members

	int cell_number;	//this is a unique cell identifier, used for the general case
	//to generalize this, I'll need a vector of nodes and a vector of faces -- but that is beyond me right now

	cvector<double> cell_viewfactors;	//This is a list of viewfactors, will be indexed to cell_number
	cvector<double> surface_viewfactors;	//This is a list of surface viewfactors -- it will be indexed to surface_number
	double volumetric_source;	//This is the volumetric energy source term

	//random number generator
	CRandomMother rand_gen;

};

#endif
