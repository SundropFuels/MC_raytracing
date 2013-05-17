#include "ray.h"
#include <iostream>
#include <cstdlib>

using namespace std;

//constructors
Ray::Ray()
{
	cvector<double> origin(3);
	origin.push_back(0);
	origin.push_back(0);
	origin.push_back(0);

	cvector<double> direction(2);
	direction.push_back(0);
	direction.push_back(0);
}

Ray::Ray(const cvector<double> & ray_origin, const cvector<double> & ray_direction)
{
	origin = ray_origin;
	direction = ray_direction;
}

Ray::Ray(const Ray & original)
{
	origin = original.get_origin();
	direction = original.get_direction();
}

Ray::~Ray()
{
	//does nothing
}

//accessors

cvector<double> Ray::get_origin() const
{
	return origin;
}

cvector<double> Ray::get_direction() const
{
	return direction;
}

//mutators
void Ray::set_origin(const cvector<double> & ray_origin)
{
	origin = ray_origin;
}

void Ray::set_direction(const cvector<double> & ray_direction)
{
	direction = ray_direction;
}

//length detecting member functions
double Ray::calc_length_to_cylinder_wall(const double & tube_radius)
{
	if(origin[0] > tube_radius)
	{
		return -1;				//right now, this just is an erroneous number...will return an error later
	}	


	return (-origin[0]*cos(direction[1]) + sqrt(tube_radius*tube_radius - origin[0]*origin[0]*sin(direction[1])*sin(direction[1])))/sin(direction[0]);
	
}

cvector<double> Ray::calc_cyl_intercept_position(const double & ray_length)
{
	double z_intercept = origin[2] + ray_length*cos(direction[0]);
	double l_prime = ray_length * sin(direction[0]);
	double r_intercept = sqrt(origin[0]*origin[0] + l_prime*l_prime + 2*origin[0]*l_prime*cos(direction[1]));
	double phi_intercept = 0;
	if(direction[1] <= 3.14159/2 || direction[1] >= 3*3.14159/2)
	{
		phi_intercept = origin[1] + asin(l_prime/r_intercept*sin(direction[1]));
	}
	else
	{
		phi_intercept = 3.14159 + origin[1] - asin(l_prime/r_intercept*sin(direction[1]));
	}

	if(phi_intercept >= 2*3.14159)		
	{
		phi_intercept -= 2*3.14159;
	}

	if(phi_intercept < 0)			
	{
		phi_intercept += 2*3.14159;
	}

	//Now need to build the vector to return
	
	cvector<double> intercept_position(3);
	intercept_position.push_back(r_intercept);
	intercept_position.push_back(phi_intercept);
	intercept_position.push_back(z_intercept);

	return intercept_position;
}
