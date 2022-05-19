#pragma once
#include "Layer.h"
class ConvolutionalLayer :
    public Layer
{
public:
	ConvolutionalLayer(size_t intputWidth, size_t inputHeight, size_t channels, size_t kernelSize, size_t kernelCount);
	void UploadFromFile(std::ifstream& file);
	void SetInput(NetworkType* input);
	void FeedForword();
	void SaveToFile(std::ofstream& file);
	void SetUpLearning();
	virtual void UpdateByGradient(double learnRate, int setSize);
	NetworkType* Backpropagation(NetworkType* outputGradient);
	~ConvolutionalLayer();
private:
	size_t intputWidth, inputHeight, channels, kernelSize, kernelCount;
	size_t outputWidth, outputHeight;
	std::vector<std::vector<matrix<NetworkType>*>> kernels;
	std::vector<matrix<NetworkType>*> biases;
	std::vector<std::vector<matrix<NetworkType>*>> kernelsGradient;
	std::vector<matrix<NetworkType>*> biasesGradient;
	std::vector<matrix<NetworkType>*> inputMatrices;
	std::vector<matrix<NetworkType>*> outputMatrices;
};

