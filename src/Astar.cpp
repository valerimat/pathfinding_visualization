#include "Astar.h"
#include "Node.h"
#include "Graph.h"
#include "Board.h"
#include <chrono>
#include <thread>


void Astar::do_algo(sf::RenderWindow& window, Board* board)
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

	//initialize open and close list
	std::vector<Node* > open_list;
	std::vector<Node* > close_list;

	//getting the data for the starting node
	Astar::data start_values;

	start_node->set_data((void*)&start_values);

	//add first node to open list
	open_list.push_back(start_node);
	
	//while there are nodes in the open list
	while (open_list.size() > 0)
	{
		//might wanna add this part to settings:
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));

		//find the node with lowest f
		int index_of_lowest = find_lowest_f_node(open_list);
		Node* lowest = open_list[index_of_lowest];

		//erase this node
		open_list.erase(open_list.begin() + index_of_lowest);

		//get its neighbors:
		std::vector<Node*> neighbors = lowest->get_neighboor_list();

		//add neighbors to open list 
		add_neighbors(neighbors,lowest, end, open_list,close_list,board);

		//find if end node is in open list:
		int index = end_in_open(open_list,end);

		if (index >= 0)
		{
			generate_path(open_list[index], board, window);
			return;
		}

		close_list.push_back(lowest);
		board->set_checked(lowest->get_location());

		redraw(board,window);
	}
	
}
//-----------------------------------------------------------------------------

int Astar::end_in_open(std::vector<Node*> open_list, sf::Vector2i end_point)
{
	for (int i = 0; i < open_list.size(); ++i)
	{
		if (open_list[i]->get_location() == end_point)
			return i;
	}
	return -1;
}
//-----------------------------------------------------------------------------

int Astar::find_lowest_f_node(std::vector<Node*> open_list)
{
	Node* best_node;
	void* data;
	int index = 0;
	int min_f_value = 0;

	//run on open list find the one with the best index
	for(int i =0; i < open_list.size(); ++i)
	{
		data = open_list[i]->get_data();
		if (min_f_value == 0)
		{
			index = i;
			min_f_value = ((Astar::data*)data)->f_value;
			continue;
		}
		if (((Astar::data*)data)->f_value < min_f_value)
		{
			index = i;
			min_f_value = ((Astar::data*)data)->f_value;
		}
	}

	return index;
}
//-----------------------------------------------------------------------------

void Astar::add_neighbors(
	std::vector<Node*> & neighbors,
	Node* lowest,
	sf::Vector2i end_point, //for calcluating h value
	std::vector<Node*> & open_list,
	std::vector<Node*> close_list,
	Board * board)
{
	

	Astar::data parents_data = *(Astar::data *)lowest->get_data();

	for (int i = 0; i < neighbors.size(); ++i)
	{
		//if no data -> we didnt check it yet
		if (neighbors[i]->get_data() == nullptr)
		{
			neighbors[i]->set_father(lowest);
			Astar::data * values = new Astar::data(
				set_values(parents_data.g_value,
					       manheten_algo(lowest->get_location(),end_point)));

			neighbors[i]->set_data((void *)values);

			open_list.push_back(neighbors[i]);
			board->set_pending(neighbors[i]->get_location());
		}
		else
		{
			//check there is no node in the open list with lowest f
			if (there_is_lowest(open_list, neighbors[i]))
				//if there is do nothing
				continue;
			else if(there_is_lowest(close_list, neighbors[i]))
				continue;
			else
			{
				neighbors[i]->set_father(lowest);
				Astar::data* values = new Astar::data(
					set_values(parents_data.g_value,
						manheten_algo(lowest->get_location(), end_point)));
				neighbors[i]->set_data((void*)&values);
				open_list.push_back(neighbors[i]);
				board->set_pending(neighbors[i]->get_location());
			}
		}
	}
}
//-----------------------------------------------------------------------------

Astar::data Astar::set_values(int parents_g, int h_value)
{
	Astar::data data;
	data.g_value = parents_g + 1;
	data.h_value = h_value;
	data.f_value = data.g_value + data.h_value;

	return data;
}
//-----------------------------------------------------------------------------

bool Astar::there_is_lowest(std::vector<Node*> open_list, Node* cur_node)
{
	for (auto node : open_list)
	{
		if (node->get_location() == cur_node->get_location())
		{
			if ((*(Astar::data*)node->get_data()).f_value 
				<=
				(*(Astar::data*)cur_node->get_data()).f_value)
				return true;
			else
				return false;
		}
	}
	return false;
}
//-----------------------------------------------------------------------------

int Astar::manheten_algo(sf::Vector2i curr, sf::Vector2i to)
{
	int x = abs(curr.x - to.x);
	int y = abs(curr.y - to.y);

	return x + y;
}
//-----------------------------------------------------------------------------

void Astar::generate_path(Node* end_node, Board* board, sf::RenderWindow& window)
{
	while (end_node->get_father() != nullptr)
	{
		board->set_found(end_node->get_location());
		end_node = end_node->get_father();
	}
	redraw(board,window);
}
//-----------------------------------------------------------------------------

void Astar::redraw(Board* board, sf::RenderWindow& window)
{
	window.clear();

	board->draw(window);

	window.display();
}
//-----------------------------------------------------------------------------