

/*
	These are methods that run common vector and matrix operations on arrays of doubles
	
	-RB Johnson, 10/5/2016
*/

double dotProduct(double x [],double y []);

double magnitude(double x[]);

double determinant3(double x[3][3]);

void crossProduct(double x [], double y [],double product []);

void add(double x [], double y [], double sum []);

void subtract(double x [], double y [], double sum []);

void multiply(double x,double y [], double product []);

void normalize(double x [], double normal[]);

void mat_mult3x3(double x[3][3],double y[3][3],double ans[3][3]);

void mat_mult3x1(double x[3][3],double y[3],double ans[3]);

void transpose3(double x[3][3],double ans[3][3]);


