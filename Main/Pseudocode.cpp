#include "Pseudocode.hpp"


void Pseudocode::DrawPseudocode() {
	if (text == "INSERT") line = lineinsert;
	else if (text == "SEARCH") line = linesearch;
	else if (text == "DELETE") line = linedelete;
	else if (text == "") line.clear();
	float lineheight = 40;
	float y = area_text.y + 20;
	DrawRectangleRounded(this->area_text, 0.1f, 100, C[2]);
	for (int i = 0; i < line.size(); i++) {
		if (i == highlightline) {
			DrawRectangle(area_text.x, y - 10, area_text.width, 35, BLACK);
		}
		DrawText(line[i].c_str(), area_text.x + 10, y, 20, WHITE);
		y += lineheight;
	}
}