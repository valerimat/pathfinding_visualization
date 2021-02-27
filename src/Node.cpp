#include "Node.h"

//ctors:
Node::Node(sf::Vector2i location):
	m_location(location)
{
}
//----------------------------------------------------------------------------_

//Getters:
Color Node::get_color()
{
	return m_color;
}
//-----------------------------------------------------------------------------

sf::Vector2i Node::get_location()
{
	return m_location;
}
//-----------------------------------------------------------------------------

void * Node::get_data()
{
	return m_data;
}
//-----------------------------------------------------------------------------

Node* Node::get_father()
{
	return m_father;
}
//-----------------------------------------------------------------------------

std::vector<Node*> Node::get_neighboor_list()
{
	return neighbor_list;
}
//-----------------------------------------------------------------------------

//Setters:
void Node::set_color()
{
	switch (m_color)
	{
	case WHITE:
		m_color = GREY;
		break;
	case BLACK:
		break;
	case GREY:
		m_color = BLACK;
		break;
	default:
		break;
	}
}
//-----------------------------------------------------------------------------

void Node::set_father(Node* father)
{
	m_father = father;
}
//-----------------------------------------------------------------------------

void Node::set_neigbor_list(std::vector<Node*> nodes)
{
	neighbor_list = nodes;
}
//-----------------------------------------------------------------------------

void Node::set_data(void * data)
{
	m_data = data;
}
//-----------------------------------------------------------------------------
