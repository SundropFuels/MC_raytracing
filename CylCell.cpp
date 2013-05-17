#include "CylCell.h"
#include "CylSurface.h"

CylCell::CylCell()
{
	temperature = 0.0;
	abs_coeff = 0.0;
	scatt_coeff = 0.0;
}

CylCell::CylCell(double & temp, double & a, double & sigma, cvector<double> & minima, cvector<double> & maxima)
	: Cell(temp, a, sigma)
{
	r_min = minima[0];
	r_max = maxima[0];

	phi_min = minima[1];
	phi_max = maxima[1];

	z_min = minima[2];
	z_max = maxima[2];
}

bool CylCell::point_within(const cvector<double> & point) const
{
	bool flag = 0;
	if(r_min <= point[0] && r_max > point[0])
	{
		if(phi_min <= point[1] && phi_max > point[1])
		{
			if(z_min <= point[2] && z_max > point[2])
			{
				flag = 1;
			}
		}
	}

	return flag;
}

Ray CylCell::generate_ray()
{
	double r = rand_gen.Random() * (r_max - r_min) + r_min;
	double phi = rand_gen.Random() * (phi_max - phi_min) + phi_min;
	double z = rand_gen.Random() * (z_max - z_min) + z_min;

	cvector<double> origin(3);
	origin.push_back(r);
	origin.push_back(phi);
	origin.push_back(z);

	double theta_prime = acos(1-2*rand_gen.Random());
	double phi_prime = rand_gen.Random() * 2 * 3.14159;

	cvector<double> direction(2);
	direction.push_back(theta_prime);
	direction.push_back(phi_prime);

	return Ray(origin, direction);

}	

double CylCell::generate_ray_length()
{

	return -1/(abs_coeff+scatt_coeff) * log(rand_gen.Random());
} 

void CylCell::calculate_viewfactors(int num_rays, const cvector<CylCell> & cells, const CylSurface & tube)
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
			
			length = generate_ray_length();
			if(length >= current_ray.calc_length_to_cylinder_wall(tube.get_radius()))
			{
				//cout << "Ray hit wall" << endl;				
				length = current_ray.calc_length_to_cylinder_wall(tube.get_radius());
				intercept_position = current_ray.calc_cyl_intercept_position(length);
				
				if(intercept_position[2] >= tube.get_length() || intercept_position[2] < 0)
				{
					//we just throw this ray away -- it left the tube
					absorbed = 1;
					//cout << "Ray out of tube" << endl;
				}
				else
				{
					//is the ray absorbed?
					if(rand_gen.Random() <= tube.emissivity())
					{
						//add the ray to the tube bucket
						//cout << "Ray absorbed" << endl;
						cell_buckets[cells.size()]++;
						absorbed = 1;
						//cout << "Wall ray absorbed!" << endl;
						
					}
					else
					{

						//cout << "Ray scattered" << endl;						
						cvector<double> direction(2);
						direction.push_back(acos(1-2*rand_gen.Random()));		
						direction.push_back(rand_gen.Random() * 3.14159 + 3.14159/2);	//these need to run from pi/2 to 3pi/2
						current_ray = Ray(intercept_position, direction);
						
					}

				}
			}
			else
			{
				//This ray is attenuated -- need to see if it is in the tube
				found = 0;
				intercept_position = current_ray.calc_cyl_intercept_position(length);
				//cout << "Ray attenuated in volume" << endl;				
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
							//cout << "Ray absorbed by volume cell" << endl;
						}
						else
						{
							//Need a new ray direction --assuming isotropic scattering right now
							cvector<double> direction(2);
							direction.push_back(acos(1-2*rand_gen.Random()));
							direction.push_back(rand_gen.Random() * 2 * 3.14159);							

							current_ray = Ray(intercept_position, direction);
							//cout << "Ray scattered by volume cell" << endl;				
						}
						
						break;
					}
					
				}
				if(!found)
					{
						//cout << "Ray lost from end of tube" << endl;
						absorbed = 1;			//This ray is lost
					}


			}

		}

	}


	
	//now we've run this for N rays -- we just need to calculate the viewfactors
	cell_viewfactors.clear();	
	
	double sum_VF = 0;	
	for(int k = 0; k < cell_buckets.size() - 1; k++)
	{
		cell_viewfactors.push_back((double)cell_buckets[k]/(double)num_rays);
		//cout << "Viewfactor to cell #" << k << ":" << cell_viewfactors[k] << endl;
		sum_VF += cell_viewfactors[k];
		
	}

	surface_viewfactors.clear();
	surface_viewfactors.push_back((double)cell_buckets[cells.size()]/(double)num_rays);
	sum_VF += surface_viewfactors[0];
	cout << "Surface viewfactor: " << surface_viewfactors[0] << endl;
	cout << "Sum of viewfactors: " << sum_VF << endl;


} 


void CylCell::set_indices(int r_ind, int phi_ind, int z_ind)
{
	r_index = r_ind;
	phi_index = phi_ind;
	z_index = z_ind;

}

double CylCell::volume() const
{
	return (z_max-z_min)*(phi_max-phi_min)*(r_max*r_max - r_min*r_min)/2;

}

void CylCell::calc_volumetric_source(const cvector<CylCell> & cells, const CylSurface & tube)
{
	double sum;
	double T_cell;
	sum = -4*abs_coeff*5.6E-8*temperature*temperature*temperature*temperature*(this->volume());		//power OUT from this element
	

	//add in contributions from each of the other volume cells	
	for(int i = 0; i < cells.size(); i++)
	{
		T_cell = cells[i].get_temperature();
		sum+= 4 * 5.6E-8 * cells[i].get_abs_coeff()*T_cell*T_cell*T_cell*T_cell*cell_viewfactors[i]*cells[i].volume();
		
	}

	sum += 5.6E-8 * tube.get_temperature() * tube.get_temperature() * tube.get_temperature() * tube.get_temperature() * surface_viewfactors[0] * 4*abs_coeff * (this->volume());
	

	volumetric_source = sum/(this->volume());

}

void CylCell::set_minima(const cvector<double> & min)
{

	r_min = min[0];
	phi_min = min[1];
	z_min = min[2];
}

void CylCell::set_maxima(const cvector<double> & max)
{
	r_max = max[0];
	phi_max = max[1];
	z_max = max[2];
}

double CylCell::get_volumetric_source()
{
	return volumetric_source;
}

cvector<double> CylCell::centroid()
{
	cvector<double> centroid_vec(3,0);
	double rc, phic, zc;
	
	rc = 2/3*(r_max*r_max*r_max-r_min*r_min*r_min)/(r_max*r_max-r_min*r_min)*sqrt(2-2*cos(phi_max-phi_min))/(phi_max-phi_min);

	phic = (phi_min+phi_max)/2;
	if(phic > 2*3.14159)
	{
		phic = phic - 2*3.14159;
	}
	
	zc = (z_min+z_max)/2;

	centroid_vec[0] = rc;
	centroid_vec[1] = phic;
	centroid_vec[2] = zc;
	return centroid_vec;

}
