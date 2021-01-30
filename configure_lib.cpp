/**
 * @file configure_lib.cpp
 * @author Shiladitya Biswas
 * @brief A Cpp configuration file to find the best leaf size for Stressan's Algorithm. This file evaluates the execution time of the matmul function in class BigMatrix as function of different LEAF_SIZE.
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

using namespace std;
using namespace MATOPS;

int main(int argc, char** argv){

    cout<<"------------ Program to find out optimal LEAF_SIZE ---------------\n";

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
    int l_size;
    int low_lim= atoi(argv[2]);
    int upper_lim=atoi(argv[3]);

    for(l_size=low_lim;l_size<=upper_lim;l_size=2*l_size) // changing leaf size
        {  //cout<<"Testing for: "<<l_size<<'\n';
            MatObj.set_LEAF_SIZE(l_size);
            double temp_time=0;
            for(int n=0;n<N_epoch;n++) // Number of times the library is run
            {   //cout<<n<<'\n';
                
                auto start = std::chrono::steady_clock::now();
                MatObj.matmul(path_to_A,path_to_B,path_to_C);
                auto end = std::chrono::steady_clock::now();
                
                std::chrono::duration<double> elapsed_seconds = end-start;
                temp_time+=elapsed_seconds.count();

            }
            temp_time/=N_epoch;
            
            if(temp_time<min_time)
            {
                min_time=temp_time;
                final_leaf_size=l_size;
            }
        }

        cout<<"Best Leaf size = "<<final_leaf_size<<'\n';

    return 0;
}



