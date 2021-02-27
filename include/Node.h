#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "Macros.h"


class Node
{
public:

	//ctors:
	Node(sf::Vector2i location);

	//setters:
	void set_color();
	void set_father(Node * father);
	void set_neigbor_list(std::vector<Node*> nodes);
	void set_data(void* data);

	//getters:
	sf::Vector2i get_location();
	Color get_color();
	Node* get_father();
	void* get_data();
	std::vector<Node*> get_neighboor_list();

	
private:

	//members:
	std::vector<Node*> neighbor_list;
	Color m_color = WHITE;
	Node * m_father = nullptr;
	sf::Vector2i m_location;

	//will hold data for the algorithms
	void* m_data = nullptr;
};