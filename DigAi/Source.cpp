#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "DrawingBoard.h"
#include "Network.h"
#include "FullyConnectedLayer.h"

#define NumOfHiddenLayers 3
#define NumOfNodesInHidden 40
#define NumOfNodesInInput 2025
#define NumOfNodesInOutput 14

int main()
{
    //int arr1[] = { 3,4,2 };
    //int arr2[] = {13, 9, 7, 15, 8, 7, 4, 6, 6, 4, 0, 3};
    //matrix<int> m1(3, 1, arr1);
    //matrix<int> m2(3, 4, arr2);
    //matrix<int> m3(1, 4);
    //m1.TransposeMul(m2, m3);
    //std::cout << m3;
    //while (true) {}
    //return 0;

    sf::RenderWindow window(sf::VideoMode(SCREENSIZE, SCREENSIZE), "DIGAI");
    DrawingBoard* board = new DrawingBoard();

    //board->InsertInput2("data_new");
    //board->InsertInput3("data_new");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            board->SetCell(sf::Mouse::getPosition(window).x,
                sf::Mouse::getPosition(window).y);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            board->ClearBoard();
        }
        window.clear();
        board->DrawBoard(window);
        window.display();
    }

    return 0;
}
