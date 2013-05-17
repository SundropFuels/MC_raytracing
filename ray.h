#ifndef RAY
#define RAY



#include "cvector.cpp"
#include <cmath>


class Ray
{
	//by default, this is a Cartesian ray
	//This system will be subclassed to get the cylindrical ray in need for tubes	

	public:

	//constructors
	Ray();
	Ray(const cvector<double> & ray_origin, const cvector<double> & ray_direction);
	Ray(const Ray & original);		//copy constructor
	~Ray();

	//accessors
	cvector<double> get_origin() const;
	cvector<double> get_direction() const;

	//mutators
	void set_origin(const cvector<double> &);
	void set_direction(const cvector<double> &);

	//length detecting member functions
	double calc_length_to_cylinder_wall(const double & tube_radius);		//calculates intercept length with a wall
	cvector<double> calc_cyl_intercept_position(const double & ray_length);			//given a ray length, calculates (cylindrical) coord termination position
	



	private:
	cvector<double> origin;		//origin of the ray (x,y,z)
	cvector<double> direction;	//(theta,phi) direction of the ray (theta = pi/2 along ray direction, phi = 0 along ray direction)

	


};

#endif
