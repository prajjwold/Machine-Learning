#include "Perceptron.h"
#include <math.h>
#include <iomanip>


Perceptron::Perceptron( Matrix& in, Matrix& tgt){
	nData=in.getNumRows();
	// inputs=new Matrix(nData,in.getNumCols()+1);
	inputs = in.concat(-Matrix::ones(nData,1),1);
	// inputs.print();
	targets=tgt;

	nIn=inputs.getNumCols(); 
	nOut=targets.getNumCols(); 

	//Initialize weights
	weights=Matrix::zeros(nIn,nOut);
	// weights=Matrix::random(nIn,nOut,1,10);
	// weights=weights*0.1-0.05;

	//For Chi-Square Data Normalization
	mean=Matrix::zeros(1,inputs.getNumCols());
	stdDev=Matrix::zeros(1,inputs.getNumCols());

	//For MinMax Normalization
	min=Matrix::zeros(1,inputs.getNumCols());
	max=Matrix::zeros(1,inputs.getNumCols());
}


void Perceptron::pcnTrain(Matrix& in, Matrix& tgt, const double eta, const int iterations){
	//Normalize the input

	//Chi-Square Normalization
	// mean = calMean(in);
	// stdDev = calstdDeviation(in);
	// Matrix normalized=chiSquarNnormalize(in,mean,stdDev);

	//MinMax Normalization
	min = calMin(in);
	max = calMax(in);
	Matrix normalized=minMaxNormalize(in,min,max);
	//inputs.print();

	nData=in.getNumRows();
	//Add bias to the input
	inputs = normalized.concat(-Matrix::ones(nData,1),1);
	targets=tgt;

	nIn=inputs.getNumCols(); 
	nOut=targets.getNumCols(); 

	//Initialize weights
	//weights=Matrix::zeros(nIn,nOut);
	// weights=Matrix::random(nIn,nOut,1,5);
	// weights=weights*0.1-0.05;
	weights=Matrix::random(nIn,nOut);
	//cout<<"BEGIN TRAINING"<<endl;

	for(int i=0;i<iterations;i++){
		// cout<<"Iterations: "<<i<<endl;

		Matrix outputs= pcnFwd(in);

		// cout<<"Outputs"<<endl;
		//in.concat(outputs,1).print();
		weights=weights-(inputs.transpose()*(outputs-targets)*eta);
		// cout<<"After Weights"<<endl;
		// printWeights();
	}

}

Matrix Perceptron::activationFn(Matrix& in){
	Matrix outputs= Matrix(in.getNumRows(),in.getNumCols());
	for(int i=0;i<in.getNumRows();i++){
		for(int j=0;j<in.getNumCols();j++){
			//Logic for Step Function
			// if(in.getData()[i][j]>0){
			// 	outputs.getData()[i][j]= 1;
			// }
			// else {
			// 	outputs.getData()[i][j]= 0;
			// }

			//Logic for Sigmoid Function
			double beta=30;
			//outputs.getData()[i][j]= round(1/(1+exp(-beta*in.getData()[i][j])));
			outputs.getData()[i][j]= (1.0/(1+exp(-1*beta*in.getData()[i][j])));
		}
	}
	return outputs;
}

Matrix Perceptron::pcnFwd( Matrix& in){
	nData=in.getNumRows();

	// cout<<"Inputs without bias:"<<endl;
	// in.print();

	//Normalized and then Add bias to the input

	//Chi-Square Normalization
	// Matrix normalized=chiSquareNormalize(in,mean,stdDev);

	//MinMax Normalization
	Matrix normalized=minMaxNormalize(in,min,max);
	// cout<<"Normalized Inputs without bias:"<<endl;
	// normalized.print();

	Matrix inputs = normalized.concat(-Matrix::ones(nData,1),1);
	// cout<<"Normalized Inputs with bias:"<<endl;
	// inputs.print();
	int nData=inputs.getNumRows();

	// cout<<"Before Weights:"<<endl;
	// weights.print();

	Matrix activations = inputs*weights;
	// cout<<"Activations:"<<endl;
	// activations.print();

	//activations.print();
	Matrix outputs=activationFn(activations);
	// cout<<"Outputs"<<endl;
	// outputs.print();
	return outputs;
}

Matrix Perceptron::pcnTest( Matrix& in){
	nData=in.getNumRows();
	//Normalized and then Add bias to the input

	//Chi-Square Normalization
	// Matrix normalized=normalize(in,mean,stdDev);

	//MinMax Normalization
	Matrix normalized=minMaxNormalize(in,min,max);

	Matrix inputs = normalized.concat(-Matrix::ones(nData,1),1);
	int nData=inputs.getNumRows();

	Matrix activations = inputs*weights;
	Matrix outputs=activationFn(activations);
	//cout<<"Inputs-Outputs"<<endl;
	//in.concat(outputs,1).print();
	Matrix concatResult=in.concat(outputs,1);
	for(int i=0;i<in.getNumRows();i++){
			cout<<std::setprecision(1)<<std::fixed;
			cout<<concatResult.getData()[i][0]<<"\t"<<concatResult.getData()[i][1]<<"\t"<<concatResult.getData()[i][2]<<"\t"<<concatResult.getData()[i][3];
			cout<<std::setprecision(0)<<std::fixed;
			cout<<"\t"<<(int)concatResult.getData()[i][4]<<"\t"<<(int)concatResult.getData()[i][5]<<"\t"<<(int)concatResult.getData()[i][6]<<endl;
	}
	return outputs;
}
Matrix Perceptron::calMax(Matrix& in){
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

Matrix Perceptron::calMin(Matrix& in){
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

Matrix Perceptron::calMean(Matrix& in){
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

Matrix Perceptron::calstdDeviation(Matrix& in){
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

Matrix Perceptron::chiSquareNormalize(const Matrix& in, Matrix& mean, Matrix& stdDev){
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


Matrix Perceptron::minMaxNormalize(const Matrix& in, Matrix& min, Matrix& max){
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