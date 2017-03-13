#include <iostream>
#include "Matrix.h"

using namespace std;


class Perceptron{
private:
	Matrix inputs;
	Matrix targets;
	Matrix weights;
	double eta; //learning rate

	int nIn; //number of input nodes + bias
	int nOut; //number of output nodes
	int nData; //num of training data rows

	//For Chi-Square Data Normalization
	Matrix mean;
	Matrix stdDev;
	//For MinMax Data Normalization
	Matrix min;
	Matrix max;

public:
	Perceptron( Matrix& in, Matrix& tgt);
	void pcnTrain(Matrix& inputs, Matrix& targets, const double eta, const int iterations);
	Matrix pcnFwd(Matrix& inputs);
	Matrix pcnTest(Matrix& inputs);
	Matrix activationFn(Matrix& in);
	void printWeights(){weights.print();}


	//For Chi-Square Data Normalization
	Matrix calMean(Matrix& in);
	Matrix calstdDeviation(Matrix& in);
	Matrix chiSquareNormalize(const Matrix& in, Matrix& mean, Matrix& stdDev);
	//For MinMax Data Normalization
	Matrix calMin(Matrix& in);
	Matrix calMax(Matrix& in);
	Matrix minMaxNormalize(const Matrix& in, Matrix& min, Matrix& max);
};