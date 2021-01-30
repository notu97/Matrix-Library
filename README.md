# Matrix-Library

A simple Matrix library to perform  Matrix operations namely Matrix Multiplication and Transpose. The library is divided into 2 parts, one for Matrix operations on small Matrices (class Matrix) and other for Large Matrices (class BigMatrix). The complete code documentation generated by Doxygen can be found [here](https://notu97.github.io/Matrix-Library/index.html).

Matrix multiplication for small matrices is done using the straight forward solution with time complexity `O(n^3)`. While for large matrices the Matrix multiplication is done using the Strassen's Algorithm that has Time Complexity of approximatley `O(n^2.8)`.

For Large Matrices the input is taken in a Comma Separated Variable (csv) file format, and the output is stored in a csv file. For small matrices the user has to manually enter the values of the matrix either using a initializer_list format or as a 2D vector. 

## Installation and Configuration
Just include the [matrix.h](https://github.com/notu97/Matrix-Library/blob/main/matrix.h) header file in your C++ working directory and include it in your main cpp code using #include"matirx.h". Inorder to have the best performance from this library in terms of Matrix Multiplicaiton, on has to experimentally find out and set the LEAF_SIZE for the Stressan's Multiplcation Library. In order to find this value two 2000x2000 matrices were multiplied (for N_epoch 10 times, for each time the execution time was recorded and eventually the average of all the 10 reading were taken) with differnt values of LEAF_SIZE ranging from SIZE_Lower=8 to SIZE_upper=512. For my computer the optimal ```LEAF_SIZE``` was found to be 64. The ```LEAF_SIZE``` will vary from computer to computer, hence a [configure_lib.cpp](https://github.com/notu97/Matrix-Library/blob/main/configure_lib.cpp) and its correponding object file ```configure_lib``` is provided with this library. The command to find the optimal ```LEAF_SIZE``` is as follows:

``` sh

./configure_lib <N_epoch> <SIZE_Lower> <SIE_upper>

```


## Usage
### Matrix Class (for small Matrices)
#### Defining a small Matrix of size 3x4 of type float

Using initilizer list
``` C++
MATOPS::Matrix<float,3,4> A{{1,2,3,4},{5,6,7,8},{9,10,11,12}};

```

Using 2D std::vector
``` C++

std::vector<std::vector<float>> vect {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
MATOPS::Matrix<float,3,4> A(vect);

```

#### Transposing a small Matrix
``` C++
MATOPS::Matrix<float,3,4> A{{1,2,3,4},{5,6,7,8},{9,10,11,12}};
std::cout<< A.transpose();
```

#### Multiplying 2 small Matrices
``` C++
MATOPS::Matrix<float,3,4> A{{1,2,3,4},{5,6,7,8},{9,10,11,12}};
MATOPS::Matrix<float,4,2> B{{1,2},{5,6},{9,10},{3,4}};
MATOPS::Matrix<float,3,2> C=A*B;

std::cout<< C;
//OR
std::cout<<A*B;
```

### BigMatrix Class (for large Matrices)
Since big Matrices are already defined in a csv file, we can just parse the files and find out the dimensions of the matrix. The only information to be given to the header file is the Datatype of the Matrix. 

#### BigMatrix Multiply (Strassen's Algorithm)
Let there be 2 matrices A and B stored in 2 csv files namely A.csv and B.csv repectively. We wish to multiply both of them and store the result in a third file named Ans.csv . The code for this process is shown below.

``` C++
MATOPS::BigMatrix<float> MatObj; // Defining a Matrix object

// Multiplying the two Matrices A.csv, B.csv and storing the result in Ans.csv
MatObj.matmul("/path/to/A.csv","/path/to/B.csv","/path/to/Ans.csv");

MatObj.Mat_print("/path/to/Ans.csv"); // Printing the Answer
```
#### BigMatrix Transpose
Given a matrix A in A.csv file, we wish to find out its transpose and store it in a new file A_trans.csv

``` C++
MATOPS::BigMatrix<float> MatObj; // Defining a Matrix object
MatObj.Transpose("/path/to/A.csv", "/path/to/A_trans.csv"); // Transposing the matrix and store in a A_trans.csv

MatOnj.Transpose("/path/to/A.csv"); // In-place Matrix transpose.

MatObj.Mat_print("/path/to/A_trans.csv"); // Printing the result
```

## Example code
```  C++
#include<iostream>
#include "matrix.h"
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
	MatObj.matmul("/path/to/A.csv","/path/to/B.csv","/path/to/Ans.csv");

	// Read Matrix A from A.csv, find its Transpose and save it in A_trans.csv
	MatObj.Transpose("/path/to/A.csv", "/path/to/A_trans.csv");

	// In-place Transpose: Read Matrix A from A.csv, find its Transpose and overwrite A.csv
	MatObj.Transpose("/path/to/A.csv");

	// print Matrix in file A.csv
	MatObj.Mat_print("/path/to/A.csv");

	return 0;
}


```




