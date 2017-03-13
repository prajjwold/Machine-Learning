#include<iostream>
#include<cstdlib>
#include<fstream>
#include "Perceptron.h"
using namespace std;


int main()
{

    // ifstream fin;
    // fin.open("cubeData.txt");
    int in,rows,cols;
	//read training data set
	cin>>in>>rows>>cols;
	//cout<<in<<endl<<rows<<" "<<cols<<endl;
	
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
	//print matrix
	// trainingSet.print();
	// inputs.print();
	// targets.print();

	//Train the Perceptron
	Perceptron pcn(inputs,targets);
	pcn.pcnTrain(inputs,targets,0.25,1000);


	//read test data set
	cin>>rows>>cols;
	//cout<<rows<<" "<<cols<<endl;
	Matrix testSet(rows,cols);
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			cin>>value;
			testSet.getData()[i][j]=value;
		}
	}
	//print matrix
	//testSet.print();
	//BEGIN TESTING
	cout<<"BEGIN TESTING"<<endl;
	pcn.pcnTest(testSet);
}
