#pragma once
#include <vector>
#include <functional>
#include "Layer.h"

NetworkType* disCostDerivative(std::vector<NetworkType> output, int label);

class Network
{
public:
	Network(std::vector<Layer*> layers, size_t inputSize, size_t outputSize, std::string path = "");
	std::vector<NetworkType> FeedForword(NetworkType* input);
	void Backpropagation(NetworkType* input, int label, std::function<NetworkType* (std::vector<NetworkType>, int)>& costDerivative);
	void Learn(std::vector<NetworkType*>& input, std::vector<int>& label, std::function<NetworkType* (std::vector<NetworkType>, int)> costDerivative, int epochs, double learnRate, int setSize, std::string savePath = "");
private:
	void SaveNetwork(std::string path);
	std::vector<Layer*> layers;
	NetworkType* input, *output;
	size_t inputSize, outputSize;
};

