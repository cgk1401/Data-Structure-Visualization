#include "ExplanationCode.hpp"

void ExplanationCode::DrawExplancodeArea() {
	DrawRectangleRounded(this->area_text, 0.3f, 100, C[2]);
	int fontsize = 20;
	int padding = 10.0f;
	float maxlength = this->area_text.width - 2 * padding;
	float lengthcurrentline = 0.0f;
	string word = "";
	string wraptext = "";
	for (char c : this->text) {
		if (c == ' ' || c == '\n') {
			int lengthword = MeasureText(word.c_str(), fontsize);
			if (lengthcurrentline + lengthword > maxlength) {
				lengthcurrentline = lengthword + MeasureText(" ", fontsize);
				wraptext += "\n" + word + (c == ' ' ? " " : "");
			}
			else {
				lengthcurrentline += lengthword + MeasureText(" ", fontsize);
				wraptext += word + (c == ' ' ? " " : "");

			}
			word = "";
		}
		else {
			word += c;
		}
	}
	if (!word.empty()) {
		int lengthword = MeasureText(word.c_str(), fontsize);
		if (lengthcurrentline + lengthword > maxlength) {
			wraptext += "\n" + word;
		}
		else {
			wraptext += word;
		}
	}
	int linecount = 0;
	for (int i = 0; i < wraptext.size(); i++) {
		if (wraptext[i] == '\n') linecount++;
	}
	linecount++;
	float lineheight = fontsize + 4;
	float totalheightline = lineheight * linecount;
	float startY = this->area_text.y + (this->area_text.height - totalheightline) / 2;
	istringstream iss(wraptext);
	string line = "";
	while (getline(iss, line)) {
		float textwidth = MeasureText(line.c_str(), fontsize);
		float startX = this->area_text.x + (this->area_text.width - textwidth) / 2;
		DrawText(line.c_str(), startX, startY, fontsize, WHITE);
		startY += lineheight;
	}
}
