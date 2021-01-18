/*
 * matrix.h
 *
 *  Created on: Jan 9, 2021
 *      Author: shiladitya
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

		template<typename T, size_t m, size_t n>
		class Matrix{

			T **array;

			public:

			virtual ~Matrix() {}

			size_t cols()
			{
				return n; //m_col;
			}

			size_t rows()
			{
				return m; //m_row;
			}


			// Default Matrix Initialization
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
			Matrix( std::vector<std::vector<T>>& A):Matrix()
			{

				for(size_t i=0; i<A.size(); ++i)
					for(size_t j=0; j<A[0].size(); ++j)
						ElementAt(i,j) = A[i][j];
			}


			// Transpose of Matrix
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

			template<size_t k, size_t k1>
			friend Matrix<T,m,k> operator*(const Matrix<T,m,n> &A, const Matrix<T,k1,k> &B)
			{
				if(n==k1)
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
			Matrix& operator=(const Matrix& rhs) {
				if( this != &rhs )
					for(size_t i=0; i<m; ++i)
					for(size_t j=0; j<n; ++j)
						ElementAt(i,j) = rhs.ElementAt(i,j);
				return *this;
			}

			const T& ElementAt(size_t i, size_t j) const
				{ return array[i][j]; }

			T& ElementAt(size_t i, size_t j)
				{ return array[i][j]; }

			// Ofstream operator Overloaded
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
		template<typename My_data> My_data convert_to(const std::string &str)
			{
				std::istringstream ss(str);

				My_data num;

				ss>>num;
				return num;
			}

		// BIG MATRIX Multiplication and Transpose
		template<typename Data1>
		class BigMatrix
		{

			public:
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

			// Print Matrix
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



		// Matrix Multiplication from CSV files
//		template<typename Data>
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

							for(int i=m_1;i<dim_n;i++)
							{
								free(C[i]);
							}



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

							// Free The memory before quitting
							free(A);
							free(B);

							return C;
					}

				} // matmul function ends here

			};

//		template<typename Data_T>
//		Data_T** Transpose(std::string path)



}  // MATOPS namespace ends here

#endif /* MATRIX_H_ */
