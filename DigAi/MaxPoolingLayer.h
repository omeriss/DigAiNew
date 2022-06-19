#pragma once
#include "Layer.h"

class MaxPoolingLayer: 
	public Layer
{
public:
	MaxPoolingLayer(size_t intputWidth, size_t inputHeight, size_t channels, size_t poolSize, size_t stride);
	void UploadFromFile(std::ifstream& file) {};
	void FeedForword();
	void SetInput(NetworkType* input);
	void SaveToFile(std::ofstream& file) {};
	void SetUpLearning();
	virtual void UpdateByGradient(double learnRate, int setSize) {};
	NetworkType* Backpropagation(NetworkType* outputGradient);
	~MaxPoolingLayer();
private:
	size_t intputWidth, inputHeight, channels, poolSize, stride;
	size_t outputWidth, outputHeight;
	std::vector<matrix<NetworkType>*> inputMatrices;
	std::vector<matrix<NetworkType>*> outputMatrices;
};

