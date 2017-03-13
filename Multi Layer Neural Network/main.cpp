#include<iostream>
#include<cstdlib>
#include<fstream>
#include<math.h>
#include "MLP.h"
using namespace std;


int main()
{
    int in,hiddenNodes,rows,cols;
	//read training data set
	cin>>in>>hiddenNodes>>rows>>cols;
	
	Matrix trainingSet(rows,cols);
	Matrix inputs(rows,in);
	Matrix targets(rows,cols-in);
	double value;
	for(int i=0;i<rows;i++){
		int k=0;
		for(int j=0;j<cols;j++){
			cin>>value;
			trainingSet.getData()[i][j]=value;
			if(j<in){
				inputs.getData()[i][j]=value;
			}
			else{
				targets.getData()[i][k++]=value;
			}

		}
	}
		
	//Train the MLP
	 MLP mlp(inputs,targets,hiddenNodes);
	 mlp.mlpTrain(inputs,targets,0.1,3000);

	//read test data set
	cin>>rows>>cols;
	Matrix testSet(rows,cols);
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			cin>>value;
			testSet.getData()[i][j]=value;
		}
	}
	//BEGIN TESTING
	cout<<"BEGIN TESTING"<<endl;
	mlp.mlpTest(testSet);

	return 0;
}