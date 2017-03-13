#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class Matrix{
private:
	 int rows;
	 int cols;
	 double **data;

	// public void add(int (*aa)[col],int (*bb)[col],int (*to)[col],int r,int c);
	// public void sub(int (*aa)[col],int (*bb)[col],int (*to)[col],int r,int c);
	// public void mul(int (*aa)[col],int (*bbt)[rows],int (*to)[col],int r,int c);
	// public void trans(int (*aa)[col],int (*tr)[rows],int r,int c);
	// public void concat(int (*aa)[col1], int (*bb)[col2], int r, int c);

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
	 //Matrix& random(const int row, const int col,const int  minRange,  const int maxRange) ;
	 

	 static Matrix& random(const int row, const int col,const int  minRange,  const int maxRange) ;
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

};

