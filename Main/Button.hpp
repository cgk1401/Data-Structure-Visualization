#ifndef BUTTON_HPP  
#define BUTTON_HPP  
using namespace std;
#include <iostream>
#include <string>
#include "raylib.h"
#include "Config.hpp"



class Button {

public:
	float coordinateX;
	float coordinateY;
	float width;
	float height;
	Color color;
	string s;


	Button(float coordinateX, float coordinateY, float width, float height, string s, Color color);
	void DrawButton();
	bool IsCover();
	bool IsClick();
};
class ButtonInit : public Button {
public:
	ButtonInit(float coordinateX, float coordinateY, float width, float height, string s, Color color) : Button(coordinateX, coordinateY, width, height, s, color) {};
};
class ButtonInsert : public Button {
public:
	ButtonInsert(float coordinateX, float coordinateY, float width, float height, string s, Color color) : Button(coordinateX, coordinateY, width, height, s, color) {};
};

class ButtonDelete : public Button {
public:
	ButtonDelete(float coordinateX, float coordinateY, float width, float height, string s, Color color) : Button(coordinateX, coordinateY, width, height, s, color) {};
};
class ButtonSearch : public Button {
public:
	ButtonSearch(float coordinateX, float coordinateY, float width, float height, string s, Color color) : Button(coordinateX, coordinateY, width, height, s, color) {};
};

extern ButtonInit buttoninit;
extern ButtonInsert buttoninsert;
extern ButtonDelete buttondelete;
extern ButtonSearch buttonsearch;




#endif // BUTTON_HPP
