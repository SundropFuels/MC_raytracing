#include "CylSurface.h"

CylSurface::CylSurface()
	:rand_gen(time(0))
{
	eps = 1;			//body is, by default, black
	radius = 1;
	length = 1;
}

CylSurface::CylSurface(const double & r, const double & l, const double & e)
	:rand_gen(time(0))
{

	eps = e;
	radius = r;
	length = l;
}

double CylSurface::emissivity() const
{
	return eps;
}

double CylSurface::get_radius() const
{
	return radius;
}

double CylSurface::get_length() const
{
	return length;
}

double CylSurface::get_temperature() const
{
	return temperature;
}

void CylSurface::set_eps(const double & e)
{
	eps = e;
}

void CylSurface::set_length(const double & l)
{
	length = l;
}

void CylSurface::set_radius(const double & r)
{
	radius = r;
}

void CylSurface::set_temperature(const double & T)
{
	temperature = T;
}

double CylSurface::area() const
{

	return radius*2*length*3.14159;
}

/*
Ray CylSurface::generate_ray()
{
	double r = radius;
	double phi = rand_gen.Random() * 2 * 3.14159;
	double z = rand_gen.Random() * length;

	cvector<double> origin(3);
	origin.push_back(r);
	origin.push_back(phi);
	origin.push_back(z);

	double theta_prime = acos(1-2*rand_gen.Random());
	double phi_prime = rand_gen.Random() * 3.14159 - 3.14159/2;

	cvector<double> direction(2);
	direction.push_back(theta_prime);
	direction.push_back(phi_prime);

	return Ray(origin, direction);

}

double CylSurface::generate_ray_length(const double & abs_coeff, const double & scatt_coeff)
{

	return -1/(abs_coeff+scatt_coeff) * log(rand_gen.Random());
} 

void CylSurface::calculate_viewfactors(int num_rays, const cvector<CylCell> & cells)
{
	//General procedure
	//I.  Generate a ray at random
	//II. Assign a length to the ray
	//III.Is ray length >= distance to the wall?
	//	a. Yes -- Is the ray contained in the system?
	//		i. Yes -- Is the ray absorbed or reflected?
	//			1.  Absorbed -- add this to the surface's bucket
	//			2.  Reflected -- generate a new ray, repeat process from the wall
	//		ii. No -- Move on to the next ray
	//	b. No -- Calculate position of extinction and find the cell it is extinguished in
	//		i. Scattered? - Generate new ray and repeat process from that cell
	//		ii.Absorbed? -- add this to the surfaces bucket
	//IV. Continue for N total rays
	//V. Determine fractional viewfactors Fi = (Ni/N)
	cvector<int> cell_buckets(cells.size()+1, 0);	
	double abs_coeff = cells[0].get_abs_coeff();
	double scatt_coeff = cells[0].get_scatt_coeff();	//right now this only works for uniform properties throughout volume
	int found = 0;
	int absorbed;
	Ray current_ray;
	double length;
	cvector<double> intercept_position;
	for(int n = 0; n < num_rays; n++)
	{
		absorbed = 0;
		current_ray = generate_ray();		
		while(absorbed == 0)
		{
			
			length = generate_ray_length(abs_coeff, scatt_coeff);
			if(length >= current_ray.calc_length_to_cylinder_wall(radius))
			{
				length = current_ray.calc_length_to_cylinder_wall(radius);
				intercept_position = current_ray.calc_cyl_intercept_position(length);
				if(intercept_position[2] >= length || intercept_position[2] < 0)
				{
					//we just throw this ray away -- it left the tube
					absorbed = 1;
				}
				else
				{
					//is the ray absorbed?
					if(rand_gen.Random() <= eps)
					{
						//add the ray to the tube bucket
						cell_buckets[cells.size()]++;
						absorbed = 1;
					}
					else
					{

						cvector<double> direction(2);
						direction[0] = acos(1-2*rand_gen.Random());
						direction[1] = rand_gen.Random() * 3.14159 - 3.14159/2;	//these need to run from -pi/2 to pi/2 for surface rays

						current_ray = Ray(intercept_position, direction);
					}

				}
			}
			else
			{
				//This ray is attenuated -- need to see if it is in the tube
				found = 0;
				for(int j = 0; j < cells.size(); j++)
				{
					if(cells[j].point_within(intercept_position))
					{
						found = 1;						
						//is this ray absorbed?
						if(rand_gen.Random() <= (cells[j].get_abs_coeff())/(cells[j].get_abs_coeff() + cells[j].get_scatt_coeff()))
						{
							cell_buckets[j]++;
							absorbed = 1;
						}
						else
						{
							//Need a new ray direction --assuming isotropic scattering right now
							cvector<double> direction(2);
							direction[0] = acos(1-2*rand_gen.Random());
							direction[1] = rand_gen.Random() * 2 * 3.14159;							

							current_ray = Ray(intercept_position, direction);				
						}
						
						break;
					}
					if(!found)
					{
						absorbed = 1;			//This ray is lost
					}
				}


			}

		}

	}

	//now we've run this for N rays -- we just need to calculate the viewfactors
	cell_viewfactors.clear();	
	for(int k = 0; k < cell_buckets.size() - 1; k++)
	{
		cell_viewfactors.push_back(cell_buckets[k]/num_rays);
		
	}

	self_viewfactor = cell_buckets[cells.size()]/num_rays;
	

}

*/	
