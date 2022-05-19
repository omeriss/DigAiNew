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
    //int arr1[] = { 17, 24, 1, 8, 15, 23, 5, 7, 14, 16, 4, 6, 13, 20, 22, 10, 12, 19, 21, 3, 11, 18, 25, 2, 9 };
    //int arr2[] = {1, 3, 1, 0, 5, 0, 2, 1, 2};
    //matrix<int> m1(5, 5, arr1);
    //matrix<int> m2(3, 3, arr2);
    //matrix<int> m3(7, 7);
    //m1.FullConvolution(m2, m3);
    //std::cout << m3;
    //while (true) {}
    //return 0;

    sf::RenderWindow window(sf::VideoMode(SCREENSIZE, SCREENSIZE), "DIGAI");
    DrawingBoard* board = new DrawingBoard();

    //board->InsertInput2("data_new");
    board->InsertInput3("data_new");

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
