#pragma once
//Singelton class to handle setting and calculations for diffrent sizes
//Might wanna move sizes to diff class that uses settings

class Settings
{
public:
	// get singleton
	static Settings& get_settings() { static Settings s_settings; return s_settings; };

	//getters:
	float get_window_height();
	float get_window_width();
	float get_scale();

	//setters:
	void set_window_width(float width);
	void set_window_height(float width);
	void set_scale(float scale);


private:
	// c-tor
	Settings();

	// avoids copy 
	Settings(const Settings&) = delete;
	void operator=(Settings const&) = delete;


	//members:
	float m_window_width = 0;
	float m_window_height = 0;
	float m_scale = 1;
};
