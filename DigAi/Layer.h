#pragma once
#include <string>
#include <fstream>
#include "Matrix.h"

typedef double NetworkType;

class Layer
{
public:
	Layer(NetworkType* input, NetworkType* output);
	Layer(NetworkType* input, size_t outputSize);
	virtual void SetInput(NetworkType* input);
	NetworkType* GetOutput();
	virtual void FeedForword() = 0;
	virtual NetworkType* Backpropagation(NetworkType* outputGradient) = 0;
	virtual void UpdateByGradient(double learnRate, int setSize) = 0;
	virtual void SaveToFile(std::ofstream& file) = 0;
	virtual void UploadFromFile(std::ifstream& file) = 0;
	virtual void SetUpLearning() = 0;
	~Layer();
protected:
	NetworkType* input;
	NetworkType* output;
	NetworkType* inputGradient;
};