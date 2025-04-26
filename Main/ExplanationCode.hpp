#ifndef EXPLANATIONCODE_HPP
#define EXPLANATIONCODE_HPP

#include <iostream>
#include <raylib.h>
#include <sstream>
#include <vector>
#include "Config.hpp"
using namespace std;

class ExplanationCode {
public:
    string text = "";
    vector<string> lines_insert = {
    "Select an operation to begin.",
    "Calculating index for the value.",
    "Probing linearly due to collision.",
    "Value inserted into slot."
    };

    vector<string> lines_search = {
        "Select an operation to begin.",
        "Calculating index for the value.",
        "Probing linearly to find value.",
        "Value found."
    };

    vector<string> lines_delete = {
        "Select an operation to begin.",
        "Calculating index for the value.",
        "Probing linearly to delete.",
        "Value deleted from slot."
    };

    vector<string> lines_init = {
        "Select an operation to begin.",
        "Initializing new table.",
        "Generating random table.",
        "Loading table from file."
    };
    vector<string> lines;

    float highlightline = -1;

    const float MENU_WIDTH = ScreenWidth / 5.0f;
    const float Height_Area = 100.0f;
    const float Weigh_Area = MENU_WIDTH * 0.85f;
    const float Coordinate_X_Area = MENU_WIDTH * 0.075f;
	const float Coordinate_Y_Area = (20 + 60  /*Start position Button Init*/) + 8.3 * (30 + 15); /*position * (BUTTON_HEIGHT + BUTTON_SPACING)*/
	Color color_area = C[1];

    Rectangle area_text{
        Coordinate_X_Area,
        Coordinate_Y_Area,
        Weigh_Area,
        Height_Area,
    };

    void Setstringexplancode(string text) { this->text = text; }
    void SetHighLight(int highlightline) { this->highlightline = highlightline; }
    void DrawExplancodeArea();
	
};

#endif // !EXPLANATIONCODE_HPP