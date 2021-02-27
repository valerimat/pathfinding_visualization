#pragma once
#include <functional>

enum TextureName
{
	RESET,
	START,
	END_PNT,
	START_PNT,
	WALL_PNT,
	DELETE_PNT,
};

enum AnimationTypes
{
	KeepPressed,
	ResetOnRelease,
};

enum ButtonType
{
	RESET_BUTTON,
	START_BUTTON,
	ADD_END,
	ADD_START,
	ADD_WALL,
	ADD_NONE,
	NONE_B,
};

enum Color {
		WHITE,
		BLACK,
		GREY
};

enum Algorithm
{
	A_BFS = 1,
	A_DFS = 2,
	A_Dijiksra = 3,
	A_Astar = 4
};

const char NONE = ' ';
const char START_CHAR = '@';
const char END = '$';
const char WALL = '#';
const char GREY_NODE = '*';
const char BLACK_NODE = '$';

//those wont change
const int NUMBER_OF_BUTTONS = 6;
const float BASE_BUTTON_HEIGHT = 50.f;
const float BASE_BUTTON_WIDTH = 50.f;


typedef std::function<void* (void*)>ButtonTask;