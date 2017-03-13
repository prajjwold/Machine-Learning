#include <iostream>
#include "Matrix.h"
#include <math.h>

using namespace std;

class MLP{
private:
	Matrix inputs;
	Matrix targets;
	Matrix weight1;
	Matrix weight2;
	double eta; //learning rate

	int nIn; //number of input nodes + bias
	int nOut; //number of output nodes
	int nData; //num of training data rows

	int L; 			//number of input nodes
    int M; 			//number of neurons in hidden layer
	int N; 			//number of output nodes

	//For Chi-Square Data Normalization
	Matrix mean;
	Matrix stdDev;
	//For MinMax Data Normalization
	Matrix min;
	Matrix max;


public:
	MLP( Matrix& in, Matrix& tgt, int hiddenNodes);
	void mlpTrain(Matrix& inputs, Matrix& targets, const double eta, const int iterations);
	Matrix mlpFwd(Matrix& inputs);
	Matrix mlpTest(Matrix& inputs);
	Matrix activationFn(Matrix& in);
	Matrix stepFunction(Matrix& in);
	Matrix sigmoidFunction(Matrix& in);
	double calcError(const Matrix& targets, const Matrix& output);
	void printWeights();
	
	//For Chi-Square Data Normalization
	Matrix calMean(Matrix& in);
	Matrix calstdDeviation(Matrix& in);
	Matrix chiSquareNormalize(const Matrix& in, Matrix& mean, Matrix& stdDev);

	//For MinMax Data Normalization
	Matrix calMin(Matrix& in);
	Matrix calMax(Matrix& in);
	Matrix minMaxNormalize(const Matrix& in, Matrix& min, Matrix& max);
};