#include "VectorHelpers.h"
#include <iostream>
#include <math.h>

// Vector Helpers
using std::cout;
using std::endl;

int length = 3;

double dotProduct(double x [],double y [])
{
	double product = 0;
	
	for(int i=0; i<length; i++)
	{
		product += x[i]*y[i];
	}
	
	return product;
}

double magnitude(double x [])
{
	double sum = 0;
	
	for(int i=0;i<length;i++)
	{
		sum += pow(x[i],2);
	}
	
	double mag = pow(sum,0.5);
	return mag;
}

double determinant3(double x[3][3])
{
	double ans = x[0][0]*x[1][1]*x[2][2]+x[0][1]*x[1][2]*x[2][0]+x[0][2]*x[1][0]*x[2][1]-x[0][2]*x[1][1]*x[2][0]-x[0][1]*x[1][0]*x[2][2]-x[0][0]*x[1][2]*x[2][1];
	
	return ans;
}

void crossProduct3(double x [], double y [], double product [])
{	
	product[0] = x[1]*y[2]-x[2]*y[1];
	product[1] = x[2]*y[0]-x[0]*y[2];
	product[2] = x[0]*y[1]-x[1]*y[0];
}

void add(double x [], double y [], double sum [])
{	
	for(int i=0;i<length;i++)
	{
		sum[i] = x[i]+y[i];
	}
}

void subtract(double x [], double y [], double sum [])
{
	for(int i=0;i<length;i++)
	{
		sum[i] = x[i]-y[i];
	}
}

void multiply(double x,double y [], double product [])
{
	for(int i=0;i<length;i++)
	{
		product[i] = y[i]*x;
	}
}

void normalize(double x [],double normal [])
{
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

void mat_mult4x4(double x [4][4], double y [4][4], double ans [4][4])
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			ans[i][j] = x[i][0]*y[0][j]+x[i][1]*y[1][j]+x[i][2]*y[2][j]+x[i][3]*y[3][j];
		}
	}
}

void mat_mult4x1(double x[4][4],double y[3],double ans[3])
{
	for(int i=0;i<3;i++)
	{
		ans[i] = x[i][0]*y[0]+x[i][1]*y[1]+x[i][2]*y[2]+x[i][3]*1;
	}
}

void transpose4(double x[4][4], double ans[4][4])
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<3;j++)
		{
			ans[i][j] = x[j][i];
		}
	}
}

void copy(double x[], double copy[])
{
	for(int i=0;i<length;i++)
	{
		copy[i] = x[i];
	}
}