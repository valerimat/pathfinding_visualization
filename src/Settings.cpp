#include "Settings.h"

Settings::Settings() :
	m_window_width(1200), m_window_height(600)
{};


//Getters:
float Settings::get_window_height()
{
	return m_window_height;
}

float Settings::get_window_width()
{
	return m_window_width;
}

float Settings::get_scale()
{
	return m_scale;
}

//Setter:
void Settings::set_window_height(float height)
{
	m_window_height = height;
}

void Settings::set_window_width(float width)
{
	m_window_width = width;
}

void Settings::set_scale(float scale)
{
	m_scale = scale;
}