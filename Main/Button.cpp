#include "Button.hpp"

<<<<<<< HEAD
ButtonInit buttoninit(20, SecondMenuHeight + SecondMenuHeight * float(1) / 6, SecondMenuWidth* float(1) / 3, 90, "Init", RED); //SecondMenuHeight * 1 / 6
ButtonInsert buttoninsert(20, SecondMenuHeight + SecondMenuHeight * float(2) / 6, SecondMenuWidth* float(1) / 3, 90, "Insert", BLUE);
ButtonDelete buttondelete(20, SecondMenuHeight + SecondMenuHeight * float(4) / 6, SecondMenuWidth* float(1) / 3, 90, "Delete", PINK);
ButtonSearch buttonsearch(20, SecondMenuHeight + SecondMenuHeight * float(3) / 6, SecondMenuWidth* float(1) / 3, 90, "Search", DARKBLUE);
ButtonRandom buttonrandom(20 + SecondMenuWidth * float(1) / 3 + 50, SecondMenuHeight + SecondMenuHeight * float(1) / 6 + 50, SecondMenuWidth* float(1) / 3, 80, "Random", BLUE);
ButtonLoadFile buttonloadfile(20 + SecondMenuWidth * float(1) / 3 + 50, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + 50, SecondMenuWidth* float(1) / 3, 80, "LoadFile", BLUE);

//20, SecondMenuHeight + SecondMenuHeight * float(3) / 6, SecondMenuWidth* float(1) / 3, 90,
=======
ButtonInit buttoninit(0, SecondMenuHeight + SecondMenuHeight * float(1) / 6, SecondMenuWidth* float(1) / 3, SecondMenuHeight * 1 / 6, "Init", C[2]);
ButtonInsert buttoninsert(0, SecondMenuHeight + SecondMenuHeight * float(2) / 6, SecondMenuWidth* float(1) / 3, SecondMenuHeight * 1 / 6, "Insert", C[2]);
ButtonDelete buttondelete(0, SecondMenuHeight + SecondMenuHeight * float(3) / 6, SecondMenuWidth* float(1) / 3, SecondMenuHeight * 1 / 6, "Delete", C[2]);
ButtonSearch buttonsearch(0, SecondMenuHeight + SecondMenuHeight * float(4) / 6, SecondMenuWidth* float(1) / 3, SecondMenuHeight * 1 / 6, "Search", C[2]);
ButtonClear buttonclear(0, SecondMenuHeight + SecondMenuHeight * float(5) / 6, SecondMenuWidth* float(1) / 3, SecondMenuHeight * 1 / 6, "Clear", C[2]);

>>>>>>> LinkedList
Button::Button(float coordinateX, float coordinateY, float width, float height, string s, Color color) {
	this->coordinateX = coordinateX;
	this->coordinateY = coordinateY;
	this->width = width;
	this->height = height;
	this->s = s;
	this->color = color;
}

<<<<<<< HEAD
bool Button::IsCover() {
	return GetMouseX() >= this->coordinateX && GetMouseX() <= this->coordinateX + this->width && GetMouseY() >= this->coordinateY && GetMouseY() <= this->coordinateY + this->height;
}
=======

>>>>>>> LinkedList
void Button::DrawButton() {
	int textWidth = MeasureText(this->s.c_str(), 20);
	int centerX = this->coordinateX + (this->width - textWidth) / 2;
	int centerY = this->coordinateY + (this->height - 20) / 2;

<<<<<<< HEAD
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
	//DrawRectangle(coordinateX, coordinateY, width, height, drawColor);
	DrawText(this->s.c_str(), centerX, centerY, 20, WHITE);

}



=======

	DrawRectangle(coordinateX, coordinateY, width, height, color);
	DrawText(this->s.c_str(), centerX, centerY, 20, C[0]);

}

>>>>>>> LinkedList
bool Button::IsClick() {
	Vector2 mouse = GetMousePosition();
	Rectangle rectange = { coordinateX, coordinateY, width, height };
	return (CheckCollisionPointRec(mouse, rectange) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
<<<<<<< HEAD
}
=======
}
void Button::setColor(Color color) {
	this->color = color;
}


>>>>>>> LinkedList
