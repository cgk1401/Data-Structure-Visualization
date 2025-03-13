
#include <iostream>
#include "GUI.hpp"
#include <raylib.h>
#include "Config.hpp"


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

void GUI::DrawHashTable() {
	Gui.DrawBack();
}

void GUI::DrawLinkedList() {
	Gui.DrawBack();
}

void GUI::DrawAVLTree() {
	Gui.DrawBack();
}

void GUI::DrawGraph() {
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

