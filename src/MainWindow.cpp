#include "SFML/Graphics.hpp"
#include "Settings.h"
#include "MainWindow.h"
#include "UI.h"
#include "board.h"


void MainWindow::Run(Algorithm algo)
{
    sf::Mouse mouse;

    auto &settings = Settings::get_settings();

    Board * board = new Board;

    UI ui(algo,board);
   

    sf::RenderWindow window(sf::VideoMode(settings.get_window_width(), settings.get_window_height()), "My window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        //=======================================
        auto location = window.mapPixelToCoords(
            { mouse.getPosition(window).x, mouse.getPosition(window).y });

        board->check_hover(location);

        //=======================================

        window.clear();

        ui.draw(window);
        board->draw(window);

        window.display();
        
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
            break;

            case sf::Event::MouseButtonPressed:
            {
                auto location = window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });

                switch (event.mouseButton.button)
                {
                case sf::Mouse::Button::Left:
                {
                    ui.check_pressed(location,window);
                    board->check_pressed(location);
                    break;
                }
                break;
                }
                break;
            }
            default:
                break;
            }
        }
    }
}
//-----------------------------------------------------------------------------


	
