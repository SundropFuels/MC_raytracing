#ifndef CVECTOR
#define CVECTOR


/********************************************************************************
cvector.h

Class definition for Chris' vector class -- based on STL containers, build from scratch

Version 1.0

*********************************************************************************/
using namespace std;
#include <iostream>
#include <cstdlib>


template <typename vElement>
class cvector
{
	public:
	//Constructors
	cvector();					//default
	cvector(int capacity);
	cvector(int capacity, vElement value);
	cvector(const cvector & original);		//copy constructor
	~cvector();					//destructor

	//accessors
	int capacity() const;				//returns current capacity
	int size() const;				//returns current size
	bool empty() const;				//evaluates whether vector is empty
	void reserve(int n);				//increase capacity to n
	void print() const;				//show the vector on the screen
	void clear();					//this clears the vector (sets size = 0)

	//mutators
	void push_back(vElement value);			//add value to the back of the vector, increase cap if necessary
	void push_front(vElement value);		//add value to the front of the vector, increase cap it necessary	
	void pop_back();				//remove last element of vector
	vElement & front();				//return a reference to the first element of the vector
	vElement & back();				//return a reference to the last element of the vector

	//operators
	cvector<vElement> & operator=(const cvector<vElement> & original);	//assignment operator
	vElement & operator[](int index);					//index
	const vElement & operator[](int index) const;				//constant index
	cvector<vElement> operator+(const cvector<vElement> & v2);		//vector addition
	cvector<vElement> operator*(const vElement & k);			//scalar multiplication	

	vElement operator*(const cvector<vElement> & v2);			//inner (dot) product

	//may need to add some const versions of these

	//comparators
	template <typename vElement1> friend bool operator== (const cvector<vElement1> & v1, const cvector<vElement1> & v2);



	private:

	int mySize;
	int myCapacity;
	vElement *myElements;



};

//implementation of class functions


/***************************************constructors/destructors**************************************************/
template <typename vElement>
cvector<vElement>::cvector()
{
	myCapacity = 4;					//some minimal amount of memory allocated
	mySize = 0;
	myElements = new vElement[myCapacity];	
	
}

template <typename vElement>
cvector<vElement>::cvector(int capacity)
{
	myCapacity = capacity;
	mySize = 0;
	myElements = new vElement[myCapacity];
	
}

template <typename vElement>
cvector<vElement>::cvector(int capacity, vElement value)
{
	myCapacity = capacity;
	mySize = myCapacity;
	myElements = new vElement[myCapacity];
	for(int i = 0; i<mySize; i++)
	{
		myElements[i] = value;
	}


	
}

template <typename vElement>
cvector<vElement>::cvector(const cvector & original)
{
	myCapacity = original.capacity();
	myElements = new vElement[myCapacity];	
	
	mySize = original.size();
	for(int i = 0; i<mySize; i++)
	{
		myElements[i] = original[i];
	}

	
}

template <typename vElement>
cvector<vElement>::~cvector()
{
	delete[] myElements;
	myElements = NULL;
	
						
}

/*********************************************accessors/mutators***********************************************************/
template <typename vElement>
int cvector<vElement>::capacity() const
{
	return myCapacity;
}

template <typename vElement>
int cvector<vElement>::size() const
{
	return mySize;
}

template <typename vElement>
bool cvector<vElement>::empty() const
{
	return (mySize == 0);
}

template <typename vElement>
void cvector<vElement>::print() const
{
	cout << "| " ;	
	for(int i=0; i<mySize-1; i++)
	{
		cout << myElements[i] << "\t";
	}
	cout << myElements[mySize-1] << " |" << endl;
	return;
}

template <typename vElement>
void cvector<vElement>::clear()
{
	mySize = 0;
}


template <typename vElement>
void cvector<vElement>::reserve(int n)
{
	if(n<myCapacity)
	{
		cout << "Cannot shrink vectors...data loss possible!  Exiting..." << endl;
		exit(1);
	}
		

	//first step: create a new array to hold the elements of capacity n
	vElement *newElements = new vElement[n];
	
	//second step: copy information from myElements to newArray
	for(int j=0; j<mySize;j++)
	{
		newElements[j] = myElements[j];
	}

	//third step: update capacity information
	myCapacity = n;

	//fourth step: deallocate memory of myElements
	delete[] myElements;

	//final step: set memory location of myElements equal to that of newElements
	myElements = newElements;			
}

template <typename vElement>
void cvector<vElement>::push_back(vElement value)
{
	if(mySize == myCapacity)			//make space if required
	{
		reserve(2*myCapacity);
	}

	mySize++;
	myElements[mySize-1] = value;
}

template <typename vElement>
void cvector<vElement>::push_front(vElement value)
{
	if(mySize == myCapacity)
	{
		reserve(2*myCapacity);
	}
	
	cvector<vElement> vcopy(*this);
	mySize++;
	myElements[0] = value;
	for(int i = 1; i < mySize; i++)
	{
		myElements[i] = vcopy[i-1];
	}
}

template <typename vElement>
void cvector<vElement>::pop_back()
{
	if(empty())
	{
		cout << "The vector was empty...that won't work." << endl;
		exit(1);
	}

	mySize--;					//simply move the pointer
}

template <typename vElement>
vElement & cvector<vElement>::front()
{
	if(empty())
	{
		cout << "The vector is empty...that won't work." << endl;
		exit(1);
	}
	
	return myElements[0];
}

template <typename vElement>
vElement & cvector<vElement>::back()
{
	if(empty())
	{
		cout << "The vector is empty...that won't work." << endl;
		exit(1);
	}

	return myElements[mySize-1];
}


/*************************************operators**********************************/

template <typename vElement>
cvector<vElement> & cvector<vElement>::operator=(const cvector<vElement> & original)
{
	if (this != &original)				//make sure you don't set something equal to itself
	{
		delete[] myElements;
		myCapacity = original.capacity();
		myElements = new vElement[myCapacity];
		
		if (myElements == 0)
		{
			cout << "**********INADEQUATE MEMORY ****************" << endl;
			exit(1);
		}		
		
		mySize = original.size();

		for(int j=0; j<mySize; j++)
		{
			myElements[j] = original[j];
		}

	}

	return *this;
}

template <typename vElement>
vElement & cvector<vElement>::operator[](int index)
{
	if(index>=mySize)
	{
		cout << "Index beyond capacity of vector, exiting..." << endl;
		exit(1);
	}

	return myElements[index];
}

template <typename vElement>
const vElement & cvector<vElement>::operator[](int index) const
{
	if(index>=mySize)
	{
		cout << "Index beyond capacity of vector, exiting..." << endl;
		exit(1);
	}

	return myElements[index];
}

template <typename vElement>
cvector<vElement> cvector<vElement>::operator+(const cvector<vElement> & v2)
{
	if(mySize != v2.size())
	{
		cout << "Vectors not of equal size.  Addition not possible.  Exiting..." << endl;
		exit(1);
	}

	cvector<vElement> v3 = v2;
	for(int j = 0; j < mySize; j++)
	{
		v3[j] = myElements[j] + v2[j];
	}
	
	return v3;  
}

template <typename vElement>
cvector<vElement> cvector<vElement>::operator*(const vElement & k)
{
	cvector<vElement> scaledVec(myCapacity);
	for(int i=0; i<mySize; i++)
	{
		scaledVec.push_back(k*myElements[i]);
	}

	return scaledVec;

}

template <typename vElement>
vElement cvector<vElement>::operator*(const cvector<vElement> & v2)
{
	if(mySize != v2.size())
	{
		cout << "Dot product requires equal size vectors" << endl;
		exit(1);
	}

	vElement val = 0;
	for(int p=0; p < mySize; p++)
	{
		val = val + myElements[p]*v2[p];
	}

	return val;
}

/**************************************comparators**********************************************/
template <typename vElement1>
bool operator==(const cvector<vElement1> & v1, const cvector<vElement1> & v2)
{
	bool equal = 1;
	if(v1.size() != v2.size())
	{
		equal = 0;
		return equal;			//get out early before element by element checking
	}

	for(int i = 0; i < v1.size(); i++)
	{
		if(v1[i] != v2[i])
		{
			equal = 0;
			return equal;
		}
	}

	return equal;
}

	



#endif

