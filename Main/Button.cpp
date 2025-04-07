#include "Button.hpp"

//SecondMenuHeight * 1 / 6
ButtonInit buttoninit(20, SecondMenuHeight + SecondMenuHeight * float(1) / 6, SecondMenuWidth* float(1) / 3, SecondMenuHeight * 1 / 6, "Init", C[2]);
ButtonInsert buttoninsert(20, SecondMenuHeight + SecondMenuHeight * float(2) / 6, SecondMenuWidth* float(1) / 3, SecondMenuHeight * 1 / 6, "Insert", C[2]);
ButtonDelete buttondelete(20, SecondMenuHeight + SecondMenuHeight * float(3) / 6, SecondMenuWidth* float(1) / 3, SecondMenuHeight * 1 / 6, "Delete", C[2]);
ButtonSearch buttonsearch(20, SecondMenuHeight + SecondMenuHeight * float(4) / 6, SecondMenuWidth* float(1) / 3, SecondMenuHeight * 1 / 6, "Search", C[2]);
ButtonClear buttonclear(20, SecondMenuHeight + SecondMenuHeight * float(5) / 6, SecondMenuWidth* float(1) / 3, SecondMenuHeight * 1 / 6, "Clear", C[2]);

ButtonRandom buttonrandom(20 + SecondMenuWidth * float(1) / 3 + 50, SecondMenuHeight + SecondMenuHeight * float(1) / 6 + 50, SecondMenuWidth* float(1) / 3, 80, "Random", C[2]);
ButtonLoadFile buttonloadfile(20 + SecondMenuWidth * float(1) / 3 + 50, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + 50, SecondMenuWidth* float(1) / 3, 80, "LoadFile", C[2]);

Button buttonvertex(20 + SecondMenuWidth * float(1) / 3 + 50, SecondMenuHeight + SecondMenuHeight * float(1) / 6 + 50, SecondMenuWidth* float(1) / 3, 80, "Vertex", C[2]);
Button buttonedge(20 + SecondMenuWidth * float(1) / 3 + 50, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + 50, SecondMenuWidth* float(1) / 3, 80, "Edge", C[2]);

Button buttondijkstra(20, SecondMenuHeight + SecondMenuHeight * float(4) / 6, SecondMenuWidth* float(1) / 3, SecondMenuHeight * 1 / 6, "Dijkstra", C[2]);
//20, SecondMenuHeight + SecondMenuHeight * float(3) / 6, SecondMenuWidth* float(1) / 3, 90,

Button::Button(float coordinateX, float coordinateY, float width, float height, string s, Color color) {
	this->coordinateX = coordinateX;
	this->coordinateY = coordinateY;
	this->width = width;
	this->height = height;
	this->s = s;
	this->color = color;

	//Font customFont = LoadFont("../../Data-Structure-Visualization/assets/PublicSans-Bold.ttf");
}

bool Button::IsCover() {
	return GetMouseX() >= this->coordinateX && GetMouseX() <= this->coordinateX + this->width && GetMouseY() >= this->coordinateY && GetMouseY() <= this->coordinateY + this->height;
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

void Button::DrawClickEffect(){
	DrawLineEx({ coordinateX + 10, coordinateY + 15}, { coordinateX + 10, coordinateY + height - 15 }, 4.0f, DARKBLUE);
}

void Button::ConfigureButton(int position) {
	const float MENU_WIDTH = ScreenWidth / 5.0f;
	const float MENU_HEIGHT = ScreenHeight;

	const float BUTTON_WIDTH = MENU_WIDTH * 0.85f;
	const float BUTTON_HEIGHT = 40.0f;
	const float BUTTON_MARGIN_X = MENU_WIDTH * 0.075f;
	const float BUTTON_SPACING = 15.0f;
	const float BUTTON_START_Y = MENU_HEIGHT / 8;

	this->coordinateX = BUTTON_MARGIN_X;
	this->coordinateY = BUTTON_START_Y + position * (BUTTON_HEIGHT + BUTTON_SPACING);
	this->width = BUTTON_WIDTH;
	this->height = BUTTON_HEIGHT;
	this->color = C[2];
	this->DrawButton(); 
}