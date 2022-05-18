#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define NumOfHiddenLayers 3
#define NumOfNodesInHidden 20
#define NumOfNodesInInput 784
// 28*28 pixels
#define NumOfNodesInOutput 10
// the dig
#define SetSize 10

#define TimeTOGoOverTrain 20


typedef double HiddenW[NumOfNodesInHidden][NumOfNodesInHidden];

class NeuralNetwork
{
public:
	NeuralNetwork();
	NeuralNetwork(string fileName);
	int Calc(double* input);
	void SaveToFile(string fileName);
	void BackProp(vector<double*> input, vector<int> label, double jumpSize);
	void Learn(vector<double*>& input, vector<int>& label, double jumpSize);
	void Test(vector<double*>& input, vector<int>& label);

private:
	vector<double> layers[NumOfHiddenLayers + 2];
	vector<double> bias[NumOfHiddenLayers + 1];
	double inputW[NumOfNodesInHidden][NumOfNodesInInput];
	double outputW[NumOfNodesInOutput][NumOfNodesInHidden];
	HiddenW hiddenWs[NumOfHiddenLayers - 1];

};

