
﻿#include <iostream>
#include "GUI.hpp"
<<<<<<< HEAD
#include<string>
#include"HashTable.hpp"

using namespace std;


HashTable myHashTable(10);
=======

using namespace std;

>>>>>>> d3ef482 (Fix gitignore and update demo menu)
GUI Gui;

TypeDataStructure CurrentStruture = MENU;


<<<<<<< HEAD
=======

>>>>>>> d3ef482 (Fix gitignore and update demo menu)
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

<<<<<<< HEAD

void GUI::DrawSecondMenu() {
    DrawRectangle(0, ScreenHeight / 2, ScreenWidth / 5, ScreenHeight / 2, GRAY);
    buttoninit.DrawButton();
    buttoninsert.DrawButton();
    buttondelete.DrawButton();
    buttonsearch.DrawButton();
	// Xử lý Insert
    if (buttoninsert.IsClick()) {
        Gui.ClickInsert = true;
    }
    if (Gui.ClickInsert) {
        DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40, 
                 SecondMenuHeight + SecondMenuHeight * float(2) / 6 + 
                 (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, WHITE);
        Gui.InputInsert();
    }

    // Xử lý Init
	if (buttoninit.IsClick()) {
		Gui.ClickInit = true;
	}
	if (Gui.ClickInit) {
		DrawText("Size : ", SecondMenuWidth * float(1) / 3 + 40,
			SecondMenuHeight + SecondMenuHeight * float(1) / 6 +
			(SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, WHITE);
		Gui.InputInit();
	}
	//Xử lý Delete
	if (buttondelete.IsClick() == true) {
		Gui.ClickDelete = true;
	}
	if (buttondelete.IsClick()) {
		Gui.ClickDelete = true;
		inputstring = "";  // Reset input để tránh lỗi nhập trước đó
	}
	if (Gui.ClickDelete) {
		DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40,
			SecondMenuHeight + SecondMenuHeight * float(3) / 6 +
			(SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, WHITE);
		Gui.InputDelete();
	}
	//Xử lý Delete
	if (buttonsearch.IsClick()) {
		Gui.ClickSearch = true;
		inputstring = "";  // Reset input để tránh lỗi nhập trước đó
	}
	if (Gui.ClickSearch) {
		DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40,
			SecondMenuHeight + SecondMenuHeight * float(4) / 6 +
			(SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, WHITE);
		Gui.InputSearch();
	}

}

void GUI::DrawHashTable() {
	Gui.DrawSecondMenu();
	myHashTable.drawHashTable();  // Gọi hàm vẽ Hash Table
}

void GUI::DrawLinkedList() {

	Gui.DrawSecondMenu();

=======
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
		Gui.InputInsert();
	}

}
void GUI::DrawHashTable() {

	Gui.DrawSecondMenu();
	Gui.DrawBack();
}

void GUI::DrawLinkedList() {
	Gui.DrawSecondMenu();
>>>>>>> d3ef482 (Fix gitignore and update demo menu)
	Gui.DrawBack();
}

void GUI::DrawAVLTree() {
<<<<<<< HEAD

	Gui.DrawSecondMenu();

=======
	Gui.DrawSecondMenu();
>>>>>>> d3ef482 (Fix gitignore and update demo menu)
	Gui.DrawBack();
}

void GUI::DrawGraph() {
<<<<<<< HEAD

	Gui.DrawSecondMenu();

=======
	Gui.DrawSecondMenu();
>>>>>>> d3ef482 (Fix gitignore and update demo menu)
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

<<<<<<< HEAD

=======
>>>>>>> d3ef482 (Fix gitignore and update demo menu)
void GUI::InputInsert() {
	int key = GetCharPressed();
	while (key > 0) {
		if (key >= '0' && key <= '9') {
			inputstring += char(key);
		}
		key = GetCharPressed();
	}
	DrawText(inputstring.c_str(), SecondMenuWidth * float(1) / 3 + 120, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, WHITE);

<<<<<<< HEAD
	if (IsKeyPressed(KEY_ENTER) && !inputstring.empty()) {
		int value = std::stoi(inputstring);  // Chuyển input thành số nguyên
		myHashTable.insert(value);  // Chèn số vào Hash Table
		myHashTable.drawHashTable();  // Vẽ lại Hash Table để cập nhật giao diện

		cout << "Inserted Value: " << value << endl;  // Debug
=======
	if (IsKeyPressed(KEY_ENTER)) {
		cout << "Value: " << inputstring << endl;
>>>>>>> d3ef482 (Fix gitignore and update demo menu)
		inputstring = "";
		Gui.ClickInsert = false;
	}

	if (IsKeyPressed(KEY_BACKSPACE) && !inputstring.empty()) {
		inputstring.pop_back();
	}
}

<<<<<<< HEAD
void GUI::InputInit() {
	int key = GetCharPressed();
	while (key > 0) {
		if (key >= '0' && key <= '9') {
			inputstring += char(key);
		}
		key = GetCharPressed();
	}
	DrawText(inputstring.c_str(), SecondMenuWidth * 1 / 3 + 120,
		SecondMenuHeight + SecondMenuHeight * 1 / 6 +
		(SecondMenuHeight * 1 / 6) * 1 / 2, 20, WHITE);

	if (IsKeyPressed(KEY_ENTER)) {
		int bucketSize = std::stoi(inputstring);
		if (bucketSize > 0) {
			myHashTable = HashTable(bucketSize);  // Khởi tạo lại bảng băm
			myHashTable.drawHashTable();  // Cập nhật giao diện
			cout << "Created new Hash Table with " << bucketSize << " buckets!" << endl;
		}
		else {
			cout << "Invalid bucket size!" << endl;
		}
		inputstring = "";
		Gui.ClickInit = false;
	}

	if (IsKeyPressed(KEY_BACKSPACE) && !inputstring.empty()) {
		inputstring.pop_back();
	}
}

void GUI::InputDelete() {
	if (!Gui.ClickDelete) return;  // Nếu chưa nhấn nút DELETE thì không làm gì

	int key = GetCharPressed();
	while (key > 0) {
		if (key >= '0' && key <= '9') {
			inputstring += char(key);
		}
		key = GetCharPressed();
	}

	// Hiển thị số nhập vào
	DrawText(inputstring.c_str(), SecondMenuWidth * 1 / 3 + 120,
		SecondMenuHeight + SecondMenuHeight * 3 / 6 +
		(SecondMenuHeight * 1 / 6) * 1 / 2, 20, WHITE);

	if (IsKeyPressed(KEY_ENTER) && !inputstring.empty()) {
		int value = std::stoi(inputstring);
		myHashTable.remove(value);  // Gọi hàm xóa trong HashTable
		inputstring = "";
		Gui.ClickDelete = false;  // Đặt lại trạng thái click
	}

	if (IsKeyPressed(KEY_BACKSPACE) && !inputstring.empty()) {
		inputstring.pop_back();
	}
}

void GUI::InputSearch() {
	if (!Gui.ClickSearch) return;  // Nếu chưa nhấn nút SEARCH thì không làm gì

	int key = GetCharPressed();
	while (key > 0) {
		if (key >= '0' && key <= '9') {
			inputstring += char(key);
		}
		key = GetCharPressed();
	}

	// Hiển thị số nhập vào
	DrawText(inputstring.c_str(), SecondMenuWidth * 1 / 3 + 120,
		SecondMenuHeight + SecondMenuHeight * 4 / 6 +
		(SecondMenuHeight * 1 / 6) * 1 / 2, 20, WHITE);

	if (IsKeyPressed(KEY_ENTER) && !inputstring.empty()) {
		int value = std::stoi(inputstring);
		bool found = myHashTable.search(value);  // Kiểm tra trong Hash Table

		if (found) {
			std::cout << "Found: " << value << std::endl;
			DrawText("Found!", ScreenWidth / 2, ScreenHeight / 2, 30, PINK);
		}
		else {
			std::cout << "Not Found: " << value << std::endl;
			DrawText("Not Found!", ScreenWidth / 2, ScreenHeight / 2, 30, RED);
		}

		inputstring = "";
		Gui.ClickSearch = false;  // Đặt lại trạng thái click
	}

	if (IsKeyPressed(KEY_BACKSPACE) && !inputstring.empty()) {
		inputstring.pop_back();
	}
}
=======
>>>>>>> d3ef482 (Fix gitignore and update demo menu)
