# Matrix-Library

A simple Matrix library to perform Matrix Multiplication(using Strassen's Algorithm) and Transpose(Coming Soon !!!).

```  C++
#include<iostream>
#include <matrix.h>
#include<vector>

using namespace std;
using namespace MATOPS;


int main() {
	
	// Define matrices of size 2x4 and 2x2 of type double
	Matrix<double,2,4> B{{1,2,4,5},{4,6,7,8}};  
	Matrix<double,2,2> A{{1,2},{2,2}};
	
	// Print the Matrices and their Product A*B
	cout<<A<<"\n \n"<<B<<"\n \n"<< A*B<<"\n\n";

	BigMatrix<float> MatObj;

	float** a=MatObj.matmul("/path/to/A.csv","/path/to/B.csv","/path/to/Ans.csv");


	float** b=MatObj.Transpose("/path/to/A.csv", "/path/to/A_tras.csv");

	MatObj.Mat_print("/path/to/A.csv");

	free(a);
	free(b);
	return 0;
}


```
