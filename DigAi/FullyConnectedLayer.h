#pragma once
#include "Layer.h"
class FullyConnectedLayer :
    public Layer
{
public:
	FullyConnectedLayer(size_t inputSize, size_t outputSize);
	void UploadFromFile(std::ifstream& file);
	void FeedForword();
	void SaveToFile(std::ofstream& file);
	void SetUpLearning();
	virtual void UpdateByGradient(double learnRate, int setSize);
	NetworkType* Backpropagation(NetworkType* outputGradient);
	~FullyConnectedLayer();
private:
	size_t inputSize, outputSize;
	matrix<NetworkType> weights;
	Vector<NetworkType> biases;
	matrix<NetworkType>* weightsGradient;
	Vector<NetworkType>* biasesGradient;
};

