/**
 * @file configure_lib.cpp
 * @author Shiladitya
 * @brief A Cpp configuration file to find the best leaf size for Stressan's Algorithm.
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

using namespace std;
using namespace MATOPS;

int main(){

    // int leaf_s=64;
    int N_epoch=5;
    BigMatrix<int> MatObj;
    
    string path_to_A, path_to_B,path_to_C;
    /**
     * @brief Get the path to the Big Matrices (Matrix csv files)
     * 
     */
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
    
    for(l_size=8;l_size<=256;l_size=2*l_size) // changing leaf size
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

                // std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

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



