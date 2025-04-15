#ifndef BUTTON_HPP  
#define BUTTON_HPP  

#include <iostream>
#include <string>
#include "raylib.h"
#include "Config.hpp"
using namespace std;

class Button {
public:
	float coordinateX;
	float coordinateY;
	float width;
	float height;
	Color color;
	string s;

	Button(string s, Color color);
	void DrawButton();
	bool IsCover();
	bool IsClick();
	void setColor(Color color);
	void DrawClickEffect();
	void ConfigureButton(float position);
};
class ButtonInit : public Button {
public:
	ButtonInit(string s, Color color) : Button(s, color) {};
};

class ButtonInsert : public Button {
public:
	ButtonInsert(string s, Color color) : Button(s, color) {};
};

class ButtonDelete : public Button {
public:
	ButtonDelete(string s, Color color) : Button(s, color) {};
};

class ButtonSearch : public Button {
public:
	ButtonSearch(string s, Color color) : Button(s, color) {};
};

class ButtonRandom : public Button {
public:
	ButtonRandom(string s, Color color) : Button(s, color) {};
};

class ButtonLoadFile : public Button {
public:
	ButtonLoadFile(string s, Color color) : Button(s, color) {};
};

class ButtonClear : public Button {
public:
	ButtonClear(string s, Color color) : Button(s, color) {};
};

extern ButtonInit buttoninit;
extern ButtonInsert buttoninsert;
extern ButtonDelete buttondelete;
extern ButtonSearch buttonsearch;
extern ButtonRandom buttonrandom;
extern ButtonLoadFile buttonloadfile;
extern ButtonClear buttonclear;
extern Button buttonvertex;
extern Button buttonedge;
extern Button buttondijkstra;
extern Button buttonauto;
extern Button buttonstep;
extern Button buttonnext;
extern Button buttonprev;
extern Button buttonreturn;
extern Button buttonpause;
extern Button buttonrun;

#endif // BUTTON_HPP
