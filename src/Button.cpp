#include "Button.h"
#include "Macros.h"

//Ctors:
Button::Button(ButtonTask to_do,
	sf::Texture* texture,
	sf::Vector2f  location ,
	sf::Vector2f size,
	AnimationTypes ani_type):

	m_task(to_do), type(ani_type)
{
	set_sprite(texture, location, size);
}
//-----------------------------------------------------------------------------

//Draw:
void Button::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
//-----------------------------------------------------------------------------

//Getters:
sf::Sprite Button::get_sprite()
{
	return m_sprite;
}
//-----------------------------------------------------------------------------

//Setters:
void Button::set_sprite(sf::Texture* texture, sf::Vector2f& location, sf::Vector2f size)
{
	m_sprite.setPosition(location);
	m_sprite.setTexture(*texture);
	m_sprite.setScale(size);
}
//-----------------------------------------------------------------------------

//Helpers:
void * Button::on_click(void * args)
{
	return m_task(args);
}
//-----------------------------------------------------------------------------




