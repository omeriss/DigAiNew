#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include "Constants.h"
#include "NeuralNetwork.h"
#include "Network.h"
#include "FullyConnectedLayer.h"
#include "ActivationFunction.h"
#include "ConvolutionalLayer.h"

class DrawingBoard
{
public:
	DrawingBoard();
	void DrawBoard(sf::RenderWindow& window);
	void SetCell(int x, int y);
	void ClearBoard();
	void InsertInput(const char* dataName, const char* labelName, int mode);
	void InsertInput2(string dataName);
	void InsertInput3(string dataName);
	void Test(sf::RenderWindow& window);
	int GetNum();

private:
	NeuralNetwork* network;
	Network* network2;
	float board[PIXELLEN][PIXELLEN];
	sf::RectangleShape pixel;
	int lastX, lastY;
	sf::Font font;
	sf::Text text;
};

