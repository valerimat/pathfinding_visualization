#include "Graph.h"


//Ctors:
Graph::Graph(std::vector<std::vector<char>> data)
{
	int width = data.size();
	int height = data[0].size();

	m_nodes.resize(height);

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (data[i][j] != WALL)
			{
				Node* node = new Node(sf::Vector2i(j, i));
				m_nodes[i].push_back(node);
			}
			else
				m_nodes[i].push_back(nullptr);
		}
	}

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if(m_nodes[i][j] !=nullptr)
			m_nodes[i][j]->set_neigbor_list(get_neighbors(sf::Vector2i(j,i)));
		}
	}
}
//-----------------------------------------------------------------------------


Graph::~Graph()
{
	if (m_nodes[0].size() > 0)
	{
		for (int i = 0; i < m_nodes[0].size(); ++i)
		{
			for (int j = 0; j < m_nodes.size(); ++j)
			{
				delete m_nodes[i][j];
			}
		}
	}
}
//-----------------------------------------------------------------------------

std::vector<Node*> Graph::get_neighbors (sf::Vector2i loc)
{
	std::vector<Node*> neig;
	//top
	if(loc.y -1 >= 0)
		if (m_nodes[loc.y - 1][loc.x] != nullptr)
		{
			neig.push_back(m_nodes[loc.y - 1][loc.x]);
		}

	//bottom
	if (loc.y + 1 < m_nodes.size())
		if (m_nodes[loc.y + 1][loc.x]!= nullptr)
		{
			neig.push_back(m_nodes[loc.y + 1][loc.x]);
		}

	//left
	if (loc.x - 1 >= 0)
		if (m_nodes[loc.y][loc.x - 1] != nullptr)
		{
			neig.push_back(m_nodes[loc.y][loc.x-1 ]);
		}

	if (loc.x + 1 < m_nodes.size())
		if (m_nodes[loc.y][loc.x+1] != nullptr)
		{
			neig.push_back(m_nodes[loc.y][loc.x+1]);
		}

	return neig;
}
//-----------------------------------------------------------------------------

std::vector<std::vector<Node*>> Graph::get_graph()
{
	return m_nodes;
}
//-----------------------------------------------------------------------------

Node* Graph::get_node(int i, int j)
{
	return m_nodes[i][j];
}
//-----------------------------------------------------------------------------