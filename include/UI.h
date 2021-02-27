#pragma once
#include <SFML/Graphics.hpp>

#include "Button.h"
#include "Macros.h"

class Algo;
class Board;

//Will basically have all the drawing capablities and logic behind the sidebar
//The sidebar will be also the one runing all the actions.

class UI
{
public:
	//ctors and dtors:
	UI(Algorithm algo_name, Board * board);
	~UI();

	//draw:
	void draw(sf::RenderWindow& window);

	//button related:
	void check_pressed(sf::Vector2f& location, sf::RenderWindow& window);

private:

	//button related:
	void do_action(ButtonType type, sf::RenderWindow& window);
	void create_lamdas();
	
	//on load:
	void load_buttons();
	void load_background();
	void load_components();
	void set_algo(Algorithm algo_name);

	//button members:
	std::vector<std::unique_ptr<Button>> m_buttons;
	std::vector<ButtonTask> m_lambdas;
	int m_pressed_index = -1;
	ButtonType m_selected;

	//other members:
	sf::RectangleShape m_background_rect;
	Board * m_board;
	Algo  * m_algo;
};