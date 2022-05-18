#include "FullyConnectedLayer.h"

FullyConnectedLayer::FullyConnectedLayer(size_t inputSize, size_t outputSize):Layer(nullptr, outputSize), weights(outputSize, inputSize), biases(outputSize)
{
	this->inputSize = inputSize;
	this->outputSize = outputSize;
	weights.RandomInit();
	biases.RandomInit();
	biasesGradient = nullptr;
	weightsGradient = nullptr;
}

void FullyConnectedLayer::UploadFromFile(std::ifstream& file)
{
	file.read((char*)biases.GetPointer(), sizeof(NetworkType) * outputSize);
	file.read((char*)weights.GetPointer(), sizeof(NetworkType) * outputSize * inputSize);
}

void FullyConnectedLayer::FeedForword()
{
	Vector<NetworkType> inputVec(inputSize, input);
	Vector<NetworkType> outputVec(outputSize, output);
	weights.mul(inputVec, outputVec);
	outputVec += biases;
}

void FullyConnectedLayer::SaveToFile(std::ofstream& file)
{
	file.write((const char*)biases.GetPointer(), sizeof(NetworkType) * outputSize);
	file.write((const char*)weights.GetPointer(), sizeof(NetworkType) * outputSize * inputSize);
}

void FullyConnectedLayer::SetUpLearning()
{
	if (!inputGradient) {
		inputGradient = new NetworkType[inputSize];
		biasesGradient = new Vector<NetworkType>(outputSize);
		weightsGradient = new matrix<NetworkType>(outputSize, inputSize);
		biasesGradient->Zeros();
		weightsGradient->Zeros();
	}
}

void FullyConnectedLayer::UpdateByGradient(double learnRate, int setSize)
{
	(*biasesGradient) *= learnRate / setSize;
	(*weightsGradient) *= learnRate / setSize;
	biases -= *biasesGradient;
	weights -= *weightsGradient;
	biasesGradient->Zeros();
	weightsGradient->Zeros();
}

NetworkType* FullyConnectedLayer::Backpropagation(NetworkType* outputGradient)
{
	Vector<NetworkType> outputGradientVec(outputSize, outputGradient);
	Vector<NetworkType> inputVec(inputSize, input);
	Vector<NetworkType> inputGradientVec(inputSize, inputGradient);
	outputGradientVec.mulTranspose(inputVec, *weightsGradient ,true);
	(*biasesGradient) += outputGradientVec;
	weights.TransposeMul(outputGradientVec, inputGradientVec);
	return inputGradient;
}

FullyConnectedLayer::~FullyConnectedLayer()
{
	if (biasesGradient)
		delete biasesGradient;
	if (weightsGradient)
		delete weightsGradient;
}
