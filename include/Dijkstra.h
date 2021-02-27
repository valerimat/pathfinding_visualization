#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Algo.h"
class Node;
class Board;

//Implementing dijikstra search algorithm with 1 as weight between 2 adjoint nodes

class Dijikstra : public Algo
{
public:
	//no need for c tor
	virtual void do_algo(sf::RenderWindow& window, Board* board) override;
	
private:
	bool is_discovered(sf::Vector2i loc, std::vector<Node*> list);
	int get_node_with_lowest_dist(std::vector<Node*> nodes);
	void set_neighbors(Node* curr,
	std::vector<Node*>& nodes,
	std::vector<Node*>& neigbors,
	Board* board,
	sf::RenderWindow& widndow);
	void redraw(Board* board, sf::RenderWindow& window);
	void draw_path(Board* board, sf::RenderWindow& window, Node* end_node);
};

