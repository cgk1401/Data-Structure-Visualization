#include "Button.hpp"

ButtonInit buttoninit(0, SecondMenuHeight + SecondMenuHeight * float(1) / 6, SecondMenuWidth* float(1) / 3, SecondMenuHeight * 1 / 6, "Init", RED);
ButtonInsert buttoninsert(0, SecondMenuHeight + SecondMenuHeight * float(2) / 6, SecondMenuWidth* float(1) / 3, SecondMenuHeight * 1 / 6, "Insert", BLUE);
ButtonDelete buttondelete(0, SecondMenuHeight + SecondMenuHeight * float(3) / 6, SecondMenuWidth* float(1) / 3, SecondMenuHeight * 1 / 6, "Delete", PINK);
ButtonSearch buttonsearch(0, SecondMenuHeight + SecondMenuHeight * float(4) / 6, SecondMenuWidth* float(1) / 3, SecondMenuHeight * 1 / 6, "Search", DARKBLUE);

Button::Button(float coordinateX, float coordinateY, float width, float height, string s, Color color) {
	this->coordinateX = coordinateX;
	this->coordinateY = coordinateY;
	this->width = width;
	this->height = height;
	this->s = s;
	this->color = color;
}


void Button::DrawButton() {
	int textWidth = MeasureText(this->s.c_str(), 20);
	int centerX = this->coordinateX + (this->width - textWidth) / 2;
	int centerY = this->coordinateY + (this->height - 20) / 2;


	DrawRectangle(coordinateX, coordinateY, width, height, color);
	DrawText(this->s.c_str(), centerX, centerY, 20, WHITE);

}

bool Button::IsClick() {
	Vector2 mouse = GetMousePosition();
	Rectangle rectange = { coordinateX, coordinateY, width, height };
	return (CheckCollisionPointRec(mouse, rectange) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}


