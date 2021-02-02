/**
 * @file configure_lib.cpp
 * 
 * @brief A Cpp configuration file to find the best leaf size for Stressan's Algorithm and generate a "configure.txt" file. This file evaluates the 
 * execution time of the MATOPS::BigMatrix<Data1>::matmul() function as function of different LEAF_SIZE values. This flag is always run with the 
 * SET_LEAF_SIZE flag. This flag enables the matrix.h file to run in configuration mode. Thus enabling configure_lib.cpp to vary LEAF_SIZE variable 
 * of matrx.h and find the most optimal LEAF_SIZE value. For a given LEAF_SIZE value this program calls MATOPS::BigMatrix<Data1>::matmul() N_epoch (>2)
 * no. of times and finds out the average execution time of MATOPS::BigMatrix<Data1>::matmul() for that particular LEAF_SIZE. Use the following command 
 * to run the configure_lib.cpp file
 * 
 * \code{.sh}
 *  $ g++ configure_lib.cpp -o configure_lib -DSET_LEAF_SIZE && ./configure_lib <N_epoch>
 * \endcode
 * 
 * The program begins with LEAF_SIZE = 8, calls MATOPS::BigMatrix<Data1>::matmul() N_epoch times and calculates the average execution time of matmul 
 * over all the calls and stores it in a varaible min_time. It continues doing the same for LEAF_SIZE=16, 32,64 ..... as min_time keeps reducing.
 * As soon as the value of min_time starts increasing we break out of the inifinite while loop and store the LEAF_SIZE value that gave the least min_time
 * in a configure.txt file. This file is later used by matmul to multiply big matrices.
 *  
 * @author Shiladitya Biswas
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
                MatObj.matmul("Configure_Data/large_A.csv","Configure_Data/large_B.csv","Configure_Data/Ans.csv");
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



