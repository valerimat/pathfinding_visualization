#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Algo.h"
class Node;
class Board;

//will find the path usign A*

class Astar :public Algo
{
public:
	//no need for c tor
	virtual void do_algo(sf::RenderWindow& window, Board* board) override;

	//this struct will wrap the info
	struct data
	{
		int g_value =0; //distance from start
		int h_value =0; //distance from end
		int f_value =0; //total
	};

private:

	//the function the algorithm uses more info in cpp
	int find_lowest_f_node(std::vector<Node*> open_list);

	void add_neighbors(
		std::vector<Node*> & neighbors,
		Node* lowest,
		sf::Vector2i end_point,
		std::vector<Node*>& open_list,
		std::vector<Node*> close_list,
		Board* board);

	int manheten_algo(sf::Vector2i curr, sf::Vector2i to);

	bool there_is_lowest(std::vector<Node*> open_list, Node* node);

	int end_in_open(std::vector<Node*> open_list, sf::Vector2i end_point);

	Astar::data set_values(int parents_f, int g_value);

	void generate_path(Node * end_node, Board * board,sf::RenderWindow & window);

	void redraw(Board* board, sf::RenderWindow& window);
};

