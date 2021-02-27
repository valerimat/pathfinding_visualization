#include <iostream>
#include <functional>

#include "UI.h"
#include "Textures.h"
#include "Settings.h"
#include "Board.h"
#include "BFS.h"
#include "Astar.h"
#include "Dijkstra.h"
#include "DFS.h"
#include "Algo.h"


//Ctors:
UI::UI(Algorithm algo_name, Board* board) :
	m_board(board)
{
	set_algo(algo_name);
	create_lamdas();
	load_components();	
}
//----------------------------------------------------------------------------

//Dtors:
UI::~UI()
{
	delete m_algo;
}
//----------------------------------------------------------------------------

//On load:
void UI::load_components()
{
	load_background();
	load_buttons();
}
//----------------------------------------------------------------------------

void UI::set_algo(Algorithm algo_name)
{
	
	switch (algo_name)
	{
	case A_BFS:
		m_algo = new BFS();
		break;
	case A_DFS:
		m_algo = new DFS();
		break;
	case A_Dijiksra:
		m_algo = new Dijikstra();
		break;
	case A_Astar:
		m_algo = new Astar();
		break;
	default:
		break;
	}
}
//----------------------------------------------------------------------------

void UI::load_background()
{
	//using settings:
	auto& settings = Settings::get_settings();
	//no need but for safety:
	m_background_rect.setPosition(sf::Vector2f(0, 0));

	//settign ui size to be of the height of the window and width of 20%
	sf::Vector2f size(settings.get_window_width() * 0.2, settings.get_window_height());

	m_background_rect.setSize(size);

	m_background_rect.setFillColor(sf::Color(124, 124, 124, 255));
}
//----------------------------------------------------------------------------

void UI::load_buttons()
{
	auto& settings = Settings::get_settings();
	auto& textures = Textures::get_textures();

	float height_for_each = settings.get_window_height() / NUMBER_OF_BUTTONS;

	float offset_y = height_for_each - BASE_BUTTON_HEIGHT * settings.get_scale();

	offset_y /= 2;

	float offset_x = 0.1f * settings.get_window_width() - BASE_BUTTON_WIDTH * settings.get_scale();

	offset_x /= 2;

	for (int i = 0; i < NUMBER_OF_BUTTONS; ++i)
	{
		sf::Vector2f loc(offset_x, i * height_for_each + offset_y);
		sf::Vector2f scale(settings.get_scale(), settings.get_scale());

		if (i < 2)
			m_buttons.push_back(std::make_unique<Button>
			(m_lambdas[i], textures.get_texture((TextureName(i))), loc, scale, ResetOnRelease));
		else
			m_buttons.push_back(std::make_unique<Button>
			(m_lambdas[i], textures.get_texture((TextureName(i))), loc, scale, KeepPressed));
	}

}
//----------------------------------------------------------------------------

//Button related:
void UI::do_action(ButtonType type, sf::RenderWindow& window)
{

	switch (type)
	{
	case RESET_BUTTON:
		m_selected = NONE_B;
		m_board->reset();
		break;
	case START_BUTTON:
		m_selected = NONE_B;
		m_algo->do_algo(window, m_board);
		break;
	case ADD_END:
		if (m_selected == ADD_END)
		{
			m_selected = NONE_B;
			//RESET ANIMATION
			break;
		}
		m_selected = ADD_END;
		break;
	case ADD_START:
		if (m_selected == ADD_START)
		{
			m_selected = NONE_B;
			//RESET ANIMATION
			break;
		}
		m_selected = ADD_START;
		break;
	case ADD_WALL:
		if (m_selected == ADD_WALL)
		{
			m_selected = NONE_B;
			//RESET ANIMATION
			break;
		}
		m_selected = ADD_WALL;
		break;
	case ADD_NONE:
		if (m_selected == ADD_NONE)
		{
			m_selected = NONE_B;
			//RESET ANIMATION
			break;
		}
		m_selected = ADD_NONE;
		break;
	default:
		break;
	}
	m_board->set_selected(m_selected);
}
//----------------------------------------------------------------------------

void UI::check_pressed(sf::Vector2f& location, sf::RenderWindow& window)
{
	for (int i = 0; i < NUMBER_OF_BUTTONS; ++i)
	{
		if (m_buttons[i]->get_sprite().getGlobalBounds().contains(location))
		{
			ButtonType type = (*(ButtonType*)m_buttons[i]->on_click(NULL));
			do_action(type, window);
			m_pressed_index = i;
		}
	}
}
//----------------------------------------------------------------------------

void UI::create_lamdas()
{
	//for learning how to use lambadas no real use case here:
	m_lambdas.push_back([](void* args) {ButtonType* type = new ButtonType(RESET_BUTTON);
	return (void*)type; });
	m_lambdas.push_back([](void* args) {ButtonType* type = new ButtonType(START_BUTTON);
	return (void*)type; });
	m_lambdas.push_back([](void* args) {ButtonType* type = new ButtonType(ADD_END);
	return (void*)type; });
	m_lambdas.push_back([](void* args) {ButtonType* type = new ButtonType(ADD_START);
	return (void*)type; });
	m_lambdas.push_back([](void* args) {ButtonType* type = new ButtonType(ADD_WALL);
	return (void*)type; });
	m_lambdas.push_back([](void* args) {ButtonType* type = new ButtonType(ADD_NONE);
	return (void*)type; });
}
//----------------------------------------------------------------------------

//Draw:
void UI::draw(sf::RenderWindow& window)
{
	//draw backgroud:
	window.draw(m_background_rect);

	//draw buttons:
	for (int i = 0; i < NUMBER_OF_BUTTONS; ++i)
	{
		m_buttons[i]->draw(window);
	}
}
//----------------------------------------------------------------------------



