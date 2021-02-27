#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

#include "Macros.h"

//will handle all the logic behind the board

class Board
{
public:
	//ctor:
	Board();

	//draw:
	void draw(sf::RenderWindow& window);

	//setters:
	void set_width(int width);
	void set_height(int height);
	void reset();
	void set_selected(ButtonType selected);
	void set_checked(sf::Vector2i);
	void set_found(sf::Vector2i);
	void set_pending(sf::Vector2i);

	//checking hover and clicks:
	void check_hover(sf::Vector2f& location);
	void check_pressed(sf::Vector2f& location);

	//getters:
	std::vector<std::vector <char>> get_data();
	sf::Vector2i get_start();
	sf::Vector2i get_end();

private:

	//helper functions:
	void reset_char_board();
	void reset_size();
	void load_board();
	float size_of_block(int num_of_blocks, float height);
	sf::Vector2f calc_alignment(int width, float window_height, float window_width);

	//other members:
	int m_width = 30;
	int m_height = 30;

	sf::RectangleShape  m_hovered_over_rect;
	sf::RectangleShape* m_end = nullptr;
	sf::RectangleShape* m_start = nullptr;

	//will hold the board data - char for lower space usage
	std::vector<std::vector<char>> m_data;
	std::vector < std::vector < sf::RectangleShape>> m_rects;

	ButtonType m_selected;
};