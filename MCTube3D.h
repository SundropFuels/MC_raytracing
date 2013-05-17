#include "cvector.cpp"
#include <iostream>
#include <cstdlib>
#include "CylCell.h"
#include "CylSurface.h"
#include <string>
#include "csv_reader.h"

using namespace std;


class MCTube3D
{

	public:
	MCTube3D();
	MCTube3D(string filename);
	~MCTube3D();

	void setup_from_csv(string filename);

	void createTube(const double & length, const double & radius, const double & emissivity, const double & temperature);
	void meshTube(const int num_radial_slices, const int num_phi_slices, const int num_z_slices);
	void setTemperatures(const cvector<double> & temperatures);
	void setAbsCoeffs(const cvector<double> & abs_coeffs);
	void setScattCoeffs(const cvector<double> & scatt_coeffs);	
	void calculate_viewfactors(const int num_rays);
	void calculate_source_terms();
	void write_source_output(string filename);


	void print_mesh();

	private:

	CylSurface tube;
	cvector<CylCell> cells;

};




