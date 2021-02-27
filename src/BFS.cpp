#include "BFS.h"
#include "Node.h"
#include "Graph.h"
#include "Board.h"

void BFS::do_algo(sf::RenderWindow & window,Board * board)
{
	std::vector<std::vector<char>> data = board->get_data();
	sf::Vector2i start = board->get_start();
	sf::Vector2i end = board->get_end();

	//safety
	if (start == sf::Vector2i(-1, -1) || end == sf::Vector2i(-1, -1))
		return;

	Graph graph(data);
	Node* start_node = graph.get_node( start.y, start.x);
	Node * end_node = graph.get_node(end.y, end.x);

	

	std::vector<Node*> list;
	std::vector<Node*> neighbors;

	list.push_back(start_node);

	Node* curr;
	while (1)
	{
		if (list.size() == 0)
			return;

		curr = list[0];

		if (curr == end_node)
		{
			path_found(curr, board);
			break;
		}

		board->set_checked(curr->get_location());

		curr->set_color();

		list.erase(list.begin());
		
		neighbors = curr->get_neighboor_list();

		clear_neigbors(list,curr,neighbors,board);
		
		curr->set_color();

		redraw(board, window);

	}

	redraw(board, window);
}
//----------------------------------------------------------------------------

void BFS::clear_neigbors(std::vector<Node*>& list,Node * curr, std::vector<Node*>& neighbors, Board * board)
{
	for (int i = 0; i < neighbors.size() ; ++i)
	{
		if (neighbors[i]->get_color() == WHITE)
		{
			neighbors[i]->set_color();
			neighbors[i]->set_father(curr);
			board->set_pending(neighbors[i]->get_location());
			list.push_back(neighbors[i]);
		}
	}
}
//----------------------------------------------------------------------------

void BFS::path_found(Node * end_node,Board * board)
{
	Node* node = end_node;
	while (node->get_father() != nullptr)
	{
		board->set_found(node->get_location());
		node = node->get_father();
	}
}
//----------------------------------------------------------------------------

void BFS::redraw(Board * board,sf::RenderWindow & window)
{
	window.clear();

	board->draw(window);

	window.display();
}
//----------------------------------------------------------------------------


