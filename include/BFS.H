#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Macros.h"
#include "Algo.h"
class Node;
class Board;

class BFS : public Algo
{
public:
	//no need for c tor
	virtual void do_algo(sf::RenderWindow & window, Board* board) override;

private:

	void clear_neigbors(std::vector<Node*>& list,Node* curr, std::vector<Node*>& neighbors, Board* board);
	void path_found(Node* end_node, Board* board);
	void redraw(Board* board, sf::RenderWindow& window);
};