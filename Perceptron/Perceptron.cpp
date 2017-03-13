#include "Perceptron.h"


Perceptron::Perceptron( Matrix& in, Matrix& tgt){
	nData=in.getNumRows();
	// inputs=new Matrix(nData,in.getNumCols()+1);
	inputs = in.concat(-Matrix::ones(nData,1),1);
	// inputs.print();
	targets=tgt;

	nIn=inputs.getNumCols(); 
	nOut=targets.getNumCols(); 

	//Initialize weights
	//weights=Matrix::zeros(nIn,nOut);
	weights=Matrix::random(nIn,nOut,1,10);
	weights=weights*0.1-0.05;
}


void Perceptron::pcnTrain(Matrix& in, Matrix& tgt, const double eta, const int iterations){
	nData=in.getNumRows();
	//Add bias to the input
	inputs = in.concat(-Matrix::ones(nData,1),1);
	targets=tgt;

	nIn=inputs.getNumCols(); 
	nOut=targets.getNumCols(); 

	//Initialize weights
	weights=Matrix::random(nIn,nOut,1,10);
	weights=weights*0.1-0.05;

	//cout<<"BEGIN TRAINING"<<endl;

	for(int i=0;i<iterations;i++){
		//cout<<"Iterations: "<<i<<endl;
		//cout<<"Weights"<<endl;
		//printWeights();
		Matrix outputs= pcnFwd(in);
		// cout<<"Outputs"<<endl;
		//in.concat(outputs,1).print();
		weights=weights-(inputs.transpose()*(outputs-targets)*eta);
		
		//Randomize order of inputs

	}

}

Matrix Perceptron::activationFn(Matrix& in){
	Matrix outputs= Matrix(in.getNumRows(),in.getNumCols());
	for(int i=0;i<in.getNumRows();i++){
		for(int j=0;j<in.getNumCols();j++){
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

Matrix Perceptron::pcnFwd( Matrix& in){
	nData=in.getNumRows();
	//Add bias to the input
	Matrix inputs = in.concat(-Matrix::ones(nData,1),1);
	int nData=inputs.getNumRows();

	Matrix activations = inputs*weights;
	Matrix outputs=activationFn(activations);
	//cout<<"Inputs-Outputs"<<endl;
	//in.concat(outputs,1).print();
	return outputs;
}

Matrix Perceptron::pcnTest( Matrix& in){
	nData=in.getNumRows();
	//Add bias to the input
	Matrix inputs = in.concat(-Matrix::ones(nData,1),1);
	int nData=inputs.getNumRows();

	Matrix activations = inputs*weights;
	Matrix outputs=activationFn(activations);
	//cout<<"Inputs-Outputs"<<endl;
	in.concat(outputs,1).print();
	return outputs;
}