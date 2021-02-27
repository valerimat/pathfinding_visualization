#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Algo.h"
class Node;
class Board;

//Implementing dijikstra search algorithm with 1 as weight between 2 adjoint nodes

class DFS : public Algo
{
public:
	//no need for c tor
	virtual void do_algo(sf::RenderWindow& window, Board* board) override;

private:
	void run_recursivly(Node* next_node, Node* end_node, Board* board ,sf::RenderWindow& window);
	void redraw(Board* board, sf::RenderWindow& window);
	void generate_path(Node* end_node, Board* board, sf::RenderWindow& window);
};
