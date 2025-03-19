
#include <iostream>
#include "GUI.hpp"

using namespace std;

GUI Gui;

TypeDataStructure CurrentStruture = MENU;



void GUI::Start() {

	InitWindow(ScreenWidth, ScreenHeight, "Data Stucture Visulization");

	SetTargetFPS(60);

	while (WindowShouldClose() == false) {


		BeginDrawing();
		ClearBackground(GREEN);
		if (CurrentStruture == MENU) {
			Gui.DrawMainMenu();
		}

		else if (CurrentStruture == HASHTABLE) {
			Gui.DrawHashTable();
		}

		else if (CurrentStruture == LINKEDLIST) {
			Gui.DrawLinkedList();
		}

		else if (CurrentStruture == AVLTREE) {
			Gui.DrawAVLTree();
		}

		else if (CurrentStruture == GRAPH) {
			Gui.DrawGraph();
		}



		EndDrawing();
	}

	CloseWindow();
}

void GUI::DrawMainMenu() {
	DrawText("Choose Data Structure", ScreenWidth * float(2) / 5, ScreenHeight * float(5) / 6, 40, WHITE);

	Rectangle HASHTABLEBUTTON = { ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	Rectangle LINKEDLISTBUTTON = { ScreenWidth * float(3) / 5, ScreenHeight * float(1) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	Rectangle AVLTREEBUTTON = { ScreenWidth * float(1) / 5, ScreenHeight * float(3) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	Rectangle GRAPHBUTTON = { ScreenWidth * float(3) / 5, ScreenHeight * float(3) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	DrawRectangleRec(HASHTABLEBUTTON, DARKGRAY);
	DrawRectangleRec(LINKEDLISTBUTTON, DARKGRAY);
	DrawRectangleRec(AVLTREEBUTTON, DARKGRAY);
	DrawRectangleRec(GRAPHBUTTON, DARKGRAY);


	DrawText("HASHTABLE", ScreenWidth * float(1) / 5 + 20, ScreenHeight * float(1) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2, 20, WHITE);
	DrawText("LINKEDLIST", ScreenWidth * float(3) / 5 + 20, ScreenHeight * float(1) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2, 20, WHITE);
	DrawText("AVLTREE", ScreenWidth * float(1) / 5 + 20, ScreenHeight * float(3) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2, 20, WHITE);
	DrawText("GRAPH", ScreenWidth * float(3) / 5 + 20, ScreenHeight * float(3) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2, 20, WHITE);

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		Vector2 mouse = GetMousePosition();
		if (CheckCollisionPointRec(mouse, HASHTABLEBUTTON) == true) {

			CurrentStruture = HASHTABLE;

		}
		else if (CheckCollisionPointRec(mouse, LINKEDLISTBUTTON) == true) {

			CurrentStruture = LINKEDLIST;
		}

		else if (CheckCollisionPointRec(mouse, AVLTREEBUTTON) == true) {
			CurrentStruture = AVLTREE;
		}

		else if (CheckCollisionPointRec(mouse, GRAPHBUTTON) == true) {

			CurrentStruture = GRAPH;

		}
	}

}

void GUI::DrawSecondMenu() {
	DrawRectangle(0, ScreenHeight / 2, ScreenWidth / 5, ScreenHeight / 2, GRAY);
	buttoninit.DrawButton();
	buttoninsert.DrawButton();
	buttondelete.DrawButton();
	buttonsearch.DrawButton();

	if (buttoninsert.IsClick() == true) {
		Gui.ClickInsert = true;
	}
	if (Gui.ClickInsert == true) {
		DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, WHITE);
		int val = Gui.Input(SecondMenuWidth * float(1) / 3 + 120, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);

		if (val != -1) {
			Gui.ClickInsert = false;
		}
	}

}
void GUI::DrawHashTable() {

	Gui.DrawSecondMenu();
	Gui.DrawBack();
}

void GUI::DrawLinkedList() {
	Gui.DrawSecondMenu();
	Gui.DrawBack();
}

void GUI::DrawAVLTree() {
	Gui.DrawSecondMenu();
	Gui.DrawBack();
}

void GUI::DrawGraph() {
	Gui.DrawSecondMenu();
	Gui.DrawBack();
}

void GUI::DrawBack() {

	DrawText("Data Structure Visualization", ScreenWidth * float(2) / 5, 100, 40, WHITE);

	Rectangle BackButton = { 50, 50, 150, 50 };
	DrawRectangleRec(BackButton, RED);
	DrawText("Back", 100, 65, 30, WHITE);


	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		Vector2 mouse = GetMousePosition();
		if (CheckCollisionPointRec(mouse, BackButton)) {
			CurrentStruture = MENU;
		}
	}
}

int GUI::Input(int posX, int posY) {
	int key = GetCharPressed();
	while (key > 0) {
		if (key >= '0' && key <= '9') {
			inputstring += char(key);
		}
		key = GetCharPressed();
	}
	DrawText(inputstring.c_str(), posX, posY, 20, WHITE);

	if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) {
		if (inputstring == "") { return -1; }

		int val = std::stoi(inputstring);
		std::cout << "Input:" << val << std::endl;

		inputstring = "";

		return val;
	}

	if (IsKeyPressed(KEY_BACKSPACE) && !inputstring.empty()) {
		inputstring.pop_back();
	}

	return -1;
}

