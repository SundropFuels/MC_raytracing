#include <iostream>
#include <cmath>
#include <cstdlib>
//#include "../random_numbers/sfmt.h"
#include "../random_numbers/randomc.h"


using namespace std;

int main()
{

	cout << "This is the random number generator testor for c++" << endl;

	int seed = time(0);

	//create the random number generator
	CRandomMother rand_gen(seed);

	for(int i = 0; i < 20; i++)
	{

		cout << rand_gen.Random() << endl;
	}


	return 1;
}
