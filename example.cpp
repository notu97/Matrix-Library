/**
 * @file   example.cpp
 *
 * @date Jan 24, 2021
 * @author shiladitya
 *
 *
 * This is an example code illustrating how to use the matrix.h library.
 *
 */


//============================================================================
// Name        : example.cpp
// Author      : Shiladitya Biswas
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================





#include <iostream>
#include <matrix.h>

#include<vector>

using namespace std;
using namespace MATOPS;

/**
* Call the function and proceed 
*
*/
int main() {
	cout << "!!!Hello World!!! \n" << endl; // prints !!!Hello World!!!

	cout<<__cplusplus<<'\n';
	
	Matrix<double,2,4> B{{1,2,4,5},{4,6,7,8}};
	Matrix<double,2,2> A{{1,2},{2,2}};

	cout<<A<<"\n \n"<<B<<"\n \n"<< A*B<<"\n\n";

	BigMatrix<float> MatObj;

	float** a=MatObj.matmul("/path/to/A.csv","/path/to//B.csv","/path/to/Ans.csv");

	//cout<<a[0][0]<<" "<<a[1][0]<<" "<<a[2][0]<<" "<<a[3][0]<<" "<<a[4][0]<<" \n\n";

	float** b=MatObj.Transpose("/path/to/A.csv", "/path/to/A_tras.csv");

	MatObj.Mat_print("/path/to/A.csv");

	free(a);
	free(b);
	return 0;
}

