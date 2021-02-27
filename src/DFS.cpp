#include "DFS.h"
#include "Node.h"
#include "Graph.h"
#include "Board.h"

/*
we wont use discovery time, just color the nodes like in bfs
also we will implement it using a recursion 
*/
void DFS::do_algo(sf::RenderWindow& window, Board* board)
{
	//getting start:
	std::vector<std::vector<char>> data = board->get_data();
	sf::Vector2i start = board->get_start();
	sf::Vector2i end = board->get_end();

	//safety
	if (start == sf::Vector2i(-1, -1) || end == sf::Vector2i(-1, -1))
		return;

	//getting nodes and graph:
	Graph graph(data);
	Node* start_node = graph.get_node(start.y, start.x);
	Node* end_node = graph.get_node(end.y, end.x);

	run_recursivly(start_node, end_node,board,window);
	generate_path(end_node, board, window);

}
//-----------------------------------------------------------------------------

void DFS::run_recursivly(Node* next_node, Node* end_node, Board * board,sf::RenderWindow & window)
{
	std::vector<Node* >neigbors = next_node->get_neighboor_list();
	
	next_node->set_color();

	for (auto node : neigbors)
	{
		if (node->get_location() == end_node->get_location())
		{
			node->set_father(next_node);
			return;
		}
		else
		{
			if (node->get_color() != WHITE)
				continue;
			else
			{
				node->set_father(next_node);
				board->set_pending(node->get_location());
				run_recursivly(node, end_node,board, window);
			}
		}
	}
	board->set_checked(next_node->get_location());
	redraw(board, window);
}
//-----------------------------------------------------------------------------

void DFS::redraw(Board* board, sf::RenderWindow& window)
{
	window.clear();

	board->draw(window);

	window.display();
}
//-----------------------------------------------------------------------------

void DFS::generate_path(Node* end_node, Board* board, sf::RenderWindow& window)
{
	while (end_node->get_father() != nullptr)
	{
		board->set_found(end_node->get_location());
		end_node = end_node->get_father();
	}
	redraw(board, window);
}
//-----------------------------------------------------------------------------