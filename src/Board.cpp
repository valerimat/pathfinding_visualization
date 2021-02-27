#include "Board.h"
#include "Settings.h"
//#include "Macros.h"

//Ctors:
Board::Board()
{
	reset_char_board();
	load_board();
}
//-----------------------------------------------------------------------------

//Draw:
void Board::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			window.draw(m_rects[i][j]);
		
		}
	}
	window.draw(m_hovered_over_rect);
}
//-----------------------------------------------------------------------------

//Setters:
void Board::set_width(int width)
{
	m_width = width;
}
//-----------------------------------------------------------------------------

void Board::set_height(int height)
{
	m_height = height;
}
//-----------------------------------------------------------------------------

//not used yet:
void Board::reset_size()
{

}
//-----------------------------------------------------------------------------

void Board::reset_char_board()
{
	m_data.resize(m_height);

	for (int i = 0; i < m_height; ++i)
		for (int j = 0; j < m_width; ++j)
		{
			m_data[i].resize(m_width);
			m_data[i][j] = NONE;
		}
}
//-----------------------------------------------------------------------------

void Board::reset()
{
	reset_char_board();
	load_board();
}
//-----------------------------------------------------------------------------

void Board::set_selected(ButtonType selected)
{
	m_selected = selected;
}
//-----------------------------------------------------------------------------

void Board::set_checked(sf::Vector2i loc)
{
	m_rects[loc.y][loc.x].setFillColor(sf::Color::Blue);
}
//-----------------------------------------------------------------------------

void Board::set_found(sf::Vector2i loc)
{
	m_rects[loc.y][loc.x].setFillColor(sf::Color::Yellow);
}
//-----------------------------------------------------------------------------

void Board::set_pending(sf::Vector2i loc)
{
	m_rects[loc.y][loc.x].setFillColor(sf::Color::Green);
}
//-----------------------------------------------------------------------------

//Getters:
sf::Vector2i Board::get_start()
{
	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			if (m_data[i][j] == START)
				return sf::Vector2i(j, i);
		}
	}
	return sf::Vector2i(-1, -1);
}
//-----------------------------------------------------------------------------

sf::Vector2i  Board::get_end()
{
	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			if (m_data[i][j] == END)
				return sf::Vector2i(j, i);
		}
	}
	return sf::Vector2i(-1, -1);
}
//-----------------------------------------------------------------------------

std::vector<std::vector <char>> Board::get_data()
{
	return m_data;
}
//-----------------------------------------------------------------------------

//loading:
void Board::load_board()
{
	//the correct size
	m_rects.resize(m_height);

	auto& settings = Settings::get_settings();
	//first we set size for one block:

	//We will want to devide the height of the window so the blocks will cover 90% of the window
	float block_size = size_of_block(m_height, settings.get_window_height());

	//the first block
	sf::Vector2f base = calc_alignment(m_width, settings.get_window_height(), settings.get_window_width());

	for (int i = 0; i < m_height; ++i)
	{
		m_rects[i].clear();
		for (int j = 0; j < m_width; ++j)
		{
			sf::RectangleShape block;
			block.setFillColor(sf::Color::White);
			block.setOutlineColor(sf::Color::Black);
			block.setOutlineThickness(2.f);
			block.setPosition(sf::Vector2f(base.x + j * block_size, base.y + i * block_size));
			block.setSize(sf::Vector2f(block_size, block_size));
			m_rects[i].push_back(block);
		}
	}
}
//-----------------------------------------------------------------------------

float Board::size_of_block(int num_of_blocks, float height)
{
	float ninety_prc = height * 0.9f;

	return ninety_prc / (float)num_of_blocks;
}
//-----------------------------------------------------------------------------

sf::Vector2f Board::calc_alignment(int width, float window_height, float window_width)
{
	float size = size_of_block(width, window_height);
	float y = 0.05f * window_height;

	//how much does the ui take
	float offset_x = 0.1f * window_width;
	//how much widthout the ui
	offset_x = window_width - offset_x;

	//without the blocks
	offset_x = offset_x - size * (float)width;

	//divide by 2 
	offset_x /= 2;

	float x = 0.1f * window_width + offset_x;

	return sf::Vector2f(x, y);
}
//-----------------------------------------------------------------------------

//Helpers:
void Board::check_hover(sf::Vector2f& location)
{
	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			if (m_rects[i][j].getGlobalBounds().contains(location))
			{
				m_hovered_over_rect = m_rects[i][j];

				switch (m_selected)
				{
				case ADD_END:
					m_hovered_over_rect.setFillColor(sf::Color(211, 47, 47, 200));
					break;
				case ADD_START:
					m_hovered_over_rect.setFillColor(sf::Color(76, 175, 80, 200));
					break;
				case ADD_WALL:
					m_hovered_over_rect.setFillColor(sf::Color(1, 1, 1, 200));
					break;
				case ADD_NONE:
					m_hovered_over_rect.setFillColor(sf::Color::White);
					break;
				default:
					break;
				}
				return;
			}
		}
	}

	sf::RectangleShape rect;
	m_hovered_over_rect = rect;
}
//-----------------------------------------------------------------------------

void Board::check_pressed(sf::Vector2f& location)
{
	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			if (m_rects[i][j].getGlobalBounds().contains(location))
			{
				switch (m_selected)
				{
				case ADD_END:
					m_rects[i][j].setFillColor(sf::Color(211, 47, 47, 255));
					if (m_end == nullptr)
					{
						m_end = &m_rects[i][j];
					}
					else
					{
						m_end->setFillColor(sf::Color::White);
						m_end = &m_rects[i][j];
					}
					m_data[i][j] = END;

					break;
				case ADD_START:
					m_rects[i][j].setFillColor(sf::Color(76, 175, 80, 255));
					if (m_start == nullptr)
					{
						m_start = &m_rects[i][j];
					}
					else
					{
						m_start->setFillColor(sf::Color::White);
						m_start = &m_rects[i][j];
					}
					m_data[i][j] = START;
					break;
				case ADD_WALL:
					m_rects[i][j].setFillColor(sf::Color(1, 1, 1, 255));
					m_data[i][j] = WALL;
					break;
				case ADD_NONE:
					if (m_rects[i][j].getFillColor() == sf::Color(76, 175, 80, 255))
						m_start = nullptr;
					if (m_rects[i][j].getFillColor() == sf::Color(211, 47, 47, 255))
						m_end = nullptr;

					m_rects[i][j].setFillColor(sf::Color::White);
					m_data[i][j] = NONE;
					break;
				default:
					break;
				}
			}
		}
	}
}
//-----------------------------------------------------------------------------


