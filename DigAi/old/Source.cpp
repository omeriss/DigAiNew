#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "DrawingBoard.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREENSIZE, SCREENSIZE), "DIGAI");
    DrawingBoard* board = new DrawingBoard();

    if(UploadFile == "0")
        board->InsertInput(TRAINDATA, TRAINLABEL, 1);
    board->InsertInput(TESTDATA, TESTLABEL, 0);

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
