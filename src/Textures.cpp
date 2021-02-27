#include "Textures.h"



Textures::Textures()
{
	load_textures();
}


void Textures::load_textures()
{
	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[m_textures.size() - 1]->loadFromFile("RESET.png");

	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[m_textures.size() - 1]->loadFromFile("START.png");

	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[m_textures.size() - 1]->loadFromFile("END_PNT.png");


	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[m_textures.size() - 1]->loadFromFile("START_PNT.png");

	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[m_textures.size() - 1]->loadFromFile("WALL_PNT.png");

	m_textures.push_back(std::make_unique<sf::Texture>());
	m_textures[m_textures.size() - 1]->loadFromFile("DELETE_PNT.png");
}

//getters:
sf::Texture* Textures::get_texture(TextureName name)
{
	return m_textures[(int)name].get();
}