#pragma once
#include "Layer.h"

class ActivationFunction :
	public Layer
{
public:
	ActivationFunction(size_t layerSize);
	void FeedForword();
	void SaveToFile(std::ofstream& file) {};
	void UploadFromFile(std::ifstream& file) {};
	void UpdateByGradient(double learnRate, int setSize) {};
	void SetUpLearning();
	NetworkType* Backpropagation(NetworkType* outputGradient);
	virtual NetworkType Function(NetworkType x) = 0;
	virtual NetworkType FunctionDerivative(NetworkType x) = 0;
private:
	size_t layerSize;
};


class Sigmoid :
	public ActivationFunction
{
public:
	Sigmoid(size_t layerSize);
	NetworkType Function(NetworkType x);
	NetworkType FunctionDerivative(NetworkType x);
};