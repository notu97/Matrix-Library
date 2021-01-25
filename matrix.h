/**
 * @file   matrix.h
 *
 * @date   Jan 25, 2021
 * @author Shiladitya Biswas
 *
 *
 * This is a simple Matrix operation library, to Multiply 2 Matrices and find the transpose of a Matrix. The library is divided into two parts, one for small Matrices (i.e. Matrix multiplication is performed with O(^3) time complexity) and another for large Matrices where Stressan's Algorithm (Time Complexity: O(n^2.8)) is used to Multiply two Matrices.
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



namespace MATOPS
{

		/**
		 * This class is for matrices of smaller size. The user can define a Matrix A of size m x n of Datatype T as follows: MATOPS::Matrix<T,m,n> A.
		 * @tparam T = DataType of the Matrix. Eg. int, float, double etc.
		 * @tparam m = No. of Rows of the Matrix
		 * @tparam n = No. of Cols of the Matrix
		 */
		template<typename T, size_t m, size_t n>
		class Matrix{


			T **array;

			/**
			 * Given Matrix A
			 * @param i
			 * @param j
			 * @return Returns the (i,j)th element of Matrix A.
			 */
			const T& ElementAt(size_t i, size_t j) const
							{ return array[i][j]; }

				T& ElementAt(size_t i, size_t j)
					{ return array[i][j]; }

			public:

			virtual ~Matrix() {}

			/**
			 *
			 * @return Returns the number of columns in the Matrix
			 */
			size_t cols()
			{
				return n; //m_col;
			}

			/**
			 *
			 * @return Returns the number of Rows in the Matrix.
			 */
			size_t rows()
			{
				return m; //m_row;
			}


			// Default Matrix Initialization
			/**
			 * Default constructor to initialize the matrix with zeros.
			 */
			Matrix()
			{
				unsigned int i;
				array=(T **)calloc(m,sizeof(T*));
				for(i=0;i<m;i++)
				{
					array[i]=(T*)calloc(n,sizeof(T));
				}
			}

			// Initialize Matrix from Initializer_list
			/**
			 * Overloaded constructor the initialize the Matrix from a 2D Initializer list.
			 * @param my_list
			 */
			Matrix(std::initializer_list<std::initializer_list<T>> my_list):Matrix()
				{
					int row_n=0;
					for(std::initializer_list<T> i:my_list)
					{   int col_n=0;
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
			 * Overloaded constructor the initialize the Matrix from a 2D Vector.
			 * @param A
			 */
			Matrix( std::vector<std::vector<T>>& A):Matrix()
			{

				for(size_t i=0; i<A.size(); ++i)
					for(size_t j=0; j<A[0].size(); ++j)
						ElementAt(i,j) = A[i][j];
			}


			// Transpose of Matrix
			/**
			 * Take an object of type Matrix and returns its Transpose.
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
			 * Matrix multiplication using overloaded * operator. Takes 2 Matrices of size m x n and p x k. Checks if their inner dimensions match (i.e. n=p). If n=p then A and B is multiplied and a resultant Matrix of size m x k is returned.
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
				if(n==p)
				{
					Matrix<T,m,k> result;

					for (size_t i_m = 0; i_m != m; ++i_m) {
						for (size_t i_k = 0; i_k != k; ++i_k) {

							for (size_t i_n = 0; i_n != m; ++i_n) {
							result.ElementAt(i_m,i_k) += A.ElementAt(i_m,i_n) * B.ElementAt(i_n,i_k);
							}
						}
					}
					return result;
				}
				else
				{
					std::cerr<<"Matrix Inner Dimensions don't match !!! \n";
					exit(0);
				}

			}

			// Equal to operator Overload
			/**
			 * Equal to operator overloaded to copy one matrix into another.
			 */
			Matrix& operator=(const Matrix& rhs) {
				if( this != &rhs )
					for(size_t i=0; i<m; ++i)
					for(size_t j=0; j<n; ++j)
						ElementAt(i,j) = rhs.ElementAt(i,j);
				return *this;
			}

//			const T& ElementAt(size_t i, size_t j) const
//				{ return array[i][j]; }
//
//			T& ElementAt(size_t i, size_t j)
//				{ return array[i][j]; }

			// Ofstream operator Overloaded
			/**
			 *
			 * Operator overloaded to output/print an object of type Matrix.
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
		 * Function to Store csv file at a given destination path. This function is internally called by matmul and Transpose function to store the Resultant Matrix obtained.
		 * @tparam Data2
		 * @param C = A Pointer ponting to the 2D Matrix in the memory
		 * @param m_1 = No. of Rows of the Matrix
		 * @param n_2 = No. of Columns of the Matrix
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

					}

		// Template to convert variable type from string to int,float, double or any other Datatype
		/**
		 * Template to convert variable type from string to int,float, double or any other Datatype
		 * @tparam My_data = Datatype into which we want to convert the string input from CSV files.
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
 * This is the Class for handling Large Matrices. It takes in large Matrices as comma-separated values (CSV) files and perform both Multiplication (Stressan's Algorithm) and transpose.
 * @tparam Data1 = Datatype of the BigMatrix. Eg. int, float, double etc.
 */
		// BIG MATRIX Multiplication and Transpose
		template<typename Data1>
		class BigMatrix
		{

			private:
			// Calloc chunk of Memory===============
			Data1** Init_matrix(int n)
			{  Data1** M;
				M=(Data1 **)calloc(n,sizeof(Data1*));
				for(int i=0;i<n;i++)
				{
					M[i]=(Data1*)calloc(n,sizeof(Data1));
				}
				return M;
			}

			// Matrix ADD ===================
			Data1** add(Data1** M1, Data1** M2, int n)
			{
				Data1** temp = Init_matrix(n);
			    for(int i=0; i<n; i++)
			        for(int j=0; j<n; j++)
			            temp[i][j] = M1[i][j] + M2[i][j];
			    return temp;
			}

			// Matrix SUBTRACT ===============
			Data1** sub(Data1** M1, Data1** M2, int n)
			{
				Data1** temp = Init_matrix(n);
				for(int i=0; i<n; i++)
					for(int j=0; j<n; j++)
						temp[i][j] = M1[i][j] - M2[i][j];
				return temp;
			}

			Data1** StrassenMultiply(Data1** A, Data1** B, int n)
			{
				if(n==1)
				{
					Data1** C=Init_matrix(1);
					C[0][0]=A[0][0]*B[0][0];
					return C;
				}

				Data1** C = Init_matrix(n);
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
				Data1** P1 = StrassenMultiply(A11, sub(B12, B22, k), k);
				Data1** P2 = StrassenMultiply(add(A11, A12, k), B22, k);
				Data1** P3 = StrassenMultiply(add(A21, A22, k), B11, k);
				Data1** P4 = StrassenMultiply(A22, sub(B21, B11, k), k);
				Data1** P5 = StrassenMultiply(add(A11, A22, k), add(B11, B22, k), k);
				Data1** P6 = StrassenMultiply(sub(A12, A22, k), add(B21, B22, k), k);
				Data1** P7 = StrassenMultiply(sub(A11, A21, k), add(B11, B12, k), k);

				Data1** C11 = sub(add(add(P5, P4, k), P6, k), P2, k);
				Data1** C12 = add(P1, P2, k);
				Data1** C21 = add(P3, P4, k);
				Data1** C22 = sub(sub(add(P5, P1, k), P3, k), P7, k);

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

				for(int i=0; i<k; i++) {
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
			 * This function is called from within the MATOPS::BigMatrix<Data1>::matmul function when print == True
			 * @param C
			 * @param m
			 * @param n
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


//		};

		// LOAD from CSV file Template
//		template<typename Datatype>
			/**
			 * Function to load CSV file. This function is internally called by  MATOPS::BigMatrix<Data1>::matmul  and  MATOPS::BigMatrix< Data1 >::Transpose to load the BigMatrix 's to be multiplied or Transposed.
			 * @param path= "path to CSV file i.e. to be loaded"
			 * @return
			 */
		std::vector<std::vector<Data1>> load_CSV(const std::string &path)
		{
		    std::ifstream indata;
		    indata.open(path);
		    std::vector<std::vector<Data1>> dataList;
		    std::string line = "";

		    while(getline(indata,line))
		    {
		        std::stringstream lineStream(line);
		        std::string cell;
		        std::vector<Data1> temp;
		        while (std::getline(lineStream,cell,','))
		        {
		            temp.push_back(convert_to<Data1>(cell));
		        }
		        dataList.push_back(temp);

		    }

		    return dataList;
		}

		/**
		 * Function to print a Matrix from a .csv file.
		 * @param path = "path to .csv to i.e. to be printed"
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

		// Matrix Multiplication from CSV files
//		template<typename Data>

		/**
		 * This is the BigMatrix multiplication Function. To multiply two matrices A and B stored in A.csv and B.csv respectively and store the result in C.csv file, do the following.\n
		 *
		 * @param file_1 = "path to A.csv"
		 * @param file_2 = "path to B.csv"
		 * @param path = path to a store file (no need to predefine C.csv file in the directory, it gets generated automatically.)
		 * @param print = True, To see all the Matrices i.e. A,B and C in the output terminal/stdio. \n
		 *
		 * @return
		 * 		Returns a pointer of type Data1** pointing to the C BigMatrix in the Memory. It can be used in the main program to access the (i,j) element of the BigMatrix C.
		 *
		 *	Define a BigMatrix object BigMatrix<DataType> MatObj, where DataType can be int, float, double, long etc.\n
		 *	Then call DataType** Result = MatObj.matmul("path/to/A.csv","path/to/B.csv","path/to/C.csv") from your program. The C.csv file generated file contains C=A*B. Result[i][j] accesses the (i,j)th element of BigMatrix C.
		 */
		Data1** matmul(std::string file_1, std::string file_2, std::string path, bool print=false)

				{
					std::vector<std::vector<Data1>> MAT_1= load_CSV(file_1);
					std::vector<std::vector<Data1>> MAT_2= load_CSV(file_2);

					int m_1=MAT_1.size(), n_1=MAT_1[0].size();  // Matrix 1 M,N

					int m_2=MAT_2.size(), n_2=MAT_2[0].size(); // Matrix 2 M,N

					if(n_1 != m_2)
					{
						std::cerr<<"Matrix Inner Dimensions don't match !!! \n";
						exit(0);
					}
					else
					{
						int max_n= std::max(std::max(m_1,n_1),n_2);
						int dim_n=1;

						// Find the next power of 2.
						while(dim_n<max_n)
						{
							dim_n=dim_n<<1;
						}

						Data1 ** A;
						Data1 ** B;
						Data1 ** C;
//						BigMatrix<Data> obj;

						A=Init_matrix(dim_n); // Allocate the memory for Matrix A
						B=Init_matrix(dim_n); // Allocate the memory for Matrix B

						// build the square Matrices;

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

//							Call Stressen's Algorithm function for A x B

							C=StrassenMultiply(A, B, dim_n);

					if(print==true)
						{
								std::cout<<"A: \n";
								print_Mat(A, m_1, n_1);

								std::cout<<"\nB: \n";
								print_Mat(B, m_2, n_2);

								std::cout<<"\nANSWER: \n";
								print_Mat(C, m_1, n_2);

						}

						store_csv<Data1>(C, m_1,n_2,path);


						Data1** M=(Data1 **)calloc(m_1,sizeof(Data1*));
						for(int i=0;i<m_1;i++)
						{
							M[i]=(Data1*)calloc(n_2,sizeof(Data1));
						}

						for(int i=0;i<m_1;i++)
						{
							for(int j=0;j<n_2;j++)
							{
								M[i][j]=C[i][j];
							}
						}

							// Free The memory before quitting
							free(A);
							free(B);
							free(C);

							return M;
					}

				} // matmul function ends here

		// Matrix Transpose function begins here

		/**
		 *
		 * This is a function to find the Transpose of a BigMatrix and stores it in a csv file.
		 * @param path = "path/to/A.csv"
		 * @param str_path = path to store the Transpose of BigMatrix A.
		 * @return
		 * 		Returns a pointer of type Data1** pointing to the Transpose of BigMatrix A in the Memory. It can be used in the main program to access the (i,j) element of the Transpose of BigMatrix A
		 *
		 */
		Data1** Transpose(std::string path, std::string str_path)
			{
			    std::vector<std::vector<Data1>> MAT= load_CSV(path);

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
				return A;
			}

			};


}  // MATOPS namespace ends here

#endif /* MATRIX_H_ */
