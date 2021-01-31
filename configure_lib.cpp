/**
 * @file configure_lib.cpp
 * @author Shiladitya Biswas
 * @brief A Cpp configuration file to find the best leaf size for Stressan's Algorithm and generate a "configure.txt" file. This file evaluates the 
 * execution time of the matmul function in class BigMatrix as function of different LEAF_SIZE.
 * @version 0.1
 * @date 2021-01-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include<iostream>
#include "matrix.h"
#include<chrono>
#include<float.h>
#include<stdlib.h>
#include<fstream>
using namespace std;
using namespace MATOPS;

int main(int argc, char** argv){

    cout<<"------------ Program to find out optimal LEAF_SIZE ---------------\n";

    std::ofstream file;
	file.open("configure.txt"); // Open configure.txt file

    int N_epoch=atoi(argv[1]);
    BigMatrix<int> MatObj;
    
    string path_to_A, path_to_B,path_to_C;

    // Get the path to the Big Matrices (Matrix csv files)
    cout<<"Enter path to Matrix A: ";
    getline(cin,path_to_A);

    cout<<"Enter path to Matrix B: ";
    getline(cin,path_to_B);

    cout<<"Enter path to store Result of A*B: ";
    getline(cin,path_to_C);
	
    cout<<"Configuring ......\n";
    
    double min_time= DBL_MAX;
    int final_leaf_size=0;
    int l_size=8;
        // While loop to keep checking and tracking the best LEAF SIZE for the Library. Once we find the LEAF_SIZE that gives 
        // has the best/ lowest execution time we break out of the while loop and store the LEAF_SIZE value in a configure.txt file.
        while(1) 
        {   
            cout<<"Testing Library with LEAF_SIZE: "<<l_size<<'\n';
            MatObj.set_LEAF_SIZE(l_size); // set the LEAF_SIZE value in the matrix.h file.
            double temp_time=0;
            for(int n=0;n<N_epoch;n++) // Run the multiplication process for N_epoch of times for a fixed LEAF_SIZE value.
            {   
                // Determine the Time taken to do the multiplication operation
                auto start = std::chrono::steady_clock::now();
                MatObj.matmul(path_to_A,path_to_B,path_to_C);
                auto end = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds = end-start;
                temp_time+=elapsed_seconds.count();

            }
            temp_time/=N_epoch; // Find the average time taken over the N_epoch steps
            
            if(temp_time<min_time) // Find the LEAF_SIZE for which the least time is taken.
            {
                min_time=temp_time;
                final_leaf_size=l_size;
            }
            else
            {
                break;
            }
            l_size=2*l_size; // Double the leaf_size after every iteration
        }
        // cout<<final_leaf_size;
        
        file<<final_leaf_size<<'\n';  // Store the Optimal LEAF_SIZE value in a txt file 
        cout<<"configure.txt File Generated \n";
        file.close();
        // cout<<"Best Leaf size = "<<final_leaf_size<<'\n';

    return 0;
}



