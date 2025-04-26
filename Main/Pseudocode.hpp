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
        "Insert:",
        "Check Balance Factor :",
        "    Rotation Right",
        "    Rotation Left",
        "    Roation Left - Right",
        "    Rotation Right - Left",
    };
    vector <string> linesearch;
    vector <string> linedelete;

    // Pseudocode cho HashTable
    vector<string> lineinsert_hashtable = {
        "Insert:",
        "Compute index = key % capacity",
        "If slot is occupied, probe next",
        "Insert key into empty/deleted slot"
    };

    vector<string> linesearch_hashtable = {
        "Search:",
        "Compute index = key % capacity",
        "Probe until key is found",
        "Return index or -1 if not found"
    };

    vector<string> linedelete_hashtable = {
        "Delete:",
        "Compute index = key % capacity",
        "Probe until key is found",
        "Mark slot as deleted"
    };

    vector <string> line;
    float highlightline = -1;

    const float MENU_WIDTH = ScreenWidth / 5.0f;
    const float Height_Area = 175.0f; // Tăng để chứa ~7 dòng (7 * 25px)
    const float Weigh_Area = MENU_WIDTH * 0.85f;
    const float Coordinate_X_Area = MENU_WIDTH * 0.075f;
    // Đặt Y ngay dưới nút Next
    const float Coordinate_Y_Area = 20.0f + 28.0f + 20.0f + 9 * (40.0f + 15.0f) + 30.0f; // titleY + titleSize + margin + 9 buttons + spacing
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