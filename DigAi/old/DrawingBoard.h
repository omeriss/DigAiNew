#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include "Constants.h"
#include "NeuralNetwork.h"

class DrawingBoard
{
public:
	DrawingBoard();
	void DrawBoard(sf::RenderWindow& window);
	void SetCell(int x, int y);
	void ClearBoard();
	void InsertInput(const char* dataName, const char* labelName, int mode);
	int GetNum();

private:
	NeuralNetwork* network;
	float board[PIXELLEN][PIXELLEN];
	sf::RectangleShape pixel;
	int lastX, lastY;
	sf::Font font;
	sf::Text text;
};

