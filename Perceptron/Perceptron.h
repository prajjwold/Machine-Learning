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


public:
	Perceptron( Matrix& in, Matrix& tgt);
	void pcnTrain(Matrix& inputs, Matrix& targets, const double eta, const int iterations);
	Matrix pcnFwd(Matrix& inputs);
	Matrix pcnTest(Matrix& inputs);
	Matrix activationFn(Matrix& in);
	void printWeights(){weights.print();}
};