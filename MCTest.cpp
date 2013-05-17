#include <iostream>
#include "MCTube3D.h"
#include "cvector.cpp"
#include <string>
#include <cstdlib>




using namespace std;

int main(int argc, char **argv)
{
	string output_filename, input_filename, option;

	for(int a = 1; a < argc; a++)
	{
		option = argv[a];
		if(option == "-i")
		{
			input_filename = argv[a+1];
		}
		else if(option == "-o")
		{
			output_filename = argv[a+1];
		}

	}

	cout << "The output filename is " << output_filename << endl;
	cout << "The input filename is " << input_filename << endl;

	//csv_reader Reader(input_filename);
	MCTube3D simulator(input_filename);	
	/*	
	MCTube3D simulator;
	double length = 2.0;
	double radius = 0.2;
	double emissivity = 0.9;
	double temperature = 1673;
	
	simulator.createTube(length, radius, emissivity, temperature);
	int radial_slices = 1;
	int phi_slices = 1;
	int z_slices = 30;


	simulator.meshTube(radial_slices, phi_slices, z_slices);
	cvector<double> temps;
	cvector<double> abs_coeffs;
	cvector<double> scatt_coeffs;

	

	for(int i =0; i < (radial_slices * phi_slices * z_slices); i++)
	{
			
		temps.push_back(900);
		abs_coeffs.push_back(8.0);
		scatt_coeffs.push_back(0.2);
	}

	simulator.setTemperatures(temps);
	simulator.setAbsCoeffs(abs_coeffs);
	simulator.setScattCoeffs(scatt_coeffs);
	*/
	//Now, as a check, I'll just print each of the cell numbers and the volume/temperature of each of the cells

	simulator.print_mesh();
	simulator.calculate_viewfactors(1000000);
	simulator.calculate_source_terms();
	simulator.write_source_output(output_filename);


	return 0;
}
