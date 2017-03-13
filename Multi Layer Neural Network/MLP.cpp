#include "MLP.h"
#include <iomanip>
#include <math.h>
#include <fstream>
using namespace std;

/**
* Input Layer : 	L input nodes
* Hidden Layer1: 	M neurons
* Output Layer: 	N output nodes
*
*/


MLP::MLP( Matrix& in, Matrix& tgt, int hiddenNodes){
	nData=in.getNumRows();
	inputs = in.concat(-Matrix::ones(nData,1),1);
	targets=tgt;
	L=in.getNumCols();
	M=hiddenNodes;
	N=tgt.getNumCols();
	nIn=inputs.getNumCols(); //L+1
	nOut=tgt.getNumCols();   //N


	//Initialize weights
	weight1=Matrix::random(L+1,M,-0.1,0.1);
	weight2=Matrix::random(M+1,N,-0.1,0.1);

	//For Chi-Square Data Normalization
	mean=Matrix::zeros(1,inputs.getNumCols());
	stdDev=Matrix::zeros(1,inputs.getNumCols());

	//For MinMax Normalization
	min=Matrix::zeros(1,inputs.getNumCols());
	max=Matrix::zeros(1,inputs.getNumCols());
}


void MLP::mlpTrain(Matrix& in, Matrix& tgt, const double n, const int iterations){

	eta=n;
	// //MinMax Normalization
	// min = calMin(in);
	// max = calMax(in);
	// Matrix normalized=minMaxNormalize(in,min,max);

	//ChiSquare Normalization
	mean = calMean(in);
	stdDev = calstdDeviation(in);
	Matrix normalized=chiSquareNormalize(in,mean,stdDev);

	nData=in.getNumRows();
	//Add bias to the input
	inputs = normalized.concat(-Matrix::ones(nData,1),1);
	targets=tgt;

	nIn=inputs.getNumCols(); 
	nOut=targets.getNumCols(); 
	
	//cout<<"BEGIN TRAINING"<<endl;
	for(int i=0;i<iterations;i++){
		Matrix outputs= mlpFwd(in);
	}
}

Matrix MLP::mlpFwd( Matrix& in){
	nData=in.getNumRows();

	//MinMax Normalization
	//Matrix normalized=minMaxNormalize(in,min,max);

	//ChiSquare Normalization
	Matrix normalized=chiSquareNormalize(in,mean,stdDev);

//------------Activation at Layer 1------------------------------//
	//Add bias to the input
	Matrix input1 = normalized.concat(-Matrix::ones(nData,1),1);
	int nData=input1.getNumRows();
	//Hidden Layer Activation
	Matrix activation1 = input1*weight1;
	//Hidden Layer Output
	Matrix output1=activationFn(activation1);

//------------Activation at Layer 2-----------------------------//
	//Add bias to the output from hidden layer
	Matrix input2 = output1.concat(-Matrix::ones(nData,1),1);
	//Output Layer Activation
	Matrix activation2 = input2*weight2;
	//Output
	Matrix output2=activationFn(activation2);

	//--------------------Back Propagation----------------------//
	// //Error at output Layer
	Matrix Dout=(targets-output2).mult(output2).mult(-output2+1);
	//Error at Hidden Layer
	Matrix Dhidden=input2.mult(-input2+1).mult(Dout*weight2.transpose());
	// //Update Weights at Output Layer
	weight2=weight2+((input2.transpose() * Dout)*eta);
	//Remove the Bias Part off the end from Dhidden
	Matrix Dhidden1 = Dhidden.subset(Dhidden.getNumRows(),Dhidden.getNumCols()-1);
	//Update Weights at Output Layer
	weight1=weight1+((input1.transpose() * Dhidden1)*eta);

	return output2;
}

Matrix MLP::mlpTest( Matrix& in){
	nData=in.getNumRows();

	//ChiSquare Normalization
	Matrix normalized=chiSquareNormalize(in,mean,stdDev);

	//MinMax Normalization
	//Matrix normalized=minMaxNormalize(in,min,max);

	//------------Activation at Layer 1------------------------------//
	//Add bias to the input
	Matrix input1 = normalized.concat(-Matrix::ones(nData,1),1);
	//Hidden Layer Activation
	Matrix activation1 = input1*weight1;
	//Hidden Layer Output
	Matrix output1=activationFn(activation1);

//------------Activation at Layer 2-----------------------------//
	//Add bias to the output from hidden layer
	Matrix input2 = output1.concat(-Matrix::ones(nData,1),1);
	//Output Layer Activation
	Matrix activation2 = input2*weight2;
	//Hidden Layer Output
	Matrix output2=activationFn(activation2);
	//weight2.print();

	Matrix concatResult=in.concat(output2,1);
	for(int i=0;i<in.getNumRows();i++){
			cout<<std::setprecision(2)<<std::fixed;
			cout<<concatResult.getData()[i][0]<<"\t"<<concatResult.getData()[i][1]<<"\t"<<concatResult.getData()[i][2]<<"\t"<<concatResult.getData()[i][3]<<"\t";
			cout<<std::setprecision(2)<<std::fixed;
			cout<<concatResult.getData()[i][4]<<"\t"<<concatResult.getData()[i][5]<<"\t"<<concatResult.getData()[i][6]<<endl;
	}
	return output2;
}
Matrix MLP::calMax(Matrix& in){
	int cols=in.getNumCols();
	int rows=in.getNumRows();

	Matrix max =Matrix::zeros(1,cols);
		//calculate max
	for(int i=0;i<cols;i++){
		max.getData()[0][i]=in.getData()[0][i];
		for(int j=1;j<rows;j++){
			if(max.getData()[0][i]<in.getData()[j][i])
			{
				max.getData()[0][i]=in.getData()[j][i];
			}
		}
	}
	return max;
}

Matrix MLP::calMin(Matrix& in){
	int cols=in.getNumCols();
	int rows=in.getNumRows();

	Matrix min =Matrix::zeros(1,cols);
		//calculate min
	for(int i=0;i<cols;i++){
		min.getData()[0][i]=in.getData()[0][i];
		for(int j=1;j<rows;j++){
			if(min.getData()[0][i]>in.getData()[j][i])
			{
				min.getData()[0][i]=in.getData()[j][i];
			}
		}
	}
	return min;
}

Matrix MLP::calMean(Matrix& in){
	int cols=in.getNumCols();
	int rows=in.getNumRows();

	Matrix mean =Matrix::zeros(1,cols);
		//calculate mean
	for(int i=0;i<cols;i++){
		mean.getData()[0][i]=0.0;
		for(int j=0;j<rows;j++){
			mean.getData()[0][i]+=in.getData()[j][i];
		}
	}
	
	mean=mean/rows;
	return mean;
}

Matrix MLP::calstdDeviation(Matrix& in){
	int cols=in.getNumCols();
	int rows=in.getNumRows();

	Matrix stdDev =Matrix::zeros(1,cols);
	Matrix mean =calMean(in);
	//calculate stdDevaition
	for(int i=0;i<cols;i++){
		stdDev.getData()[0][i]=0.0;
		for(int j=0;j<rows;j++){
			stdDev.getData()[0][i]+=pow(in.getData()[j][i]-mean.getData()[0][i],2);
		}
	}
	stdDev=stdDev/rows;
	return stdDev;
}

Matrix MLP::chiSquareNormalize(const Matrix& in, Matrix& mean, Matrix& stdDev){
	if((in.getNumCols()!=mean.getNumCols()) || (in.getNumCols()!=stdDev.getNumCols())){
		cerr<<"Invalid dimension of mean or stdDev for Normalization"<<endl;
		throw "Invalid dimension of mean or stdDev for Normalization";
	}
	int cols=in.getNumCols();
	int rows=in.getNumRows();

	Matrix output = in;

	//Normalize data according to Chi Square Normalization
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			output.getData()[i][j]=(in.getData()[i][j]-mean.getData()[0][j])/stdDev.getData()[0][j];
		}	
	}
	return output;
}


Matrix MLP::minMaxNormalize(const Matrix& in, Matrix& min, Matrix& max){
	if((in.getNumCols()!=max.getNumCols()) || (in.getNumCols()!=min.getNumCols())){
		cerr<<"Invalid dimension of max or min for Normalization"<<endl;
		throw "Invalid dimension of max or min for Normalization";
	}
	int cols=in.getNumCols();
	int rows=in.getNumRows();

	Matrix output = in;
	//Normalize data according to Chi Square Normalization
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
		if(min.getData()[0][j]==max.getData()[0][j]){
			cerr<<"Min = Max \n Divide by zero error"<<endl;
			throw "Divide by zero error";
		}
			output.getData()[i][j]=(in.getData()[i][j]-min.getData()[0][j])/(max.getData()[0][j]-min.getData()[0][j]);
		}	
	}
	return output;
}


void MLP::printWeights(){
		cout<<"Weights 1 :"<<endl;
		weight1.print();
		cout<<"Weights 2 :"<<endl;
		weight2.print();
	}

double MLP::calcError(const Matrix& targets, const Matrix& output){
	double error=0.0;
	if(targets.getNumCols()!=output.getNumCols()){
		throw "Invalid row number for target and output vector";
	}
	for(int j=0;j<output.getNumRows();j++){
		int cols= output.getNumCols();
		for(int i=0;i<cols;i++){
			error+=pow((output.getData()[i][0]-targets.getData()[i][0]),2);
		}
		error*=1.0/2;	
	}
	return error/output.getNumRows();
}
Matrix MLP::activationFn(Matrix& in){ return sigmoidFunction(in);}
Matrix MLP::stepFunction(Matrix& in){
	Matrix outputs= Matrix(in.getNumRows(),in.getNumCols());
	for(int i=0;i<in.getNumRows();i++){
		for(int j=0;j<in.getNumCols();j++){
			//Logic for Step Function
			if(in.getData()[i][j]>0){
				outputs.getData()[i][j]= 1;
			}
			else {
				outputs.getData()[i][j]= 0;
			}
		}
	}
	return outputs;
}
// Saturation point [0,1]
Matrix MLP::sigmoidFunction(Matrix& in){
	double beta=1;
	Matrix outputs= Matrix(in.getNumRows(),in.getNumCols());
	for(int i=0;i<in.getNumRows();i++){
		for(int j=0;j<in.getNumCols();j++){
			//Logic for Sigmoid Function
			outputs.getData()[i][j]= 1.0/(1.0+exp(-beta*in.getData()[i][j]));
		}
	}
	return outputs;
}