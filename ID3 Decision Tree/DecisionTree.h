#include <iomanip>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <stdlib.h> 
using namespace std;


class DecisionTree{
private:
	//Num of features
	int numFeatures;
    //Data Structure to hold training data
    vector<vector<string> > data;
    //Data Structure to hold the features list
    vector<string> featurelist;
    //Data Structure to  hold the mapping for feature and list of values
    map<string,vector<string> > features;
public:
	void readData();
	double calcEntropy(vector<string> answer);
	double calcInfoGain(string feature, vector<string> featureValues, vector<vector<string> > data);
	void makeTree();

	void printFeatures();	
	void printData();
	void printData(vector<string> feature);
	void printData(vector<vector<string> > data);
	//Retrieve the column of data of the given feature only from whole data
	vector<string> retrieveFeatureData(string feature, vector<vector<string> > data);
	//Retrieve only the selected output data related to the feature with particular value
	vector<string> retrieveOutputData(string feature,string value, vector<vector<string> > data);

	int getIndex(vector<string> values, string value);
	bool checkValueExist(vector<string> values, string value);
	//retrieve the distinct values of the featureData
	vector<string> getDistinctFeatureValues(string feature, vector<string> featureData);
	//check if the feature is continuous or not
	bool isContinuous(string feature);
	//modify the value for the continuous feature in training data into two possible values (<=value and >value)
	vector<vector<string> > modifyData(string feature,string value,vector<vector<string> > data);
	// Return a feature Value on the continous feature for which the information gain is maximum when featureData is splitted on the basis of the value
	string getValueWithMaxInfoGain(string feature,vector<vector<string> > data);
	//transform Continuous Feature to Discrete Feature (with two values (<=value and >value)) with Maximum Information Gain
	vector<string> transformDiscrete(string feature,vector<vector<string> > data);
};