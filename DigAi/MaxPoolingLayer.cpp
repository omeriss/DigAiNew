#include "MaxPoolingLayer.h"

MaxPoolingLayer::MaxPoolingLayer(size_t intputWidth, size_t inputHeight, size_t channels, size_t poolSize, size_t stride)
	:Layer(nullptr, channels * ((intputWidth - poolSize)/stride + 1) * ((inputHeight - poolSize)/ stride + 1)){

	outputHeight = (inputHeight - poolSize) / stride + 1;
	outputWidth = (intputWidth - poolSize) / stride + 1;
	this->intputWidth = intputWidth;
	this->inputHeight = inputHeight;
	this->channels = channels;
	this->poolSize = poolSize;
	this->stride = stride;

	// init output matrices
	NetworkType* outputTemp = this->output;
	for (int i = 0; i < channels; i++) {
		outputMatrices.push_back(new matrix<NetworkType>(outputWidth, outputHeight, outputTemp));
		outputTemp = outputTemp + (outputWidth * outputHeight);
	}
}

void MaxPoolingLayer::SetInput(NetworkType* input)
{
	// throw error if done more than once
	if (inputMatrices.size() != 0)
		throw "can't set input twice";

	// init input
	Layer::SetInput(input);
	for (int i = 0; i < channels; i++) {
		inputMatrices.push_back(new matrix<NetworkType>(inputHeight, intputWidth, input));
		input = input + (inputHeight * intputWidth);
	}
}

void MaxPoolingLayer::SetUpLearning()
{
	if (!inputGradient) {
		inputGradient = new NetworkType[intputWidth * inputHeight * channels];
	}
}

void MaxPoolingLayer::FeedForword()
{
	int k = 0;
	for (auto inputMat : inputMatrices) {
		for (int i = 0; i < inputHeight - poolSize; i += stride) {
			for (int j = 0; j < intputWidth - poolSize; j += stride) {
				(*(outputMatrices[k]))[i/stride][j/stride] = inputMat->GetMax(i, j, poolSize, poolSize).second;
			}
		}
		k++;
	}
}


NetworkType* MaxPoolingLayer::Backpropagation(NetworkType* outputGradient)
{
	// init output Gradient matrices
	std::vector<matrix<NetworkType>*> outputGradientMatrices;
	for (int i = 0; i < channels; i++) {
		outputGradientMatrices.push_back(new matrix<NetworkType>(outputHeight, outputWidth, outputGradient));
		outputGradient = outputGradient + (outputWidth * outputHeight);
	}

	// init input Gradient matrices
	NetworkType* inputGTemp = this->inputGradient;
	std::vector<matrix<NetworkType>*> inputGradientMatrices;
	for (int i = 0; i < channels; i++) {
		inputGradientMatrices.push_back(new matrix<NetworkType>(inputHeight, intputWidth, inputGTemp));
		inputGradientMatrices[inputGradientMatrices.size() - 1]->Zeros();
		inputGTemp = inputGTemp + (inputHeight * intputWidth);
	}

	int k = 0;
	for (auto inputMat : inputMatrices) {
		for (int i = 0; i < inputHeight - poolSize; i += stride) {
			for (int j = 0; j < intputWidth - poolSize; j += stride) {
				auto best = inputMat->GetMax(i, j, poolSize, poolSize);
				(*(inputGradientMatrices[k]))[best.first.first][best.first.second] = (*(outputGradientMatrices[k]))[i/stride][j/stride];
			}
		}
		k++;
	}

	return inputGradient;
}

MaxPoolingLayer::~MaxPoolingLayer()
{
}
