#include <iostream>
#include <math.h>

// Vector Helpers
using std::cout;
using std::endl;

int length = 3;

double dotProduct(double x [],double y [])
{
	double product = 0;
	
	//int length = sizeof(&x)/sizeof(double);
	
	/*if(length != sizeof(&y)/sizeof(double))
	{
		throw std::runtime_error(std::string("Vectors must be the same size"));
	}*/
	
	for(int i=0; i<length; i++)
	{
		product += x[i]*y[i];
	}
	
	return product;
}

double* crossProduct(double x [], double y [], double product [])
{	
	//int length = sizeof(&x)/sizeof(double);
	
	//cout << "Cross length " << length << endl;
	
	/*if(length != sizeof(&y)/sizeof(double))
	{
		throw std::runtime_error(std::string("Vectors must be the same size"));
	}
	else if(length != 3)
	{
		//throw std::runtime_error(std::string("Cross Product only works for vectors of size 3"));
	}*/
	
	product[0] = x[1]*y[2]-x[2]*y[1];
	product[1] = x[2]*y[0]-x[0]*y[2];
	product[2] = x[0]*y[1]-x[1]*y[0];
	
	return product;
}

double* add(double x [], double y [], double sum [])
{
	//int length = sizeof(&x)/sizeof(double);
	
	/*if(length != sizeof(&y)/sizeof(double))
	{
		throw std::runtime_error(std::string("Vectors must be the same size"));
	}*/
	
	for(int i=0;i<length;i++)
	{
		sum[i] = x[i]+y[i];
	}
	
	return sum;
}

double* subtract(double x [], double y [], double sum [])
{
	//int length = sizeof(&x)/sizeof(double);
	
	/*if(length != sizeof(&y)/sizeof(double))
	{
		throw std::runtime_error(std::string("Vectors must be the same size"));
	}*/
	
	for(int i=0;i<length;i++)
	{
		sum[i] = x[i]-y[i];
	}
	
	return sum;
}

double* multiply(double x,double y [], double product [])
{
	//int length = sizeof(&y)/sizeof(double);
	
	for(int i=0;i<length;i++)
	{
		product[i] = y[i]*x;
	}
	
	return product;
}

double* normalize(double x [],double normal [])
{
	//int length = sizeof(&x)/sizeof(double);
	
	//cout << "normal length: " << length << endl;
	double sum = 0;
	
	for(int i=0;i<length;i++)
	{
		sum += pow(x[i],2);
	}
	
	sum = pow(sum,0.5);
	
	for(int i=0;i<length;i++)
	{
		normal[i] = x[i]/sum;
	}
	
	return normal;
}

double magnitude(double x [])
{
	double mag = pow(pow(x[0],2)+pow(x[1],2)+pow(x[2],2),0.5);
	return mag;
}

void mat_mult3x3(double x [3][3], double y [3][3], double ans [3][3])
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			ans[i][j] = x[i][0]*y[0][j]+x[i][1]*y[1][j]+x[i][2]*y[2][j];
		}
	}
}

void mat_mult3x1(double x[3][3],double y[3],double ans[3])
{
	for(int i=0;i<3;i++)
	{
		ans[i] = x[i][0]*y[0]+x[i][1]*y[1]+x[i][2]*y[2];
	}
}

void transpose3(double x[3][3], double ans[3][3])
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			ans[i][j] = x[j][i];
		}
	}
}

double determinant3(double x[3][3])
{
	double ans = x[0][0]*x[1][1]*x[2][2]+x[0][1]*x[1][2]*x[2][0]+x[0][2]*x[1][0]*x[2][1]-x[0][2]*x[1][1]*x[2][0]-x[0][1]*x[1][0]*x[2][2]-x[0][0]*x[1][2]*x[2][1];
	
	return ans;
}