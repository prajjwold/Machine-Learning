#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class Matrix{
private:
	 int rows;
	 int cols;
	 double **data;

	public:
	 Matrix(int rows, int cols);
	 Matrix(){};
	 Matrix( const Matrix& other);
	 ~Matrix();
	 int getNumRows() const {return rows;}
	 int getNumCols() const {return cols;}
	 void print();
	 double** getData() const {return data;}
	 void dimension() const { cout<<"["<<rows<<"*"<<cols<<"]"<<endl;}
	 Matrix& transpose();
	 Matrix& concat(const Matrix &b,int axis=0) const;
	 Matrix& subset(int rows, int cols);

	 //randomize the Matrix
	 static Matrix randomizeRows(const Matrix& in);
	 //Generate ordering for Matrix shuffling of Rows
	 static int* genOrdering(int rows);
	 //randomize the Matrix based on the ordering specified
	 static Matrix randomizeRows(const Matrix& in,int* ordering); 
	 //Matrix& random(const int row, const int col,const int  minRange,  const int maxRange) ;
	 

	 static Matrix& random(const int row, const int col,const double  minRange,  const double maxRange) ;
	 static Matrix& random(const int row,const int col);
	 static Matrix& ones(const int rows,const int cols);
	 static Matrix& zeros(const int rows,const int cols);

	 static Matrix add( Matrix a,  Matrix b);
	 static Matrix subtract(Matrix a, Matrix b);
	 static Matrix mult(Matrix a, Matrix b);
	 static Matrix transpose(Matrix a);
	 static Matrix inverse(Matrix a);
	 static Matrix copy(Matrix a);
	 static Matrix concat(Matrix a,Matrix b,int axis);


	 //Operator Overloading
	   Matrix& operator-();       // Unary - operator.
	   // Declare prefix and postfix increment operators.
	   Matrix& operator++();       // Prefix increment operator.
	   Matrix operator++(int);     // Postfix increment operator.

	   // Declare prefix and postfix decrement operators.
	   Matrix& operator--();       // Prefix decrement operator.
	   Matrix operator--(int);     // Postfix decrement operator.

	   Matrix &operator=( const Matrix & );  // Assignment Operator

	   Matrix& operator+( const Matrix &other ); //Binary + Operator
	   Matrix& operator-( const Matrix &other ); //Binary - Operator
	   Matrix& operator*( const Matrix &other ); //Binary * Operator
	   Matrix& operator+( const double val); //Binary + Operator 
	   Matrix& operator-( const double val ); //Binary - Operator
	   Matrix& operator*( const double val ); //Binary * Operator
	   Matrix& operator/( const double val ); //Binary / Operator

	   Matrix& mult( const Matrix &other ); //Elementwise + Operator
};

