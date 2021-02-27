#pragma once
#include "SFML/Graphics.hpp"
#include <Functional>

#include "Macros.h"

class Button
{
public:
	//ctors:
	Button(ButtonTask to_do, sf::Texture* texture, sf::Vector2f location, sf::Vector2f size, AnimationTypes type);

	//draw:
	void draw(sf::RenderWindow& window);

	//handle click:
	void * on_click(void* args);
	
	//getters:
	sf::Sprite get_sprite();

private:

	//setters:
	void set_sprite(sf::Texture * texture, sf::Vector2f& location, sf::Vector2f size);

	//members:
	ButtonTask m_task;
	sf::Sprite m_sprite;
	AnimationTypes type;
};



