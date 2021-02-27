#pragma once
#include "SFML/Graphics.hpp"
#include "board.h"

//will be a virtual class for the algorithms
class Algo
{
public:
	virtual void do_algo(sf::RenderWindow& window, Board* board) = 0;
private:

};