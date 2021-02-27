#pragma once
#include <vector>
#include "Node.h"

/*
will create and hold a graph of the board
*/

class Graph 
{
public:
	//ctors:
	Graph(std::vector<std::vector<char>> data);

	//dtors:
	~Graph();
	
	//getters:
	std::vector<std::vector<Node*>> get_graph();
	Node* get_node(int i, int j);

private:

	//private getters:
	std::vector<Node*> get_neighbors(sf::Vector2i loc);

	//members:
	std::vector<std::vector<Node *>> m_nodes;
};