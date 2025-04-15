#include "ExplanationCode.hpp"

void ExplanationCode::DrawExplancodeArea() {
	DrawRectangleRounded(this->area_text, 0.3f, 100, C[2]);
	int fontsize = 20;
	int textwidth = MeasureText(this->text.c_str(), fontsize);
	int texthight = fontsize;
	float centerX = this->area_text.x + (this->area_text.width - textwidth) / 2;
	float centerY = this->area_text.y + (this->area_text.height - texthight) / 2;
	DrawText(this->text.c_str(), centerX, centerY, fontsize, WHITE);
}
