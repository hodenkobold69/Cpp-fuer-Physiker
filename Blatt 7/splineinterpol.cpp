#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

double S(int count, double x, double* X, double*Y, double* a, double* b, double* c, double* d);	//spline function

int main(int argc, char** argv)	{

	/**	READ FILE INTO ARRAYS	**/
	std::ifstream file("a16-interpol.dat");
	std::string line;
	int count=0;

	//determine array length
	while(std::getline(file, line))
	   count++;

	//allocate memory
	double* X = (double*)malloc(count*sizeof(double));
	double* Y = (double*)malloc(count*sizeof(double));

	//get to beginning of file again
	file.clear();
	file.seekg(0, file.beg);

	//read file into arrays
	for(unsigned i=0;i<count;i++)	{

		file>>X[i]>>Y[i];
	}

	file.close();

	/**	DETERMINE MATRIX COEFFICIENTS	**/
	//allocate memory (to simplify, i matched the dimensions)
	double* lamb	= (double*)malloc(count*sizeof(double));
	double* mu		= (double*)malloc(count*sizeof(double));
	double* d		= (double*)malloc(count*sizeof(double));

	lamb[0]=mu[count-1]=d[0]=d[count-1]=0;

	//calculate first coefficients
	for(unsigned i=1;i<count-1;i++)	{

		lamb[i]=(X[i+1]-X[i])/(X[i+1]-X[i-1]);
		mu[i]	=(X[i]-X[i-1])/(X[i+1]-X[i-1]);
		d[i]	= (6./(X[i+1]-X[i-1]))*((Y[i+1]-Y[i])/(X[i+1]-X[i])-(Y[i]-Y[i-1])/(X[i]-X[i-1]));

	}

	//calculate second coefficients
	mu[0]=2;

	for(unsigned i=1;i<count;i++)	{

		double f=(-mu[i])/(mu[i-1]);
		mu[i]	=2+f*lamb[i-1];
		d[i]	=d[i]+f*d[i-1];

	}


	//substituting back
	double* M	= (double*)malloc(count*sizeof(double));

	M[count-1]=d[count-1]/mu[count-1];

	for(int i=count-2;i>=0;i--)
		M[i]=(d[i]-lamb[i]*M[i+1])/mu[i];


	//determining spline coefficients
	double* a	= (double*)malloc(count*sizeof(double));
	double* b	= (double*)malloc(count*sizeof(double));
	double* c	= (double*)malloc(count*sizeof(double));
	double* de	= (double*)malloc(count*sizeof(double));

	for(unsigned i=0;i<count-1;i++)	{

		a[i]=Y[i];
		b[i]=(Y[i+1]-Y[i])/(X[i+1]-X[i])-((2.*M[i]+M[i+1])/6.)*(X[i+1]-X[i]);
		c[i]=M[i]/2;
		de[i]=(M[i+1]-M[i])/(6*(X[i+1]-X[i]));
	}

	for(unsigned i=0; i<count-1;i++)	{

		std::cout << "a[" << i << "]=" << a[i]<<std::endl;

	}
	for(unsigned i=0; i<count-1;i++)	{

		std::cout << "b[" << i << "]=" << b[i]<<std::endl;

	}
	for(unsigned i=0; i<count-1;i++)	{

		std::cout << "c[" << i << "]=" << c[i]<<std::endl;

	}
	for(unsigned i=0; i<count-1;i++)	{

		std::cout << "de[" << i << "]=" << de[i]<<std::endl;

	}

	/**	GENERATE OUTPUT FILE	**/
	std::ofstream output("splineoutput.dat");

	const int datapoints = 300;

	for(int i = 0; i < datapoints; i++)
	{
		double x = X[0] + (X[count-1]-X[0]) * ((double)i)/(datapoints-1);

		output << x << "\t" << S(count, x, X, Y, a, b, c, de) << std::endl;
	}

	output.close();

	free(a);free(b);free(c);free(d);free(mu);free(lamb);free(de);free(M); free(X);free(Y);
}

double S(int count, double x, double* X, double*Y, double* a, double* b, double* c, double* d)	{

	int i = 0;

	while(X[i + 1] < x)	{

		i++;

		if(i == (count-1))	{

			std::cout << "OUT OF RANGE: x = " << x << std::endl;
			return 0.;
		}

	}

	return
		a[i]
		+ b[i]*(x - X[i])
		+ c[i]*(x - X[i])*(x - X[i])
		+ d[i]*(x - X[i])*(x - X[i])*(x - X[i]);
}
