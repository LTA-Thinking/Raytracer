

/*
	These are methods that run common vector and matrix operations on arrays of doubles
	
	-RB Johnson, 10/5/2016
*/

double dotProduct(double x [],double y []);

double* crossProduct(double x [], double y [],double product []);

double* add(double x [], double y [], double sum []);

double* subtract(double x [], double y [], double sum []);

double* multiply(double x,double y [], double product []);

double* normalize(double x [], double normal[]);

double magnitude(double x[]);

void mat_mult3x3(double x[3][3],double y[3][3],double ans[3][3]);

void mat_mult3x1(double x[3][3],double y[3],double ans[3]);

void transpose3(double x[3][3],double ans[3][3]);

double determinant3(double x[3][3]);
