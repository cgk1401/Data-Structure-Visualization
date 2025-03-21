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
		//0, 255, 255, 255
		//{ 50, 200, 110, 150 }
		ClearBackground({80, 220, 220, 150 });
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

	//DrawRectangleRec(HASHTABLEBUTTON, DARKGRAY);
	//DrawRectangleRec(LINKEDLISTBUTTON, DARKGRAY);
	//DrawRectangleRec(AVLTREEBUTTON, DARKGRAY);
	//DrawRectangleRec(GRAPHBUTTON, DARKGRAY);

	DrawRectangleRounded(HASHTABLEBUTTON, 0.3f, 10, DARKGRAY);
	DrawRectangleRounded(LINKEDLISTBUTTON, 0.3f, 10, DARKGRAY);
	DrawRectangleRounded(AVLTREEBUTTON, 0.3f, 10, DARKGRAY);
	DrawRectangleRounded(GRAPHBUTTON, 0.3f, 10, DARKGRAY);

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
	DrawRectangle(0, ScreenHeight / 2, ScreenWidth / 5, ScreenHeight / 2, RAYWHITE);
	buttoninit.DrawButton();
	buttoninsert.DrawButton();
	buttondelete.DrawButton();
	buttonsearch.DrawButton();
	//buttonrandom.DrawButton();
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

	if (buttoninit.IsClick() == true) {
		Gui.ClickInit_AVLTree = true;
		Gui.ClickInitEnter_AVLTree = true;
		

		Gui.ClickInsert_AVLTree = false;
		Gui.ClickInsertEnter_AVLTree = false;

		Gui.ClickSearch_AVLTree = false;
		Gui.ClickSearchEnter_AVLTree = false;

		Gui.ClickDelete_AVLTree = false;
		Gui.ClickDeleteEnter_AVLTree = false;
	}

	if (Gui.ClickInit_AVLTree == true) {
		buttonrandom.DrawButton();
		buttonloadfile.DrawButton();
		if (buttonrandom.IsClick() == true) {
			if (Gui.ClickRandom_AVLTree == true) {
				// nút random đã được bấm trước đó => resert lại cây
				tree.Clear(tree.Root);
				tree.NodeList.clear();
				tree.Random();
				tree.DrawTree();
			}
			else {
				// nút random chưa được bấm trước đó
				tree.Random();
			}
			Gui.ClickRandom_AVLTree = true;
		}
		if (buttonloadfile.IsClick() == true) {
			if (Gui.LoadFileAVLTree() == true) Gui.ClickLoadFile_AVLTree = true;
		}
	}

	if (Gui.ClickRandom_AVLTree == true) tree.DrawTree();
	if (Gui.ClickLoadFile_AVLTree == true) tree.DrawTree();

	if (buttoninsert.IsClick() == true) {
		Gui.ClickInsert_AVLTree = true;
		Gui.ClickInsertEnter_AVLTree = true;

		Gui.ClickInit_AVLTree = false;
		//Gui.ClickInitEnter_AVLTree = false;
		Gui.ClickRandom_AVLTree = false;
		Gui.ClickLoadFile_AVLTree == true;

		Gui.ClickSearch_AVLTree = false;
		Gui.ClickSearchEnter_AVLTree = false;

		Gui.ClickDelete_AVLTree = false;
		Gui.ClickDeleteEnter_AVLTree = false;
	}

	if (Gui.ClickInsert_AVLTree == true) {
		DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, BLACK);
		int value = Gui.Input(SecondMenuWidth * float(1) / 3 + 120, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);
		if (value != -1) {
			tree.Insert(tree.Root, value, tree.NodeList);
			Gui.ClickInsert_AVLTree = false;
			Gui.ClickInsertEnter_AVLTree = true;
		}
	}
	

	if (Gui.ClickInsertEnter_AVLTree == true) tree.DrawTree();



	Gui.DrawBack();
}

void GUI::DrawGraph() {
	Gui.DrawSecondMenu();
	Gui.DrawBack();
}

void GUI::DrawBack() {

	DrawText("Data Structure Visualization", ScreenWidth * float(2) / 5, 50, 40, WHITE);

	Rectangle BackButton = { 50, 50, 150, 50 };
	DrawRectangleRec(BackButton, RED);
	DrawText("Back", 100, 65, 30, WHITE);


	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		Vector2 mouse = GetMousePosition();
		if (CheckCollisionPointRec(mouse, BackButton)) {
			CurrentStruture = MENU;
			tree.Clear(tree.Root);
			tree.NodeList.clear();
		}
	}
}

bool GUI::LoadFileAVLTree() {
	const char* path = tinyfd_openFileDialog(
		"Open AVL File", "", 0, nullptr, nullptr, 0
	);
	if (path == nullptr) return false;

	ifstream ifs(path);

	if (ifs.is_open() == false) return false;

	tree.Clear(tree.Root);
	tree.NodeList.clear();

	int x; 
	while (ifs >> x) tree.Insert(tree.Root, x, tree.NodeList);

	ifs.close();
	return true;

}

int GUI::Input(int posX, int posY) {
	int key = GetCharPressed();
	while (key > 0) {
		if (key >= '0' && key <= '9') {
			inputstring += char(key);
		}
		key = GetCharPressed();
	}
	DrawText(inputstring.c_str(), posX, posY, 20, BLACK);

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