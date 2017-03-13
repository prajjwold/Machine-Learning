#include "DecisionTree.h"
#include "Tree.h"


void DecisionTree::readData(){
	cin>> numFeatures;

    string line;
    string feature;
    string value;
    getline(cin, line);
    //Read Features
    for (int i = 0; i <= numFeatures; i++) {
        getline(cin, line);
        //cout<<line<<endl;
        istringstream iss(line);
        //first read the feature name
        feature="";
        iss>>feature;
        featurelist.push_back(feature);
        //then read the values part
        value="";
        vector<string> values;
        while (iss >> value) {
            values.push_back(value);
        }
        features[feature] = values;
    }
    printFeatures();

    //read the actual data
    while(getline(cin,line)){
        istringstream iss(line);
        vector<string> row;
        while (iss >> value) {
            row.push_back(value);
        }
        data.push_back(row);
    }
    printData();
}

double DecisionTree::calcEntropy(vector<string> answer){
	double entropy=0;
	//retrieve the values of the output feature
	vector<string> outputValues=features["Ans"];

	// cout<<"Output Values:"<<endl;
	// printData(outputValues);
	// cout<<"Output Data"<<endl;
	// printData(answer);

	//Data structure to hold the mapping for output class and datacount  
	map<string,int> outputClassCount;
	//count the data for each output class
	for(int i=0;i<outputValues.size();i++){
		outputClassCount[outputValues[i]]=0;
		for(int j=0;j<answer.size();j++){
			if(answer[j].compare(outputValues[i])==0){
				outputClassCount[outputValues[i]]++;
			}
		}
		//cout<<outputValues[i]<<" : "<< outputClassCount[outputValues[i]]<<endl;
	}
	for(int i=0;i<outputValues.size();i++){
		double p = (double)outputClassCount[outputValues[i]]/answer.size();
		//cout<<"Probability : "<<outputValues[i]<<"="<<p<<endl;
		if(p!=0){
		entropy-=p*log2(p);
		}
	}
		//cout<<"Entropy: "<<entropy<<endl;
	return entropy;
}

double DecisionTree::calcInfoGain(string feature, vector<string> featureValues, vector<vector<string> > data){
    vector<string> answer = retrieveFeatureData("Ans",data);
    double entropy = calcEntropy(answer);
    double infoGain=entropy;
    for(int i=0; i<featureValues.size();i++){
        vector<string> splittedAnswer = retrieveOutputData(feature, featureValues[i],data);
        // cout<<"Feature:"<<feature<< " | Value:"<<featureValues[i]<<endl;
        // printData(splittedAnswer);
        // cout<<"Entropy Sf: "<<calcEntropy(splittedAnswer)<<endl;
        infoGain-=((double) splittedAnswer.size()/answer.size())*calcEntropy(splittedAnswer);
    }
    return infoGain;
}

void DecisionTree::makeTree(){
	vector<string> answer = retrieveFeatureData("Ans",data);
	//Datastructure to hold mapping for feature and correspoing InfoGain
	map<string,double> featureInfoGain;
	double entropy = calcEntropy(answer);

    //change each continous feature to discrete and accordinly change the trainin data
    for(int i=0;i<featurelist.size();i++){
        if(isContinuous(featurelist[i])){
            vector<string> featureValues = transformDiscrete(featurelist[i], data);  
            string value = getValueWithMaxInfoGain(featurelist[i],data);
            // cout<<"Before:"<< featurelist[i] << endl;
            // printData(features[featurelist[i]]);
            features[featurelist[i]]=featureValues; 
            // cout<<"After:" << featurelist[i] << endl;
            // printData(features[featurelist[i]]);
            data = modifyData(featurelist[i], value, data);
            // cout<<"Modified Data"<<endl;
            // printData(data);
        }
    }

	//Calculate the info gain of each features
	for(int i=0;i<featurelist.size()-1;i++){
            vector<string> featureValues = features[featurelist[i]];
			featureInfoGain[featurelist[i]] =calcInfoGain(featurelist[i],featureValues,data);
			cout<<"Info Gain ["<<featurelist[i]<<"] = "<<featureInfoGain[featurelist[i]]<<endl;
	}
}

vector<string> DecisionTree::retrieveFeatureData(string feature, vector<vector<string> > data){
	int featureIndex =getIndex(featurelist,feature);
	vector<string> featureData;

    if(featureIndex==-1){
        cout<<"DecisionTree::retrieveFeatureData :: Feature "<<feature<<" NOT FOUND"<<endl;
        exit;
    }
    for(int i=0;i<data.size();i++){
    	featureData.push_back(data[i][featureIndex]);
    }

    return featureData;
}

vector<string> DecisionTree::retrieveOutputData(string feature,string value, vector<vector<string> > data){
	vector<string> splittedAnswer;
	vector<string> featureData=retrieveFeatureData(feature, data);
	vector<string> answer=retrieveFeatureData("Ans",data);
    for(int i=0;i<answer.size();i++){
    	if(featureData[i].compare(value)==0){
    		splittedAnswer.push_back(answer[i]);
    	}
    }
    return splittedAnswer;
}


void DecisionTree::printFeatures(){
    for( map<string,vector<string> >::iterator ii=features.begin(); ii!=features.end(); ++ii)
       {
            string feature=(*ii).first;
            vector<string> values=(*ii).second;
            cout << feature << " : " ;
            for(int i=0;i<values.size();i++){
                cout<< values[i] << "\t";
            }
            cout<<endl;
       }
}

void DecisionTree::printData(){
    for(int i=0;i<data.size();i++)
       {
            for(int j=0;j<data[i].size();j++){
                cout<< data[i][j] << "\t";
            }
            cout<<endl;
       }
}

void DecisionTree::printData(vector<string> feature){
    for(int i=0;i<feature.size();i++)
       {
                cout<< feature[i] << endl;
       }
}

void DecisionTree::printData(vector<vector<string> > data){
    for(int i=0;i<data.size();i++)
       {
            for(int j=0;j<data[i].size();j++){
                cout<< data[i][j] << "\t";
            }
            cout<<endl;
       }
}

bool DecisionTree::checkValueExist(vector<string> values, string value){
    if(find(values.begin(),values.end(),value)!=values.end()){
        return true;
    }
    return false;
}

int DecisionTree::getIndex(vector<string> values, string value){
    vector<string>::iterator it;
    it=find(values.begin(),values.end(),value);
    int index = distance(values.begin(), it);

    if(it!=values.end()){
        return index;
    }
    else{
        //cout<<"Value "<<value<<" doesn't exist"<<endl;
        return -1;
    }
}

bool DecisionTree::isContinuous(string feature){
    vector<string> featureValues = features[feature];
    if(featureValues.size()==1 && featureValues[0].compare("continuous")==0){
        return true;
    }
    return false;
}

vector<string> DecisionTree::getDistinctFeatureValues(string feature, vector<string> featureData){
    vector<string> distinctFeatureValues ;
    for (int i=0;i<featureData.size();i++){
        if(!checkValueExist(distinctFeatureValues,featureData[i])){
            distinctFeatureValues.push_back(featureData[i]);
        }
    }
    return distinctFeatureValues;
}

//modify the value for the continuous feature in training data into two possible values (<=value and >value)
vector<vector<string> > DecisionTree::modifyData(string feature,string value,vector<vector<string> > data){
    vector<vector<string> > modifiedData = data;
    int index = getIndex(featurelist,feature);
    for(int i=0;i<data.size();i++){
        if(atof((data[i][index]).c_str())<=atof(value.c_str())){
            modifiedData[i][index]="<="+ value;
        }
        else{
            modifiedData[i][index]=">"+ value;
        }
    }
    return modifiedData;
}

// Return a feature Value on the continuous feature for which the information gain is maximum when featureData is splitted on the basis of the value
string DecisionTree::getValueWithMaxInfoGain(string feature,vector<vector<string> > data){
    if(!isContinuous(feature)){
        cout<<feature<<" : Not a continuous feature"<<endl;
        exit;
    }
    int featureIndex = getIndex(featurelist,feature);
    // Datastructure to hold the mapping between featureValue and InformationGain (when featureData is splitted based on the featureValue)
    map<string,double> valueInfoGain;

    vector<string> featureData=retrieveFeatureData(feature,data);
    vector<string> featureValues = getDistinctFeatureValues(feature,featureData);
    //for each featureValues, split the data based on that value and calculate the info gain
    for(int i=0;i<featureValues.size();i++){
        vector<string> modifiedFeatureValues;
        string value1="<="+featureValues[i];
        string value2=">"+featureValues[i];
        modifiedFeatureValues.push_back(value1);
        modifiedFeatureValues.push_back(value2);

        vector<vector<string> > modifiedData = modifyData(feature, featureValues[i], data);
        valueInfoGain[featureValues[i]]=calcInfoGain(feature,modifiedFeatureValues,modifiedData);
    }

    //Get the featureVal for which the Info Gain was maximum when data was splitted using that value
    string value = featureValues[0];
    int infoGain = valueInfoGain[featureValues[0]];
    for(int i=1;i<featureValues.size();i++){
        if(valueInfoGain[featureValues[i]] > infoGain){
            infoGain=valueInfoGain[featureValues[i]];
            value=featureValues[i];
        }
    }  
    return value;
}

//transform Continuous Feature to Discrete Feature (with two values) with Maximum Information Gain
vector<string> DecisionTree::transformDiscrete(string feature,vector<vector<string> > data){
    string value = getValueWithMaxInfoGain(feature, data);

    vector<string> modifiedFeatureValues;
    string value1="<="+ value;
    string value2=">"+ value;
    modifiedFeatureValues.push_back(value1);
    modifiedFeatureValues.push_back(value2);

    return modifiedFeatureValues;
}
