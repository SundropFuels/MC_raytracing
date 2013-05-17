#ifndef CYLINDER_SURFACE
#define CYLINDER_SURFACE

#include "cvector.cpp"
#include "randomc.h"
#include "ray.h"


class CylSurface
{

	public:

	CylSurface();
	CylSurface(const double & radius, const double & length, const double & eps);

	double emissivity() const;
	double get_radius() const;
	double get_length() const;
	double get_temperature() const;

	void set_eps(const double &);
	void set_radius(const double &);
	void set_length(const double &);
	void set_temperature(const double &);


	double area() const;
	

	private:

	double eps;
	double radius;
	double length;

	double temperature;

	//cvector<double> cell_viewfactors;
	//double self_viewfactor;
	
	//Ray generate_ray();
	//double generate_ray_length(const double & abs_coeff, const double & scatt_coeff);				//really, a Ray should generate its own length, but will fix this later

	CRandomMother rand_gen;



};



#endif
