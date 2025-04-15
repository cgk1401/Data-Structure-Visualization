#ifndef EXPLANATIONCODE_HPP
#define EXPLANATIONCODE_HPP

#include <iostream>
#include <raylib.h>
#include "Config.hpp"
using namespace std;

class ExplanationCode {
public :
	string text = "";

	const float MENU_WIDTH = ScreenWidth / 5.0f;
	const float Height_Area = 100.0f;
	const float Weigh_Area = MENU_WIDTH * 0.85f;
	const float Coordinate_X_Area = MENU_WIDTH * 0.075f;
	const float Coordinate_Y_Area = (20 + 60 + 10 /*Start position Button Init*/) + 8.3 * (40 + 15); /*position * (BUTTON_HEIGHT + BUTTON_SPACING)*/
	Color color_area = C[1];


	Rectangle area_text{
		Coordinate_X_Area,
		Coordinate_Y_Area,
		Weigh_Area,
		Height_Area,
	};

	void Setstringexplancode(string text) { this->text = text; }
	void DrawExplancodeArea();
	
};

#endif // !EXPLANATIONCODE_HPP
