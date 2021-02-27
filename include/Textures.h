#pragma once
#include "Macros.h"
#include <vector>
#include "SFML/Graphics.hpp"
//Singelton class to handle texture loading

class Textures
{
public:
	// get singleton
	static Textures& get_textures() { static Textures s_texturs; return s_texturs; };

	//getters:
	sf::Texture * get_texture(TextureName name);



private:
	// c-tor
	Textures();

	// avoids copy 
	Textures(const Textures&) = delete;
	void operator=(Textures const&) = delete;

	void load_textures();

	std::vector<std::unique_ptr<sf::Texture>> m_textures;
};
