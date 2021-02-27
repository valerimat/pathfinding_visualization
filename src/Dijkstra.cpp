#include "Dijkstra.h"
#include "Node.h"
#include "Graph.h"
#include "Board.h"

/*
each node we havent yet met node.data == nullptr we says its current distance in inf 
after meating a node we set its distance based on father distance +1
*/

void Dijikstra::do_algo(sf::RenderWindow& window, Board* board)
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

	//here we hold all nodes we were already on -> to select the one with the lowest value
	std::vector<Node*> nodes;
	//nodes that we already relaxed
	std::vector<Node*> set_nodes;

	//will hold curr node we check
	Node* curr = nullptr;

	//1.we set starting node distance to be 0 and place it in the nodes vector
	int distance = 0;
	int index_of_lowest = 0;

	//might replace it with templates later:
	start_node->set_data((void*)&distance);

	nodes.push_back(start_node);

	while (!is_discovered(end, set_nodes))
	{
		if (nodes.size() == 0)
			return;

		//we extract node with lowest value
		index_of_lowest = get_node_with_lowest_dist(nodes);
		
		Node* curr = nodes[index_of_lowest];
		board->set_checked(curr->get_location());

		std::vector<Node*> neigbors = curr->get_neighboor_list();
		//relax its neigbors if needed
		set_neighbors(curr,nodes,neigbors,board,window);

		//move it to set_nodes
		nodes.erase(nodes.begin() + index_of_lowest);
		set_nodes.push_back(curr);
		//continue

		redraw(board, window);
	}

	draw_path(board, window, end_node);
}
//-----------------------------------------------------------------------------

bool Dijikstra::is_discovered(sf::Vector2i loc, std::vector<Node*> list)
{
	for (auto node : list)
	{
		if (loc == node->get_location())
			return true;
	}
	return false;
}
//-----------------------------------------------------------------------------

int Dijikstra::get_node_with_lowest_dist(std::vector<Node*> nodes)
{
	int lowest = 0;
	int index = 0;

	for (int i = 0; i < nodes.size(); ++i)
	{
		if (lowest == 0)
		{
			index = i;
			lowest = (*(int*)nodes[i]->get_data());
		}
		else if((*(int*)nodes[i]->get_data()) < lowest)
		{
			index = i;
			lowest = (*(int*)nodes[i]->get_data());
		}
	}
	return index;
}
//-----------------------------------------------------------------------------

void Dijikstra::set_neighbors(Node* curr,
	std::vector<Node*>& nodes,
	std::vector<Node*>& neigbors,
	Board* board,
	sf::RenderWindow & widndow)
{
	int * curr_value = new int(*(int*)curr->get_data());
	(*curr_value)++;

	for (auto node : neigbors)
	{
		//it means its infinity
		if (node->get_data() == nullptr)
		{
			node->set_data((void*)((curr_value)));
			node->set_father(curr);
			nodes.push_back(node);
			board->set_pending(node->get_location());
		}
		else
		{
			if (*(int*)curr->get_data() > * curr_value)
			{
				node->set_data((void*)(curr_value));
				node->set_father(curr);
				nodes.push_back(node);
			}
		}
	}
}
//-----------------------------------------------------------------------------

void Dijikstra::draw_path(Board* board, sf::RenderWindow& window, Node* end_node)
{
	while (end_node != nullptr)
	{
		board->set_found(end_node->get_location());
		end_node = end_node->get_father();
	}
	redraw(board, window);
}
//-----------------------------------------------------------------------------

void Dijikstra::redraw(Board* board, sf::RenderWindow& window)
{
	window.clear();

	board->draw(window);

	window.display();
}
//-----------------------------------------------------------------------------