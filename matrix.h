/**
 * @file matrix.h
 * @author Shiladitya Biswas (https://github.com/notu97)
 * @brief The main Matrix library header file. 
 * @version 0.1
 * @date 2021-01-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include<iostream>
#include<stddef.h>
#include<vector>
#include<stdexcept>
#include<initializer_list>
#include<sstream>
#include<fstream>
#include<string.h>

/**
 * @brief The main matrix.h namespace named MATOPS- MATrix OPerations. It contains 2 Matrix classes, namely class Matrix and class BigMatrix to perform matrix operations.
 * The class Matrix uses the naive O(n^3) solution to perform matrix multiplication and the class BigMatrix uses a mixture of Strassesn's algorithm and Naive O(n^3) 
 * solution to perform Matrix multiplication. Both the classes perform matrix transpose in similar fashion, i.e. by swapping the off diagonal elements.
 */
namespace MATOPS
{

		/**
		 * @brief This class is for matrices of smaller size. The user can define a Matrix A of size m x n of Datatype T as follows: MATOPS::Matrix<T,m,n> A.
		 * @tparam T = DataType of the Matrix. Eg. int, float, double etc.
		 * @tparam m = No. of Rows of the Matrix
		 * @tparam n = No. of Cols of the Matrix
		 * 
		 * Warning: This class can't handle really large matrices. On initilizing large Matrices the program stack gets filled with data and there is no space left
		 * to do other operations. Care should be taken that the matrix sizes are less than 200.
		 */
		template<typename T, size_t m, size_t n>
		class Matrix{

			T array[m][n];
			public:

			/**
			 * Destructor
			 */
			virtual ~Matrix() {}

			/**
			 * @return Returns the number of columns in the Matrix
			 */
			size_t cols()
			{
				return n;
			}

			/**
			 *
			 * @return Returns the number of Rows in the Matrix.
			 */
			size_t rows()
			{
				return m;
			}


			// Default Matrix Initialization
			/**
			 * @brief Default constructor to initialize the matrix with zeros.
			 */
			Matrix()
			{
				for(size_t i=0;i<m;i++)
				{
					for(size_t j=0;j<n;j++)
					{
						array[i][j]=0;
					}
				}
			}

			// Initialize Matrix from Initializer_list
			/**
			 * @brief Overloaded constructor the initialize the Matrix from a 2D Initializer list.
			 * @param my_list = A 2D initializer_list of the the m x n Matrix. Eg: {{1,2},{3,4}}
			 */
			Matrix(std::initializer_list<std::initializer_list<T>> my_list):Matrix()
				{	
					//std::cout<<my_list(0).<<'\n';
					try{
						if((m!=my_list.size()))
						{
							throw "Wrong Matrix dimension initialized\n";
						}
					}catch (const char* msg)
					{
						std::cerr<< msg<<'\n';
						exit(0);
					}


					int row_n=0;
					for(std::initializer_list<T> i:my_list)
					{   int col_n=0;

						try{
						if((n!=i.size()))
						{
							throw "Wrong Matrix dimension initialized\n";
						}
						}catch (const char* msg)
						{
							std::cerr<< msg<<'\n';
							exit(0);
						}

						for(T j : i)
						{
							ElementAt(row_n,col_n)=j;
							col_n++;
							// cout<<j<<" ";
						}
						row_n++;
						//cout<<'\n';
					}
				}


			// Initialize the Matrix from 2D Vectors
			/**
			 * @brief Overloaded constructor to initialize the Matrix from a 2D Vector.
			 * @param my_vec = A 2D initializer_list of the the m x n Matrix. Eg: {{1,2},{3,4}}
			 */
			Matrix( std::vector<std::vector<T>>& my_vec):Matrix()
			{	
				try{
						if((m!=my_vec.size())||(n!=my_vec[0].size()))
						{
							throw "Wrong Matrix dimension initialized \n";
						}
					}catch (const char* msg)
					{
						std::cerr<< msg<<'\n';
						exit(0);
					}

				for(size_t i=0; i<my_vec.size(); ++i)
					for(size_t j=0; j<my_vec[0].size(); ++j)
						ElementAt(i,j) = my_vec[i][j];
			}


			// Transpose of Matrix
			/**
			 * @brief Take an object of type Matrix and returns its Transpose.
			 * @return Given input Matrix A, the Transpose of A is returned.
			 */
			Matrix<T,n,m> transpose()
			{
				Matrix<T,n,m> result;
				for(size_t i=0;i<m;++i)
				{
					for(size_t j=0;j<n;++j)
					{
						result.ElementAt(j,i)=ElementAt(i,j);
					}

				}
				return result;

			}

			// Matrix Multiplication without Malloc and time complexity: O(n^3)
			/**
			 * @brief Matrix multiplication using overloaded * operator. Takes 2 Matrices of size m x n and p x k. Checks if their inner dimensions
			 * match (i.e. n=p). If n=p then A and B is multiplied and a resultant Matrix of size m x k is returned.
			 * @tparam k = No of cols of Matrix B
			 * @tparam p = No of rows of Matrix B
			 * @param A = Matrix A
			 * @param B = Matrix B
			 * @return
			 *     Resultant Matrix Product of A and B i.e. A*B
			 */
			template<size_t k, size_t p>
			friend Matrix<T,m,k> operator*(const Matrix<T,m,n> &A, const Matrix<T,p,k> &B)
			{	
				try{ // Throw exception if Matrix inner dimensions don't match.
					if(n!=p)
					{
						throw "Matrix Inner Dimensions don't match can't multiply!!! \n";
					}
				}
				catch (const char* msg)
				{
					std::cerr<< msg<<'\n';
					exit(0);
				}

				Matrix<T,m,k> result;

				for (size_t i_m = 0; i_m < m; ++i_m) {
					for (size_t i_k = 0; i_k < k; ++i_k) {

						for (size_t i_n = 0; i_n < n; ++i_n) {
						result.ElementAt(i_m,i_k) += A.ElementAt(i_m,i_n) * B.ElementAt(i_n,i_k);
						}
					}
				}
					return result;
			}

			// Equal to operator Overload
			/**
			 * @brief Equal to operator overloaded to copy one matrix into another.
			 */
			Matrix& operator=(const Matrix& rhs) {
				if( this != &rhs )
					for(size_t i=0; i<m; ++i)
					for(size_t j=0; j<n; ++j)
						ElementAt(i,j) = rhs.ElementAt(i,j);
				return *this;
			}


			/**
			 * @brief Function to read value from the (i,j)th position of the Matrix
			 * @param i = row index
			 * @param j = column index
			 * @return
			 */
			const T& ElementAt(size_t i, size_t j) const
					{ return array[i][j]; }

			/**
			 * @brief Function to write value to the (i,j)th position of the Matrix
			 * @param i
			 * @param j
			 * @return
			 */
			T& ElementAt(size_t i, size_t j)
				{ return array[i][j]; }

			// Ofstream operator Overloaded
			/**
			 *
			 * @brief Operator overloaded to output/print an object of type Matrix.
			 */
			friend  std::ostream& operator<<(std::ostream& os, const Matrix& rhs)
			{
				for(size_t i=0; i<m; ++i)
					{
						for(size_t j=0; j<n; ++j)
							{os<<rhs.ElementAt(i,j)<<" ";}
						os<<'\n';
					}
				return os;
			}


		}; // Matrix Template Class Ends here !!!
//=====================================================================================================================================

		// CSV File storing
		/**
		 * @brief Function template to Store csv file at a given destination file. This function is internally called by matmul and Transpose 
		 * function (with Data2:= int, float etc) to store the Resultant BigMatrix from the memory to a CSV file.
		 * @tparam Data2
		 * @param C = A Pointer pointing to the 2D BigMatrix in the memory
		 * @param m_1 = No. of Rows of the Resultant BigMatrix
		 * @param n_2 = No. of Columns of the Resultant BigMatrix
		 * @param path = "path to destination csv file"
		 */
		template<typename Data2>
				void store_csv(Data2 ** C, int m_1, int n_2, std::string path)
					{
						std::ofstream file;
						file.open(path);

						for(int i=0;i<m_1;i++)
						{
							for(int j=0;j<n_2;j++)
							{
								file<<C[i][j];
								if(j<(n_2)-1)
								{
									file<<",";
								}
								else
								{
									file<<"\n";
								}
							}
						}
						file.close();

					}

		// Template to convert variable type from string to int,float, double or any other Datatype
		/**
		 * @brief Function template to convert variable type from string to int,float, double or any other Datatype spcified by My_data.
		 * @tparam My_data = Datatype into which we want to convert the string inputs parsed from CSV files.
		 * @param str = String input from the Csv file.
		 * @return Returns Converted number from string to My_data.
		 */
		template<typename My_data> My_data convert_to(const std::string &str)
			{
				std::istringstream ss(str); 

				My_data num;

				ss>>num;
				return num;
			}


		/**
		 * @brief This is the Class for handling Large Matrices. It takes in large Matrices stored as comma-separated values (CSV) files and perform both Multiplication 
		 * (Strassan's Algorithm) and transpose. It contains all the important functions namely ,matmul function, StrassanMultiply function and other helper functions 
		 * that are needed for smooth functioning of the library. This class also contains blocks of code that are gated by the SET_LEAF_SIZE flag, for example the 
		 * set_LEAF_SIZE() function and the set_configerd_Leaf_size() function. When matrix.h is compiled with the SET_LEAF_SIZE flag raised the set_LEAF_SIZE() function is active
		 * and set_configerd_Leaf_size() function is inactive. And the vice-versa happens when matrix.h is compiled without the SET_LEAF_SIZE flag.
		 * 
		 * @tparam Data1 = Datatype of the BigMatrix. Eg. int, float, double etc.
		 */
		// BIG MATRIX Multiplication and Transpose
		template<typename Data1>
		class BigMatrix
		{
			int LEAF_SIZE; // Private variable LEAF_SIZE 
			/**
			 * \privatesection
			 */
			private:

			/**
			 * @brief Function to dynamically allocate/initialize an n x n matrix in the memory.
			 * @param n = No. of rows and cols of the BigMatrix.
			 * @return Returns a pointer pointing to a memory location containing 0 matrix of size n x n.
			 *
			 */

			Data1** Init_matrix(int n)
			{   // Calloc chunk of Memory

				Data1** M;
				M=(Data1 **)calloc(n,sizeof(Data1*)); 
				for(int i=0;i<n;i++)
				{
					M[i]=(Data1*)calloc(n,sizeof(Data1));
				}
				return M;
			}

			/**
			 * @brief Function to Add 2 square Matrices of size n.
			 * @param M1 = Pointer pointing to BigMatrix M1 loaded into memory  
			 * @param M2 = Pointer pointing to BigMatrix M2 loaded into memory 
			 * @param n  = Size of the Matrices
			 * @return Returns a pointer pointing to a memory location containing the sum of M1 and M2
			 */
			// Matrix ADD ===================
			Data1** add(Data1** M1, Data1** M2, int n)
			{
				Data1** temp = Init_matrix(n);
			    for(int i=0; i<n; i++)
			        for(int j=0; j<n; j++)
			            temp[i][j] = M1[i][j] + M2[i][j];
			    return temp;
			}

			/**
			 * @brief Function to Subtract 2 square Matrices of size n.
			 * @param M1 = Pointer pointing to BigMatrix M1 loaded into memory 
			 * @param M2 = Pointer pointing to BigMatrix M2 loaded into memory 
			 * @param n  = Size of the Matrices
			 * @return Returns a pointer pointing to a memory location containing the difference of M1 and M2
			 */
			// Matrix SUBTRACT ===============
			Data1** sub(Data1** M1, Data1** M2, int n)
			{
				Data1** temp = Init_matrix(n);
				for(int i=0; i<n; i++)
					for(int j=0; j<n; j++)
						temp[i][j] = M1[i][j] - M2[i][j];
				return temp;
			}

			/**
			 * @brief The main Strassen's Algorithm function implemented using recursion. Takes in square Matrices A and B.
			 * @param A = BigMatrix A
			 * @param B = BigMatrix B
			 * @param n = Size of both A and B
			 * @return Returns a square matrix i.e. the Multiplication result of A and B.
			 * 
			 * The LEAF_SIZE is set by the MATOPS::BigMatrix<Data1>::set_configerd_Leaf_size() function from witin the MATOPS::BigMatrix<Data1>::matmul() function. The input Matrices 
			 * A and B are both broken down into 4 blocks, these matrices are used to calculate the 7 Strassen's coeffcient matrices. In order to calculate the Strassen's Coefficent
			 * the StrassenMultiply function is recurssively called. Once the matrix sizes becomes equal to or less than LEAF_SIZE, we hit the base condition and perform the Matrix 
			 * multiplication using the O(n^3) solution. Finally all the callocated memory (allocated by Init_matrix()) is freed up.
			 * 
			 * 
			 */
			Data1** StrassenMultiply(Data1** A, Data1** B, int n)
			{   
				/* Naive Strassan's Algorithm (more time consuming)
				  if(n==1)
				{
					Data1** C=Init_matrix(1);
					C[0][0]=A[0][0]*B[0][0];
					return C;
				}*/

				// Once array size of LEAF_SIZE x LEAF_SIZE or lesser is reached we switch to the O(n^3) Matrix Multiplication solution, since after this 
				// stage the recursion calls become a burden to the whole algorithm and we end up getting high execution time. The LEAF_SIZE is set by the
				// MATOPS::BigMatrix<Data1>::set_configerd_Leaf_size() function from witin the MATOPS::BigMatrix<Data1>::matmul() function.
				if(n<=LEAF_SIZE)
				{
					Data1** C=Init_matrix(n);
					for(int i=0;i<n;i++)
					{
						for(int j=0;j<n;j++)
						{
							for(int k=0;k<n;k++)
							{
								C[i][j]+=A[i][k]*B[k][j];
							}
						}
					}
					return C;
				}

				Data1** C = Init_matrix(n); // Initialize an nxn matrix to store 
				int k = n/2;

				// Initialize the Block Matrices
				Data1** A11 = Init_matrix(k);
				Data1** A12 = Init_matrix(k);
				Data1** A21 = Init_matrix(k);
				Data1** A22 = Init_matrix(k);
				Data1** B11 = Init_matrix(k);
				Data1** B12 = Init_matrix(k);
				Data1** B21 = Init_matrix(k);
				Data1** B22 = Init_matrix(k);

				// Build the block Matrices
				for(int i=0;i<k;i++)
				{
					for(int j=0;j<k;j++)
					{
						A11[i][j] = A[i][j];
						A12[i][j] = A[i][k+j];
						A21[i][j] = A[k+i][j];
						A22[i][j] = A[k+i][k+j];
						B11[i][j] = B[i][j];
						B12[i][j] = B[i][k+j];
						B21[i][j] = B[k+i][j];
						B22[i][j] = B[k+i][k+j];
					}
				}
				// Determine the Strassen's Coefficients
				Data1** TEMP_B12_B22 = sub(B12, B22, k);
				Data1** TEMP_A11_A12 = add(A11, A12, k);
				Data1** TEMP_A21_A22 = add(A21, A22, k);
				Data1** TEMP_B21_B11 = sub(B21, B11, k);


				Data1** P1 = StrassenMultiply(A11, TEMP_B12_B22, k);
				Data1** P2 = StrassenMultiply(TEMP_A11_A12, B22, k);
				Data1** P3 = StrassenMultiply(TEMP_A21_A22, B11, k);
				Data1** P4 = StrassenMultiply(A22, TEMP_B21_B11, k);

				Data1** TEMP_A11_A22 = add(A11, A22, k);
				Data1** TEMP_B11_B22 = add(B11, B22, k);
				Data1** TEMP_A12_A22 = sub(A12, A22, k);
				Data1** TEMP_B21_B22 = add(B21, B22, k);
				Data1** TEMP_A11_A21 = sub(A11, A21, k);
				Data1** TEMP_B11_B12 = add(B11, B12, k);

				Data1** P5 = StrassenMultiply(TEMP_A11_A22, TEMP_B11_B22, k);
				Data1** P6 = StrassenMultiply(TEMP_A12_A22, TEMP_B21_B22, k);
				Data1** P7 = StrassenMultiply(TEMP_A11_A21, TEMP_B11_B12, k);

				Data1** TEMP_P5_P4 = add(P5, P4, k);
				Data1** TEMP_P5_P4_P6 = add(TEMP_P5_P4, P6, k);
				Data1** TEMP_P5_P1 = add(P5, P1, k);
				Data1** TEMP_P5_P1_P3 = sub(TEMP_P5_P1, P3, k);


				Data1** C11 = sub(TEMP_P5_P4_P6, P2, k);
				Data1** C12 = add(P1, P2, k);
				Data1** C21 = add(P3, P4, k);
				Data1** C22 = sub(TEMP_P5_P1_P3, P7, k);

				// Building the returning C Matrix

				for(int i=0; i<k; i++)
				{
					for(int j=0; j<k; j++)
					{
						C[i][j] = C11[i][j];
						C[i][j+k] = C12[i][j];
						C[k+i][j] = C21[i][j];
						C[k+i][k+j] = C22[i][j];
					}
				}

				// Free up all calloced memory.
				for(int i=0; i<k; i++) {
						free(TEMP_B12_B22[i]);
						free(TEMP_A11_A12[i]);
						free(TEMP_A21_A22[i]);
						free(TEMP_B21_B11[i]);

						free(TEMP_A11_A22[i]);
						free(TEMP_B11_B22[i]);
						free(TEMP_A12_A22[i]);
						free(TEMP_B21_B22[i]);
						free(TEMP_A11_A21[i]);
						free(TEMP_B11_B12[i]);

						free(TEMP_P5_P4[i]);
						free(TEMP_P5_P4_P6[i]);
						free(TEMP_P5_P1[i]);
						free(TEMP_P5_P1_P3[i]);

				        free(A11[i]);
				        free(A12[i]);
				        free(A21[i]);
				        free(A22[i]);
				        free(B11[i]);
				        free(B12[i]);
				        free(B21[i]);
				        free(B22[i]);
				        free(P1[i]);
				        free(P2[i]);
				        free(P3[i]);
				        free(P4[i]);
				        free(P5[i]);
				        free(P6[i]);
				        free(P7[i]);
				        free(C11[i]);
				        free(C12[i]);
				        free(C21[i]);
				        free(C22[i]);
				    }

					free(TEMP_B12_B22);
					free(TEMP_A11_A12);
					free(TEMP_A21_A22);
					free(TEMP_B21_B11);

					free(TEMP_A11_A22);
					free(TEMP_B11_B22);
					free(TEMP_A12_A22);
					free(TEMP_B21_B22);
					free(TEMP_A11_A21);
					free(TEMP_B11_B12);

					free(TEMP_P5_P4);
					free(TEMP_P5_P4_P6);
					free(TEMP_P5_P1);
					free(TEMP_P5_P1_P3);

					free(A11);
				    free(A12);
				    free(A21);
				    free(A22);
				    free(B11);
				    free(B12);
				    free(B21);
				    free(B22);
				    free(P1);
				    free(P2);
				    free(P3);
				    free(P4);
				    free(P5);
				    free(P6);
				    free(P7);
				    free(C11);
				    free(C12);
				    free(C21);
				    free(C22);

				    return C;
			}

			// Print Matrix (internal printing)
			/**
			 * @brief This function is called from within the MATOPS::BigMatrix<Data1>::matmul function when print == True
			 * @param C Pointer to the memory where the array is stored.
			 * @param m No of rows of the Matrix
			 * @param n No of Columns of the Matrix
			 */
			void print_Mat(Data1** C, int m, int n)
			{
				for(int i=0;i<m;i++)
				{
					for(int j=0;j<n;j++)
					{
						std::cout<<C[i][j]<<" ";
					}
					std::cout<<'\n';
				}
			}

		// LOAD from CSV file Template
			/**
			 * @brief Function to load CSV file. This function is internally called by  MATOPS::BigMatrix<Data1>::matmul  and  MATOPS::BigMatrix< Data1 >::Transpose 
			 * to load the BigMatrix's to be multiplied or Transposed. It throws an error if path is invalid or CSV doesn't exist.
			 * @param path= "path to CSV file i.e. to be loaded"
			 * @return A pointer to the Matrix loaded in memory.
			 */
		std::vector<std::vector<Data1>> load_CSV(const std::string &path)
		{
		    std::ifstream indata;
		    indata.open(path);

		    if(indata.fail()) // Check if File exists
		    {
		    	std::cerr<<"File path: '"<<path<<"' doesn't exist\n";
		    	exit(0);
		    }

		    std::vector<std::vector<Data1>> dataList;
		    std::string line = "";

		    while(getline(indata,line))
		    {
		        std::stringstream lineStream(line);
		        std::string cell;
		        std::vector<Data1> temp;
		        while (std::getline(lineStream,cell,','))
		        {
		            temp.push_back(convert_to<Data1>(cell)); // convert from string to Data1 and store it in an 2D array.
		        }
		        dataList.push_back(temp);

		    }
		    indata.close(); // Close file
		    return dataList; // Return the 2D vector 
		}

		/**
		 * @brief Function to print a Matrix from a .csv file.
		 * @param path = "path to .csv i.e. to be printed"
		 */
			public:
		void Mat_print(std::string path)
		{
			std::vector<std::vector<Data1>> MAT= load_CSV(path);

			for(std::vector<Data1> a: MAT)
			{
				for(Data1 i: a)
				{
					std::cout<< i <<" ";
				}
				std::cout<<'\n';
			}
		}
		
		/** 
		 * @brief This Function sets the LEAF_SIZE i.e. the array size at which we shift from Strassan's Algo to normal O(n^3) solution, this prevents the 
		 * StrassenMultiply recursion function from down to a leaf size/Matrix size of 1. Once we reach a square matrix array of size LEAF_SIZE x LEAF_SIZE 
		 * or lesser, we perform the multiplication using the naive O(n^3) time complexity solution. 
		 * 
		 * 		A very high value of LEAF_SIZE leads to lesser recursion calls but ends up giving more weightage to the O(n^3) solution, thus suffer high 
		 * 		execution time. 
		 * 
		 * 		On the other hand a very low LEAF_SIZE value leads to higher number of resursion calls and gives lesser weightage to the O(n^3) solution, 
		 * 		which again leads to high execution time. 
		 * 
		 * Hence an optimal LEAF_SIZE value has to be found that gives the minimum execution time by finding a trade off between the O(n^3) solution and recurssion 
		 * calls. This indirectly implies that the value of LEAF_SIZE vary from one machine to another, thus we need to experimentally find out this value for each 
		 * machine and configure the matrix.h library accordingly. This experimentation is done by the configure_lib.cpp, which raises the SET_LEAF_SIZE flag 
		 * (thus activating the set_LEAF_SIZE() function) during execution, as a result of which the "matrix.h" library is called (in its configuration mode) by 
		 * configure_lib.cpp. This allows configure_lib.cpp to manipulate the LEAF_SIZE (private variable) of the matrix.h file. Hence configure.cpp can test the 
		 * hardware for different values of LEAF_SIZE and pick its optimal (i.e. the value that gives the lowest execution time) value and finally store the optimal 
		 * value in the configure.txt file. 
		 * 
		 */
		#ifdef SET_LEAF_SIZE 
		void set_LEAF_SIZE(int leaf_size)
		{
			LEAF_SIZE=leaf_size;
		}
		#else
		/**
		 * @brief When matrix.h is normally called i.e. without any SET_LEAF_SIZE flag, set_configerd_Leaf_size() function gets activated (set_LEAFT_SIZE() function
		 * gets deactivated). The set_configerd_Leaf_size() function searches for the configure.txt file (generated earlier by configure_lib.cpp during the configuration
		 * process) and sets the optimal value of LEAF_SIZE. This function is called by the  MATOPS::BigMatrix<Data1>::matmul before starting the multiplication process.
		 * 
		 */
		void set_configerd_Leaf_size()
		{
			std::ifstream indata;
			indata.open("configure.txt");
			std::string str="";
			getline(indata,str);
			indata.close();
			LEAF_SIZE=std::stoi(str);
		}
		#endif

		// Matrix Multiplication from CSV files
		/**
		 * @brief This is the BigMatrix multiplication Function that multiplies two matrices A and B stored in A.csv and B.csv respectively and store the result in C.csv file.
		 * Before beginning the multiplication process it calls the MATOPS::BigMatrix<Data1>::set_configerd_Leaf_size() function to parses the configure.txt (generated by 
		 * configure_lib.cpp during the configuration process) and sets the optimal LEAF_SIZE value.
		 * @param file_1 = "path to A.csv"
		 * @param file_2 = "path to B.csv"
		 * @param path = path to a store file (no need to predefine C.csv file in the directory, it gets generated automatically.)
		 * @param print = True, To see all the Matrices i.e. A,B and C in the output terminal/stdio.
		 * 
		 * Overall Working: When matmul is called, it first sets the the optimal LEAF_SIZE value. It then loads the two csv files from "path to A.csv" and "path to B.csv"
		 * directories into two 2D vectors namely MAT_1 and MAT_2 of type Data1 using MATOPS::BigMatrix<Data1>::load_CSV function. The dimensions of both the matrices are determined 
		 * from MAT_1 and MAT_2 say m_1,n_1 ad m_2,n_2 respectively. If the inner dimensions of both MAT_1 and MAT_2 don't match an error is thrown and the program is exited. If the 
		 * inner dimensions match then we proceed for Multiplication. Before calling the MATOPS::BigMatrix<Data1>::StrassenMultiply fuction, we pad the matrices with zeros to make both
		 * MAT_1 and MAT_2 square matrices of equal dimension, dim_n. Where dim_n is a power of 2 i.e. greater than or equal to max(m_1,n_1,n_2) or max(m_1,m_2,n_2) (since n_1=m_2). We 
		 * callocate (by calling MATOPS::BigMatrix<Data1>::Init_matrix(dim_n) two chunk of memory of size dim_n x dim_n pointed by pointers A and B. Finally  we build the Zero padded square
		 * Matrices by copying the contents from from MAT_1 and MAT_2 into the memory (pointed by A and B) respectively. These Memory addresses and dim_n are then passed on to the 
		 * MATOPS::BigMatrix<Data1>::StrassenMultiply function to evaluate the product of A and B. The MATOPS::BigMatrix<Data1>::StrassenMultiply() func returns a pointer pointing 
		 * to a location in the memory where the answer is stored. This memory address is then passed to the MATOPS::BigMatrix<Data1>::store_csv() along with the resultant matrix 
		 * dimension (i.e. m_1 x n_2) and the storage destination path to store the final result in a csv file.
		 * 
		 * Finally all the callocated memories are freed up using the free command.
		 * 	
		 */
		void matmul(std::string file_1, std::string file_2, std::string path, bool print=false)

				{   
					
					#ifndef SET_LEAF_SIZE 
						set_configerd_Leaf_size(); // Set the optimal LEAF_SIZE by parsing the configuration file genrated by configure_lib.cpp.
					#endif
					// std::cout<<"Current LEAF_SIZE value: "<<LEAF_SIZE<<'\n'; // Just a check to see what LEAF_SIZE value is being used
					
					// Parse the CSV files and get the Matrices to be multiplied

					std::vector<std::vector<Data1>> MAT_1= load_CSV(file_1);
					std::vector<std::vector<Data1>> MAT_2= load_CSV(file_2);

					// Get the dimensions of both the Matrices.
					int m_1=MAT_1.size(), n_1=MAT_1[0].size();  // Matrix 1 M,N
					int m_2=MAT_2.size(), n_2=MAT_2[0].size(); // Matrix 2 M,N

					try{
						if(n_1 != m_2) // Check if inner dimensions of the Matrices Match. If not then Throw error.
						{
							throw "Matrix Inner Dimensions don't match !!! \n";
						}
					  }catch (const char* msg)
						{
							std::cerr<<msg<<'\n';
							exit(0);
						}

						int max_n= std::max(std::max(m_1,n_1),n_2); // Find the max of all the Matrix dimensions, to find the next highest power of 2.
						int dim_n=1;

						// Find the next highest power of 2 using left shift operator (dim_n = Next highest power of 2).
						// This will be used to pad zeros to both matrices A and B, and ultimately given as input to StrassenMultiply() function.
						while(dim_n<max_n)
						{
							dim_n=dim_n<<1;
						}

						// Initialize 3 pointers to point at Matrices A and B, and to store the Result of AxB into C.
						Data1 ** A;
						Data1 ** B;
						Data1 ** C;

						A=Init_matrix(dim_n); // Allocate the memory for Matrix A of size dim_n
						B=Init_matrix(dim_n); // Allocate the memory for Matrix B of size dim_n

						// Build the Zero padded square Matrices A and B by copying contents from from MAT_1 and MAT_2 into A and B respectively.
							for(int k=0;k<m_1;k++)
							{
								for(int l=0;l<n_1;l++)
								{
									A[k][l]= MAT_1[k][l];
								}
							}

							for(int k=0;k<m_2;k++)
							{
								for(int l=0;l<n_2;l++)
								{
									B[k][l]= MAT_2[k][l];

								}

							}

						//Call Strassen's Algorithm function to get A x B and store in C.
							C=StrassenMultiply(A, B, dim_n);

						if(print==true) // if print is true then print A, B and the result A.
							{
									std::cout<<"A: \n";
									print_Mat(A, m_1, n_1); //Call the print_Mat function to print the Matrix

									std::cout<<"\nB: \n";
									print_Mat(B, m_2, n_2); //Call the print_Mat function to print the Matrix

									std::cout<<"\nANSWER: \n"; //Call the print_Mat function to print the Matrix
									print_Mat(C, m_1, n_2);

							}

						// Store the Result C into a CSV file, whose location is given by "path"
						store_csv<Data1>(C, m_1,n_2,path);

						// Free The memory before quitting
						for(int i=0;i<dim_n;i++)
						{
							free(A[i]);
							free(B[i]);
							free(C[i]);
						}

						free(A);
						free(B);
						free(C);


				} // matmul function ends here

		// Matrix Transpose function begins here

		/**
		 *
		 * @brief This is a function to find the Transpose of a BigMatrix and stores it in a csv file.
		 * @param path = "path/to/A.csv"
		 * @param str_path = path to store the Transpose of BigMatrix A.
		 *
		 */
		void Transpose(std::string path, std::string str_path)
			{
			    std::vector<std::vector<Data1>> MAT= load_CSV(path); // Load the Matrix from CSV file

			    Data1** A= (Data1 **)calloc(MAT[0].size(),sizeof(Data1*));

			    for(int i=0;i<MAT[0].size();i++)
				{
					A[i]=(Data1*)calloc(MAT.size(),sizeof(Data1));
				}

				for(int i=0;i<MAT.size();i++)
				{
					for(int j=0;j<MAT[0].size();j++)
					{
						A[j][i]=MAT[i][j];
					}
				}

				store_csv<Data1>(A,MAT[0].size(),MAT.size(),str_path);
				for(int i=0;i<MAT[0].size();i++)
				{
					free(A[i]);
				}
				free(A);
			}

		/**
		 * @brief This is a function to find the Transpose of a BigMatrix and stores it in the same csv file (In-palce transpose).
		 * @param path = "path/to/A.csv"
		 */
		void Transpose(std::string path)
					{
					    std::vector<std::vector<Data1>> MAT= load_CSV(path); // Load the Matrix from CSV file

					    Data1** A= (Data1 **)calloc(MAT[0].size(),sizeof(Data1*));

					    for(int i=0;i<MAT[0].size();i++)
						{
							A[i]=(Data1*)calloc(MAT.size(),sizeof(Data1));
						}

						for(int i=0;i<MAT.size();i++)
						{
							for(int j=0;j<MAT[0].size();j++)
							{
								A[j][i]=MAT[i][j];
							}
						}

						store_csv<Data1>(A,MAT[0].size(),MAT.size(),path);
						store_csv<Data1>(A,MAT[0].size(),MAT.size(),path);

						for(int i=0;i<MAT[0].size();i++)
						{
							free(A[i]);
						}
						free(A);

					}

			};


}  // MATOPS namespace ends here

#endif /* MATRIX_H_ */
