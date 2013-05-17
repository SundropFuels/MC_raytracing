#include "MCTube3D.h"

MCTube3D::MCTube3D()
{
	//default constructor does nothing
}

MCTube3D::MCTube3D(string filename)
{
	setup_from_csv(filename);
}

MCTube3D::~MCTube3D()
{
	//destructor does nothing right now
}

void MCTube3D::createTube(const double & length, const double & radius, const double & emissivity, const double & temperature)
{
	tube.set_length(length);
	tube.set_radius(radius);
	tube.set_eps(emissivity);
	tube.set_temperature(temperature);
}

void MCTube3D::meshTube(const int num_radial_slices, const int num_phi_slices, const int num_z_slices)
{

	cout << "In meshTube!" << endl;	
	CylCell cell;	
	double delta_r = tube.get_radius()/num_radial_slices;
	double delta_phi = 2*3.14159/num_phi_slices;
	double delta_z = tube.get_length()/num_z_slices;

	cvector<double> minimum(3);
	cvector<double> maximum(3);

	double T1 = 0;
	double A1 = 0;
	double S1 = 0;

	//create the cells for the tube
	cells.clear();
	for(int i = 0; i < num_z_slices; i++)
	{
		for(int j =0; j < num_radial_slices; j++)
		{
			for(int k = 0; k < num_phi_slices; k++)
			{
				minimum.clear();
				maximum.clear();
				//set min coords
				minimum.push_back(j*delta_r);
				minimum.push_back(k*delta_phi);
				minimum.push_back(i*delta_z);
				
				//set max coords
				maximum.push_back((j+1)*delta_r);
				maximum.push_back((k+1)*delta_phi);
				maximum.push_back((i+1)*delta_z);
				cell.set_minima(minimum);
				cell.set_maxima(maximum);	
				cells.push_back(cell);
				

			}
			

		}
		

	}

	//now the tube is meshed in cylindrical elements, which are stored in cvector<CylCell> cells

}

void MCTube3D::setTemperatures(const cvector<double> & temperatures)
{
	for(int i = 0; i < cells.size(); i++)
	{
		cells[i].set_temperature(temperatures[i]);
	}
	
}

void MCTube3D::setAbsCoeffs(const cvector<double> & abs_coeffs)
{
	for(int i = 0; i < cells.size(); i++)
	{
		cells[i].set_abs_coeff(abs_coeffs[i]);
	}
}

void MCTube3D::setScattCoeffs(const cvector<double> & scatt_coeffs)
{
	for(int j= 0; j<cells.size(); j++)
	{
		cells[j].set_scatt_coeff(scatt_coeffs[j]);
	}
}

void MCTube3D::calculate_viewfactors(const int num_rays)
{
	for(int i = 0; i < cells.size(); i++)
	{
		cout << "Calculating viewfactors for cell #" << i << endl;		
		cells[i].calculate_viewfactors(num_rays, cells, tube);
	}
	//Each of the cells should have its viewfactor set now

}


void MCTube3D::calculate_source_terms()
{
	for(int i = 0; i < cells.size(); i++)
	{
		
		cells[i].calc_volumetric_source(cells, tube);
		cout << "Cell #:" << i << "  Volumetric Source: " << cells[i].get_volumetric_source() << endl;
	}
}


void MCTube3D::print_mesh()
{
	cout << "Here!" << endl;
	for(int j =0; j < cells.size(); j++)
	{
		//cout << "What, what? " << endl;		
		cout << "Cell #" << j << " Temp: " << cells[j].get_temperature() << "   Volume: " << cells[j].volume() << endl;
	}
}

void MCTube3D::setup_from_csv(string filename)
{
	csv_reader Reader(filename);
	//The first few lines are slice parameters
        string holder;
        Reader >> holder >> holder >> holder >> holder; //throw away the descriptors
	double length;
	double radius;
	double emissivity;
	double temperature;
	Reader >> length >> radius >> emissivity >> temperature;
	createTube(length, radius, emissivity, temperature);
	cout << "tube created successfully..." << endl;


	Reader >> holder >> holder >> holder; //throw away slice information headers
	int radial_slices;
	int phi_slices;
	int z_slices;
	Reader >> radial_slices >> phi_slices >> z_slices;
	meshTube(radial_slices, phi_slices, z_slices);
	cout << "tube meshed successfully..." << endl;
	
	Reader >> holder >> holder >> holder >> holder; //throw away cell information headers
	int cell_number;
	double temp;
	double a;
	double sigma;
	cvector<double> temps;
        cvector<double> abs_coeffs;
	cvector<double> scatt_coeffs;
	while(!Reader.end_of_file())
	{
		Reader >> cell_number >> a >> sigma >> temp;
		temps.push_back(temp);
		abs_coeffs.push_back(a);
		scatt_coeffs.push_back(sigma);
	}
	cout << "properties successfully out of the reader..." << endl;
	setTemperatures(temps);
	setAbsCoeffs(abs_coeffs);
	setScattCoeffs(scatt_coeffs);
	cout << "gas properties set successfully..." << endl;

}

void MCTube3D::write_source_output(string filename)
{

	ofstream outfile;
	outfile.open(filename.c_str());
	outfile << "r (m),phi (m),z (m),del.q (J/m^3-s)" << endl;
	cvector<double> centroid;
	for(int i = 0; i < cells.size(); i++)
	{
		centroid = cells[i].centroid();
		outfile << centroid[0] << "," << centroid[1] << "," << centroid[2] << "," << cells[i].get_volumetric_source() << endl;
	}

	outfile.close();
}
