#include <SFML/Graphics.hpp>
#include "checkers_sfml.h"
#include "checkers.h"
#include <iostream>
#include <cctype>

void jugarDamasSFML() {
   
    const unsigned int windowSize = 800;
    sf::RenderWindow window;
    window.create(sf::VideoMode(sf::Vector2u{windowSize, windowSize}, 32), "Damas en SFML");

    initBoard(); 

    const int N = getBoardSize();                 
    const float cellSize = static_cast<float>(windowSize) / static_cast<float>(N);

    sf::RectangleShape square(sf::Vector2f(cellSize, cellSize));
    sf::CircleShape pieceShape(cellSize * 0.4f);
    pieceShape.setOrigin(sf::Vector2f(pieceShape.getRadius(), pieceShape.getRadius()));

    int selRow = -1, selCol = -1;

    while (window.isOpen()) {
     
        while (auto evOpt = window.pollEvent()) {
            const auto &ev = *evOpt;
            
            if (ev.is<sf::Event::Closed>()) {
                window.close();
                break;
            }
         
            if (ev.is<sf::Event::MouseButtonPressed>()) {
                
                if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                    continue;

                sf::Vector2i mp = sf::Mouse::getPosition(window);
                int mx = mp.x;
                int my = mp.y;
                int row = my / static_cast<int>(cellSize);
                int col = mx / static_cast<int>(cellSize);
                if (row < 0 || row >= N || col < 0 || col >= N) continue;

                if (selRow == -1) {
                   
                    char cell = getCell(row, col);
                    char cur = getCurrentPlayer();
                    if (cell == cur || cell == static_cast<char>(std::toupper(static_cast<unsigned char>(cur)))) {
                        selRow = row; selCol = col;
                    } else {
                    
                    }
                } else {
                    
                    char winner = 0;
                    bool ok = tryMoveGUI(selRow, selCol, row, col, winner);
                    selRow = selCol = -1;
                    if (ok) {
                        if (winner != 0) {
                            std::cout << "Game over. Winner: " << winner << "\n";
                            window.close();
                            break;
                        }
                    } else {
                
                        std::cout << "Invalid move\n";
                    }
                }
            }
        }

        window.clear();

       
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if ((r + c) % 2 == 0)
                    square.setFillColor(sf::Color(240, 217, 181)); 
                else
                    square.setFillColor(sf::Color(181, 136, 99));  

                square.setPosition(sf::Vector2f{c * cellSize, r * cellSize});
                window.draw(square);

                char cell = getCell(r, c);
                if (cell != '.' && cell != ' ') {
                   
                    if (cell == 'w' || cell == 'W') pieceShape.setFillColor(sf::Color::White);
                    else pieceShape.setFillColor(sf::Color::Black);

                   
                    if (cell == 'W' || cell == 'B') {
                        pieceShape.setOutlineThickness(3.f);
                        pieceShape.setOutlineColor(sf::Color::Yellow);
                    } else {
                        pieceShape.setOutlineThickness(0.f);
                    }

                    pieceShape.setPosition(sf::Vector2f{c * cellSize + cellSize * 0.5f, r * cellSize + cellSize * 0.5f});
                    window.draw(pieceShape);
                }
            }
        }

    
        if (selRow != -1) {
            sf::RectangleShape highlight(sf::Vector2f(cellSize, cellSize));
            highlight.setPosition(sf::Vector2f{selCol * cellSize, selRow * cellSize});
            highlight.setFillColor(sf::Color(0, 0, 0, 0));
            highlight.setOutlineThickness(3.f);
            highlight.setOutlineColor(sf::Color::Green);
            window.draw(highlight);
        }

        window.display();
    }
}
