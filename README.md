# Matrix-Library

A simple Matrix library to perform  Matrix operations namely Matrix Multiplication and Transpose. The library is divided into 2 parts, one for Matrix operations on small Matrices (class Matrix) and other for Large Matrices (class BigMatrix). The complete code documentation generated by Doxygen can be found [here](https://notu97.github.io/Matrix-Library/index.html).

Matrix multiplication for small matrices is done using the straight forward solution with time complexity `O(n^3)`. While for large matrices the Matrix multiplication is done using the Strassen's Algorithm that has Time Complexity of approximatley `O(n^2.8)`.

For Large Matrices the input is taken in a Comma Separated Variable (csv) file format, and the output is stored in a csv file. For small matrices the user has to manually enter the values of the matrix either using a initializer_list format or as a 2D vector. 

## Installation
Just include the [matrix.h](https://github.com/notu97/Matrix-Library/blob/main/matrix.h) header file in your C++ working directory and include it in your main cpp code using #include<matirx.h>


## Usage


## Example code
```  C++
#include<iostream>
#include <matrix.h>
#include<vector>

using namespace std;
using namespace MATOPS; //namespace for matrix.h


int main() {
	
	// Define matrices of size 2x4 and 2x2 of type double
	Matrix<double,2,4> B{{1,2,4,5},{4,6,7,8}};  
	Matrix<double,2,2> A{{1,2},{2,2}};
	
	// Print the Matrices A and B followed by Product A*B and transpose of A
	cout<<A<<"\n \n"<<B<<"\n \n"<< A*B<<"\n\n"<<A.transpose()<<"\n\n";

	BigMatrix<float> MatObj; // Define float object for Big Matrix
	
	// Multiply two Matrices in .csv format and save the result in Ans.csv file.
	float** a=MatObj.matmul("/path/to/A.csv","/path/to/B.csv","/path/to/Ans.csv");

	// Read Matrix A from A.csv, find its Transpose and save it in A_trans.csv
	float** b=MatObj.Transpose("/path/to/A.csv", "/path/to/A_trans.csv");

	// print Matrix in file A.csv
	MatObj.Mat_print("/path/to/A.csv");

	// free the a and b pointers.
	free(a);
	free(b);
	return 0;
}


```
