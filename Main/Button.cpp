#include "Button.hpp"

ButtonInit buttoninit("Init", C[2]);
ButtonInsert buttoninsert("Insert", C[2]);
ButtonDelete buttondelete("Delete", C[2]);
ButtonSearch buttonsearch("Search", C[2]);
ButtonClear buttonclear("Clear", C[2]);
ButtonRandom buttonrandom("Random", WHITE);
ButtonLoadFile buttonloadfile("LoadFile", WHITE);
Button buttonvertex("Vertex", C[2]);
Button buttonedge("Edge", C[2]);
Button buttondijkstra("Dijkstra", C[2]);
Button buttonauto("Auto", C[2]);
Button buttonstep("Step", C[2]);
Button buttonnext("Next", C[2]);
Button buttonprev("Prev", C[2]);
Button buttonreturn("Return", C[2]);
Button buttonpause("Pause", C[2]);
Button buttonrun("Run", C[2]);
Button buttonfinal("Final", C[2]);

bool Button::IsCover() {
	return GetMouseX() >= this->coordinateX && GetMouseX() <= this->coordinateX + this->width && GetMouseY() >= this->coordinateY && GetMouseY() <= this->coordinateY + this->height;
}

Button::Button(string s, Color color) {
	this->coordinateX = 0;
	this->coordinateY = 0;
	this->height = 0;
	this->width = 0;
	this->color = color;
	this->s = s;
}

void Button::DrawButton() {
	//Font custom = LoadFont("../../Data-Structure-Visualization/assets/PublicSans-Bold.ttf");
	int textWidth = MeasureText(this->s.c_str(), 20);
	int centerX = this->coordinateX + (this->width - textWidth) / 2;
	int centerY = this->coordinateY + (this->height - 20) / 2;

	Color drawColor = this->color;

	if (IsCover() == true) {
		drawColor = Color{
			(unsigned char)(color.r * 0.7f),
			(unsigned char)(color.g * 0.7f),
			(unsigned char)(color.b * 0.7f),
			color.a
		};
	}
	Rectangle rectange = { coordinateX, coordinateY, width, height };
	DrawRectangleRounded(rectange, 0.3f, 100, drawColor);
	DrawText(this->s.c_str(), centerX, centerY, 20, C[0]);
}

bool Button::IsClick() {
	Vector2 mouse = GetMousePosition();
	Rectangle rectange = { coordinateX, coordinateY, width, height };
	return (CheckCollisionPointRec(mouse, rectange) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}

void Button::setColor(Color color) {
	this->color = color;
}

void Button::DrawClickEffect() {
	DrawLineEx({ coordinateX + 10, coordinateY + 15 }, { coordinateX + 10, coordinateY + height - 15 }, 4.0f, DARKBLUE);
}

void Button::ConfigureButton(float position) {
	const float MENU_WIDTH = ScreenWidth / 5.0f;
	const float MENU_HEIGHT = ScreenHeight;

	const float BUTTON_WIDTH = MENU_WIDTH * 0.85f;
	const float BUTTON_HEIGHT = 30.0f;
	const float BUTTON_MARGIN_X = MENU_WIDTH * 0.075f;
	const float BUTTON_SPACING = 15.0f;
	//const float BUTTON_START_Y = MENU_HEIGHT / 8;
	const float BUTTON_START_Y = 20 + 60;

	this->coordinateX = BUTTON_MARGIN_X;
	this->coordinateY = BUTTON_START_Y + position * (BUTTON_HEIGHT + BUTTON_SPACING);
	this->width = BUTTON_WIDTH;
	this->height = BUTTON_HEIGHT;
	this->color = C[2];
	this->DrawButton(); 
}