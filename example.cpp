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
* Matrix<double,2,4> B{{1,2,4,5},{4,6,7,8}}; // Define Matrix B of size 2x4 and initialize it using initializer list.
*
* Matrix<double,2,2> A{{1,2},{2,2}}; // Define Matrix A of size 2x2 and initialize it using initializer list.
*
* cout<<A<<"\n \n"<<B<<"\n \n"<< A*B<<"\n\n";
*
* BigMatrix<float> MatObj; // Define BigMatrix object.
* 
* float** a=MatObj.matmul("/path/to/A.csv","/path/to/B.csv","/path/to/Ans.csv"); Taking Matrices A and B from csv file and multiply using matmul function. 
*
* cout<<a[0][0]<<" "<<a[1][0]<<" "<<a[2][0]<<" "<<a[3][0]<<" "<<a[4][0]<<" \n\n";
*
* float** b=MatObj.Transpose("/path/to/A.csv", "/path/to/A_trans.csv"); Taking Matrix A from CSV file and finding its transpose usinf Transpose function.
*
* MatObj.Mat_print("/path/to/A.csv"); // Printing Matrix A in stdio.
*
* free(a);
*
* free(b);
*
* return 0;
*/


int main() {
	cout << "!!!Hello World!!! \n" << endl; // prints !!!Hello World!!!

	cout<<__cplusplus<<'\n';
	
	Matrix<double,2,4> B{{1,2,4,5},{4,6,7,8}};
	Matrix<double,2,2> A{{1,2},{2,2}};

	cout<<A<<"\n \n"<<B<<"\n \n"<< A*B<<"\n\n";

	BigMatrix<float> MatObj;

	float** a=MatObj.matmul("/home/shiladitya/eclipse-workspace/A.csv","/home/shiladitya/eclipse-workspace/B.csv","/home/shiladitya/eclipse-workspace/Ans.csv");

	cout<<a[0][0]<<" "<<a[1][0]<<" "<<a[2][0]<<" "<<a[3][0]<<" "<<a[4][0]<<" \n\n";

	float** b=MatObj.Transpose("/home/shiladitya/eclipse-workspace/A.csv", "/home/shiladitya/eclipse-workspace/A_tras.csv");

	MatObj.Mat_print("/home/shiladitya/eclipse-workspace/A.csv");

	free(a);
	free(b);
	return 0;
}

