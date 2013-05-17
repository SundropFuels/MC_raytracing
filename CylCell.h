
//#ifndef CYLINDER_OBJ
//#define CYLINDER_OBJ

#include "cell.h"
#include "cvector.cpp"
#include "ray.h"
#include "CylSurface.h"

class CylCell : public Cell
{
	
	//This is a cell that is a section of a cylinder; this is the only cell that makes sense to use cyl. coords for

	public:

	CylCell();
	CylCell(double & temp, double & a, double & sigma, cvector<double> & minima, cvector<double> & maxima);

	bool point_within(const cvector<double> & point) const;	//checks whether the indicated point is within this cell

	//Monte-Carlo calculators
	//I don't want to try to generalize surfaces right now, so I am just going to pass in a tube radius and a vector of cells
	//Later, I can write this for a generalized surface, where the ray calculates the length to that surface, but not today

	void calculate_viewfactors(int num_rays, const cvector<CylCell> & cells, const CylSurface & tube); //calculates the viewfactors for each of the cells and the overall tube surface
											 //later can break the tube surface up into different elements, but not today
	void set_indices(int r_ind, int phi_ind, int z_ind);
	void calc_volumetric_source(const cvector<CylCell> & cells, const CylSurface & tube);
	double volume() const;								//returns the volume of the cell	
	void set_minima(const cvector<double> & min);
	void set_maxima(const cvector<double> & max);
	double get_volumetric_source();
	cvector<double> centroid();	


	
	protected:

	//Geometric parameters

	Ray generate_ray();					//generates weighted ray within the system (constant properties for now)
	double generate_ray_length();				//generates the length of a ray created within this cell (constant properties for now)


	double z_min;
	double z_max;
	double r_min;
	double r_max;
	double phi_min;
	double phi_max;
	

	int r_index;						//these provide a handy access point to a meshed tube by indexing in each direction
	int phi_index;
	int z_index;


};




//#endif
