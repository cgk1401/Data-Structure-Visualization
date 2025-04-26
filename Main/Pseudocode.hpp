#ifndef PSEUDOCODE_HPP
#define PSEUDOCODE_HPP
#include "Config.hpp"
#include <vector>
#include <iostream>
using namespace std;


class Pseudocode {
public:
	string text = "";
	vector <string> lineinsert = {
		"Insert: ",
		"Check Balance Factor :",
		"Rotation Right",
		"Rotation Left",
		"Roation Left - Right",
		"Rotation Right - Left",
	};

	vector <string> linesearch = {
		"Search: ",
		"Found",
		"Not found"
	};

	vector <string> linedelete = {
		"Delete: ",
		"Find node to delete",
		"Node is a leaf -> remove directly",
		"One child -> replace with child",
		"Two children -> ",
		"replace with inorder successor"
	};

	vector <string> line;

	float highlightline = -1;

	const float MENU_WIDTH = ScreenWidth / 5.0f;
	const float Height_Area = 380.0f;
	const float Weigh_Area = MENU_WIDTH * 0.85f;
	const float Coordinate_X_Area = MENU_WIDTH * 0.075f;
	const float Coordinate_Y_Area = (20 + 60  /*Start position Button Init*/) + 8.3 * (30 + 15) + 115; /*position * (BUTTON_HEIGHT + BUTTON_SPACING)*/
	Color color_area = C[1];


	Rectangle area_text{
		Coordinate_X_Area,
		Coordinate_Y_Area,
		Weigh_Area,
		Height_Area,
	};

	void SetstringPseudocode(string text) { this->text = text; }
	void DrawPseudocode();
	void SetHighLight(int highlightline) { this->highlightline = highlightline; }
};

#endif // !PSEUDOCODE_HPP

