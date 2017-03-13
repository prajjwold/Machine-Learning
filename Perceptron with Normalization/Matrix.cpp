#include "Matrix.h"
#include <stdio.h>
#include <string.h>
#include <iomanip>

Matrix::Matrix(int rows, int cols){
	this->rows=rows;
	this->cols=cols;
	data=new double*[rows];
	for(int i=0;i<rows;i++){
		data[i]=new double[cols];
	}
}
//copy constructor
Matrix::Matrix( const Matrix& other ):rows( other.rows ), cols( other.cols){
	data=new double*[rows];
	for(int i=0;i<other.rows;i++){
		data[i]=new double[other.cols];
	}
	for(int i=0;i<other.rows;i++){
		for(int j=0;j<other.cols;j++){
			data[i][j]=other.data[i][j];
		}
	}
	//cout<<"Copy Constructor Called"<<endl;
}

Matrix::~Matrix(){
	for(int i = 0; i < rows; i++) 
	{
    	delete [] data[i];
    	//data[i]=NULL;
	}
	delete [] data;
	// data =NULL;
	// this=NULL;
	//cout<<"Destructor Called"<<endl;
}

void  Matrix::print(){
	cout << std::setprecision(1) << std::fixed;
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			cout<<data[i][j]<<"\t";
		}
		cout<<endl;
	}
	//cout<<endl;
}

Matrix& Matrix::ones(const int rows,const int cols){
	Matrix* t=new Matrix(rows,cols);
	for(int i=0;i<t->getNumRows();i++){
		for(int j=0;j<t->getNumCols();j++){
			t->getData()[i][j]=1;
		}
	}
	return *t;
}
Matrix& Matrix::zeros(int rows,int cols){
	Matrix* t=new Matrix(rows,cols);
	for(int i=0;i<t->getNumRows();i++){
		for(int j=0;j<t->getNumCols();j++){
			t->getData()[i][j]=0;
		}
	}
	return *t;
}

Matrix& Matrix::transpose(){
	Matrix* t=new Matrix(getNumCols(),getNumRows());
	for(int i=0;i<t->getNumRows();i++){
		for(int j=0;j<t->getNumCols();j++){
			t->getData()[i][j]=getData()[j][i];
		}
	}
	return *t;
}

Matrix& Matrix::concat(const Matrix& b,int axis) const{
	if(axis==0){
		//concatenate b after the last row of a
		if(cols!=b.cols){
			cerr<<"Incompatible matrix dimension: ["<<rows<<"*"<<cols<<"]\t["<<b.rows<<"*"<<b.cols<<"]"<<endl;
			throw "Incompatible matrix dimension:";
		}
		Matrix *c=new Matrix(rows+b.rows,cols);
		//c.print();
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++){
				c->data[i][j]=data[i][j];
				//memcpy(&c.data[i][j],&data[i][j],sizeof(data[0]));
			}
		}
		for(int i=0;i<b.rows;i++){
			for(int j=0;j<cols;j++){
				c->data[rows+i][j]=b.data[i][j];
				//memcpy(&c.data[rows+i][j],&b.data[i][j],sizeof(b.data[0]));
			}
		}
		//c->print();
		return *c;
	}
	else if(axis==1){
		//concatenate b at the last column of a
		if(rows!=b.rows){
			cerr<<"Incompatible matrix dimension: ["<<rows<<"*"<<cols<<"]\t["<<b.rows<<"*"<<b.cols<<"]"<<endl;
			throw "Incompatible matrix dimension:";
		}
		Matrix *c=new Matrix(rows,cols+b.cols);
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++){
				c->data[i][j]=data[i][j];
			}
		}
		for(int i=0;i<rows;i++){
			for(int j=0;j<b.cols;j++){
				c->data[i][cols+j]=b.data[i][j];
			}
		}
		//c->print();
		return *c;
	}
	else{
		cerr<<"Invalid argument for axis";
		throw "Invalid argument for axis";
	}
}

Matrix Matrix::add(Matrix a, Matrix b){
	if(!(a.rows==b.rows && a.cols==b.cols)){
		cerr<<"Incompatible matrix dimension: ["<<a.rows<<"*"<<a.cols<<"]\t["<<b.rows<<"*"<<b.cols<<"]"<<endl;
		throw "Incompatible matrix dimension:";
		//return NULL;
	}
	Matrix c(a.rows,b.cols);
	for(int i=0;i<a.rows;i++){
		for(int j=0;j<a.cols;j++){
			c.data[i][j]=a.data[i][j] + b.data[i][j];
		}
	}
	return c;
}

Matrix Matrix::subtract(Matrix a, Matrix b){
	if(!(a.rows==b.rows && a.cols==b.cols)){
		cerr<<"Incompatible matrix dimension: ["<<a.rows<<"*"<<a.cols<<"]\t["<<b.rows<<"*"<<b.cols<<"]"<<endl;
		throw "Incompatible matrix dimension:";
		//return NULL;
	}
	Matrix c(a.rows,b.cols);
	for(int i=0;i<a.rows;i++){
		for(int j=0;j<a.cols;j++){
			c.data[i][j]=a.data[i][j] - b.data[i][j];
		}
	}
	return c;
}

Matrix Matrix::mult(Matrix a, Matrix b){
	if(!(a.cols==b.rows)){
		cerr<<"Incompatible matrix dimension: ["<<a.rows<<"*"<<a.cols<<"]\t["<<b.rows<<"*"<<b.cols<<"]"<<endl;
		throw "Incompatible matrix dimension:";
	}
	Matrix c(a.rows,b.cols);
	for(int i=0;i<a.rows;i++){
		for(int j=0;j<b.cols;j++){
			for(int k=0;k<a.cols;k++){
			c.data[i][j]+=a.data[i][k] * b.data[k][j];
			}
		}
	}
	return c;
}



Matrix Matrix::copy(Matrix a){
	Matrix b(a.rows,a.cols);
	for(int i=0;i<a.rows;i++){
		for(int j=0;j<b.cols;j++){
			b.data[i][j]=a.data[i][j];
		}
	}
	return b;
}

Matrix Matrix::concat(Matrix a, Matrix b, int axis=0){
	if(axis==0){
		//concatenate b after the last row of a
		if(a.cols!=b.cols){
			cerr<<"Incompatible matrix dimension: ["<<a.rows<<"*"<<a.cols<<"]\t["<<b.rows<<"*"<<b.cols<<"]"<<endl;
			throw "Incompatible matrix dimension:";
		}
		Matrix c(a.rows+b.rows,a.cols);
		
		for(int i=0;i<a.rows;i++){
			for(int j=0;j<a.cols;j++){
				c.data[i][j]=a.data[i][j];
			}
		}
		for(int i=0;i<b.rows;i++){
			for(int j=0;j<a.cols;j++){
				c.data[a.rows+i][j]=b.data[i][j];
			}
		}
		return c;
	}
	else if(axis==1){
		//concatenate b at the last column of a
		if(a.rows!=b.rows){
			cerr<<"Incompatible matrix dimension: ["<<a.rows<<"*"<<a.cols<<"]\t["<<b.rows<<"*"<<b.cols<<"]"<<endl;
			throw "Incompatible matrix dimension:";
		}
		Matrix c(a.rows,a.cols+b.cols);
		for(int i=0;i<a.rows;i++){
			for(int j=0;j<a.cols;j++){
				c.data[i][j]=a.data[i][j];
			}
		}
		for(int i=0;i<a.rows;i++){
			for(int j=0;j<b.cols;j++){
				c.data[i][a.cols+j]=b.data[i][j];
			}
		}
		return c;
	}
	else{
		cerr<<"Invalid argument for axis";
		throw "Invalid argument for axis";
	}
}

Matrix Matrix::transpose(Matrix a){
	Matrix t(a.getNumCols(),a.getNumRows());
	for(int i=0;i<t.rows;i++){
		for(int j=0;j<t.cols;j++){
			t.data[i][j]=a.data[j][i];
		}
	}
	return t;
}

Matrix& Matrix::random(const int row,const int col,const int minRange, const int maxRange){
	srand((unsigned)time(0));
	Matrix* a=new Matrix(row,col);
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			a->data[i][j] =minRange + rand()%(maxRange-minRange+1);
		}
	}
	//a->print();
	return *a;
}

Matrix& Matrix::random(const int row,const int col){
	srand((unsigned)time(0));
	Matrix* a=new Matrix(row,col);
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			a->data[i][j] = static_cast<double>(rand()) / static_cast<float>(RAND_MAX);
		}
	}
	//a->print();
	return *a;
}



// Define unary - operator.
Matrix& Matrix::operator-()
{
   Matrix *temp = new Matrix(getNumRows(),getNumCols());
   for(int i=0;i<getNumRows();i++){
		for(int j=0;j<getNumCols();j++){
			temp->data[i][j]=-data[i][j];
		}
	}
   return *temp;
}

// Define prefix decrement operator.
Matrix& Matrix::operator++()
{
    for(int i=0;i<getNumRows();i++){
		for(int j=0;j<getNumCols();j++){
			data[i][j]++;
		}
	}
   return *this;
}


// Define postfix increment operator.
Matrix Matrix::operator++(int)
{
   Matrix temp = *this;
   ++*this;
   return temp;
}

// Define prefix decrement operator.
Matrix& Matrix::operator--()
{
   for(int i=0;i<getNumRows();i++){
		for(int j=0;j<getNumCols();j++){
			data[i][j]--;
		}
	}
   return *this;
}

// Define postfix decrement operator.
Matrix Matrix::operator--(int)
{
   Matrix temp = *this;
   --*this;
   return temp;
}



// Define assignment operator.

Matrix& Matrix::operator=( const Matrix &m )
{
	//Commmented to allow the variable size matrix to assign to other
/*    if(!(m.rows==rows && m.cols==cols)){
		cerr<<"Incompatible matrix dimension: ["<<rows<<"*"<<cols<<"]\t["<<m.rows<<"*"<<m.cols<<"]"<<endl;
		throw "Incompatible matrix dimension:";
		//return NULL;
	}*/
   rows = m.getNumRows();
   cols = m.getNumCols();

   data=new double*[rows];
	for(int i=0;i<rows;i++){
		data[i]=new double[cols];
	}

     for(int i=0;i<getNumRows();i++){
		for(int j=0;j<getNumCols();j++){
			data[i][j]=m.getData()[i][j];
		}
	}
	//cout<<"Assignment Operator Overloading called"<<endl;

   return *this;
}



// Define Binary + Operator
Matrix& Matrix::operator+( const Matrix &other ) {
	if(!(other.rows==rows && other.cols==cols)){
		cerr<<"Incompatible matrix dimension: ["<<rows<<"*"<<cols<<"]\t["<<other.rows<<"*"<<other.cols<<"]"<<endl;
		throw "Incompatible matrix dimension:";
		//return NULL;
	}
	Matrix *c=new Matrix(rows,cols);
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			c->data[i][j]=data[i][j] + other.data[i][j];
		}
	}
	return *c;
}

// Define Binary + Operator
Matrix& Matrix::operator+( const double val ) {
	Matrix *c=new Matrix(rows,cols);
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			c->data[i][j]=data[i][j] + val;
		}
	}
	return *c;
}

// Define Binary - Operator
Matrix& Matrix::operator-(const Matrix &other ) {
	if(!(other.rows==rows && other.cols==cols)){
		cerr<<"Incompatible matrix dimension: ["<<rows<<"*"<<cols<<"]\t["<<other.rows<<"*"<<other.cols<<"]"<<endl;
		throw "Incompatible matrix dimension:";
		//return NULL;
	}
	Matrix *c=new Matrix(rows,cols);
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			c->data[i][j]=data[i][j] - other.data[i][j];
		}
	}
	return *c;
}

// Define Binary - Operator
Matrix& Matrix::operator-( const double val ) {
	Matrix* c=new Matrix(rows,cols);
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			c->data[i][j]=data[i][j] - val;
		}
	}
	return *c;
}


// Define Binary * Operator
Matrix& Matrix::operator*( const Matrix &other ) {
	if(!(cols==other.rows)){
		cerr<<"Incompatible matrix dimension: ["<<rows<<"*"<<cols<<"]\t["<<other.rows<<"*"<<other.cols<<"]"<<endl;
		throw "Incompatible matrix dimension:";
	}
	Matrix *c=new Matrix(rows,other.cols);
	for(int i=0;i<rows;i++){
		for(int j=0;j<other.cols;j++){
			for(int k=0;k<cols;k++){
			c->data[i][j]+=data[i][k] * other.data[k][j];
			}
		}
	}
	return *c;
}

// Define Binary * Operator
Matrix& Matrix::operator*( const double val) {
	Matrix *c=new Matrix(rows,cols);
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			c->data[i][j]=val*data[i][j];
		}
	}
	return *c;
}

//Define Binary / Operator
Matrix& Matrix::operator/( const double val ){
	if(val==0){
		cerr<<"Division by zero error"<<endl;
		throw "Division by zero error";
	}
	Matrix *c=new Matrix(rows,cols);
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			c->data[i][j]=data[i][j]/val;
		}
	}
	return *c;
}


//Randomize Rows
Matrix Matrix:: randomizeRows(const Matrix& in){
	int rows=in.getNumRows();
	int cols=in.getNumCols();
	int *ordering=new int[rows];
	//initialize ordering
	for(int i=0;i<rows;i++){
		ordering[i]=i;
	}
	//shuffle ordering
	for(int i=0;i<rows;i++){
		int rnd=rand()%rows;
		int temp=ordering[i];
		ordering[i]=ordering[rnd];
		ordering[rnd]=temp;
	}

	//rearrange matrix based on ordering
	Matrix output=in;
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			int temp=output.getData()[i][j];
			output.getData()[i][j]=output.getData()[ordering[i]][j];
			output.getData()[ordering[i]][j]=temp;
		}
	}

	delete ordering;
	return output;
}

//Generate ordering for Matrix shuffling of Rows
int* Matrix::genOrdering(int rows){
		int* ordering=new int[rows];
	//initialize ordering
	for(int i=0;i<rows;i++){
		ordering[i]=i;
	}
	//shuffle ordering
	for(int i=0;i<rows;i++){
		int rnd=rand()%rows;
		int temp=ordering[i];
		ordering[i]=ordering[rnd];
		ordering[rnd]=temp;
	}
	return ordering;
}

//randomize the Matrix based on the ordering specified
Matrix Matrix::randomizeRows(const Matrix& in,int* ordering){
	int rows=in.getNumRows();
	int cols=in.getNumCols();
 	//rearrange matrix based on ordering
	Matrix output=in;
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			int temp=output.getData()[i][j];
			output.getData()[i][j]=output.getData()[ordering[i]][j];
			output.getData()[ordering[i]][j]=temp;
		}
	}
	return output;
 }