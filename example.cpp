/**
 * @file   example.cpp
 * @brief  A simple example code illustrating how to use the Library
 * @date Jan 24, 2021
 * @author Shiladitya Biswas
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





#include<iostream>
#include "matrix.h"
#include<vector>

using namespace std;
using namespace MATOPS; //namespace for matrix.h


int main() {

	// Define matrices of size 2x4 and 2x2 of type double 
	// Matrix<double,2,2> A{{1,2},{3,4}};
	// Matrix<double,3,4> B{{1,2,4,5},{4,6,7,8},{1,2,4,5}};
	
	// Print the Matrices A and B followed by Product A*B and transpose of A
	// cout<<A<<"\n \n"<<B<<"\n \n"<< A*B<<"\n\n"<<A.transpose()<<"\n\n";

	BigMatrix<float> MatObj; // Define float object for Big Matrix
	
	// Multiply two Matrices in .csv format and save the result in Ans.csv file.
	MatObj.matmul("/home/shiladitya/eclipse-workspace/A.csv","/home/shiladitya/eclipse-workspace/B.csv","/home/shiladitya/eclipse-workspace/new.csv");

	// Read Matrix A from A.csv, find its Transpose and save it in A_trans.csv
	// MatObj.Transpose("/path/to/A.csv", "/path/to/A_trans.csv");

	// In-place Transpose: Read Matrix A from A.csv, find its Transpose and overwrite A.csv
	// MatObj.Transpose("/path/to/A.csv");

	// print Matrix in file A.csv
	MatObj.Mat_print("/home/shiladitya/eclipse-workspace/new.csv");

	return 0;
}


