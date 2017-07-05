#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>

class normal_generator	{	//small class names suck

	double rndSave=0.;
	int hasUsed;
public:
	normal_generator(int init): hasUsed(init){};
	double get();
};

double normal_generator::get()	{

	if(!hasUsed)	{

		hasUsed=1;
		return rndSave;
	}

	double s, v1, v2;

	do {

		v1=2.0*rand()/(double)RAND_MAX - 1., v2=2.0*rand()/(double)RAND_MAX - 1.;
		s=pow(v1, 2.)+pow(v2, 2.);

	} while(s==0 || s >=1);

	rndSave = v1*sqrt(-2*log(s)/s);
	hasUsed=0;
	return v2*sqrt(-2*log(s)/s);
}

int main()	{

	srand((unsigned int) time(0));

	normal_generator gen(0);

	int N = pow(10, 4.);

	double* X= new double[N];

	for(unsigned i=0; i<N;i++)	{

		X[i]=gen.get();
	}

	double sum1=0., sum2=0.;

	for(unsigned i = 0; i<N; i++)	{

		sum1 += X[i];
		sum2 += pow(X[i], 2.);
	}

	double mean = sum1/N;
	double std = sqrt((sum2 - pow(mean, 2.))/N);

	int sigmas[3] = {0};

	for(unsigned i=0; i<N; i++)	{

		for(unsigned j=0; j<3; j++)	{

			if(abs(X[i]) < (std*(j+1)))
				sigmas[j]++;
		}
	}

	for(unsigned i=0; i<3; i++)
		std::cout << (i+1) << "\u03C3:" << ((double)sigmas[i]/N)*100. << "%" << std::endl;


	std::cout << "mean: " << mean << std::endl;
	std::cout << "std: " << std << std::endl;

	delete[] X;
}
