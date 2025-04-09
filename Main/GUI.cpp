
#include <iostream>
#include "GUI.hpp"

using namespace std;

GUI Gui;

TypeDataStructure CurrentStruture = MENU;


GUI::GUI()
	: table(10)
{}

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
	DrawRectangle(0, ScreenHeight / 2, ScreenWidth / 5, ScreenHeight / 2, RAYWHITE);
	buttoninit.DrawButton();
	buttoninsert.DrawButton();
	buttondelete.DrawButton();
	buttonsearch.DrawButton();
}

void GUI::DrawHashTable() {
    static bool isInitClicked = false;  // Trạng thái nút Init
    static bool isCreating = false;     // Trạng thái nhập liệu cho Create
    static std::string createInput = ""; // Chuỗi nhập liệu cho Create

    Gui.DrawSecondMenu();
    Gui.DrawBack();

    // Xử lý Init
    if (buttoninit.IsClick() && !isInitClicked) {
        Gui.isClickInit = true;
        Gui.isClickInsert = Gui.isClickDelete = Gui.isClickSearch = false;
        table.startInitAnimation();
        isInitClicked = true;
        std::cout << "✅ Init Button is clicked\n";
    }

    if (Gui.isClickInit) {
        if (table.isInitAnimationRunning()) {
            table.drawInitAnimation(buttoninit.coordinateX, buttoninit.coordinateY);
        }
        else {
            table.drawInitAnimation(buttoninit.coordinateX, buttoninit.coordinateY); // Tiếp tục vẽ nút
            if (Gui.isClickCreate) {
                isCreating = true;
                Gui.isClickCreate = false;
            }
            if (Gui.isClickRandom) {
                table.handleRandomButton();
                Gui.isClickRandom = false; // Reset để nhấn Random liên tục
                // Không reset isInitClicked hay isClickInit để giữ nút hiển thị
            }
        }
    }

    // Xử lý nhập liệu cho Create
    if (isCreating) {
        DrawText("Enter number of buckets: ", 100, 200, 20, PINK);
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= '0' && key <= '9') {
                createInput += char(key);
            }
            key = GetCharPressed();
        }
        DrawText(createInput.c_str(), 300, 200, 20, BLACK);

        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) {
            if (!createInput.empty()) {
                int newSize = std::stoi(createInput);
                table.init(newSize);
                std::cout << "✅ Hash Table created with " << newSize << " buckets!\n";
                isCreating = false;
                createInput = "";
                // Không reset isInitClicked hay gọi setButtonsVisible(false)
            }
            else {
                std::cout << "❌ Please enter a valid number!\n";
                isCreating = false;
                createInput = "";
            }
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !createInput.empty()) {
            createInput.pop_back();
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            isCreating = false;
            createInput = "";
        }
    }

    // Xử lý Insert
    if (buttoninsert.IsClick()) {
        Gui.isClickInsert = true;
        Gui.isClickInit = Gui.isClickDelete = Gui.isClickSearch = false;
        if (isInitClicked) {
            isInitClicked = false;
            table.setButtonsVisible(false); // Ẩn nút khi chuyển sang Insert
            std::cout << "✅ Switched to Insert, hiding Create/Random buttons\n";
        }
    }
    if (Gui.isClickInsert) {
        DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40,
            SecondMenuHeight + SecondMenuHeight * float(2) / 6 +
            (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, PINK);
        int val = Gui.Input(SecondMenuWidth * 1 / 3 + 120,
            SecondMenuHeight + SecondMenuHeight * float(2) / 6 +
            (SecondMenuHeight * 1 / 6) * 1 / 2);
        if (val != -1) {
            table.insert(val);
            Gui.isClickInsert = false;
        }
    }

    // Xử lý Delete
    if (buttondelete.IsClick()) {
        Gui.isClickDelete = true;
        Gui.isClickInsert = Gui.isClickInit = Gui.isClickSearch = false;
        if (isInitClicked) {
            isInitClicked = false;
            table.setButtonsVisible(false); // Ẩn nút khi chuyển sang Delete
            std::cout << "✅ Switched to Delete, hiding Create/Random buttons\n";
        }
    }
    if (Gui.isClickDelete) {
        DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40,
            SecondMenuHeight + SecondMenuHeight * float(3) / 6 +
            (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, PINK);
        int val = Gui.Input(SecondMenuWidth * float(1) / 3 + 120,
            SecondMenuHeight + SecondMenuHeight * float(3) / 6 +
            (SecondMenuHeight * float(1) / 6) * 1 / 2);
        if (val != -1) {
            table.remove(val);
            Gui.isClickDelete = false;
        }
    }

    // Xử lý Search
    if (buttonsearch.IsClick()) {
        Gui.isClickSearch = true;
        Gui.isClickInsert = Gui.isClickInit = Gui.isClickDelete = false;
        if (isInitClicked) {
            isInitClicked = false;
            table.setButtonsVisible(false); // Ẩn nút khi chuyển sang Search
            std::cout << "✅ Switched to Search, hiding Create/Random buttons\n";
        }
    }
    if (Gui.isClickSearch) {
        DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40,
            SecondMenuHeight + SecondMenuHeight * float(4) / 6 +
            (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, PINK);
        int val = Gui.Input(SecondMenuWidth * float(1) / 3 + 120,
            SecondMenuHeight + SecondMenuHeight * float(4) / 6 +
            (SecondMenuHeight * float(1) / 6) * 1 / 2);
        if (val != -1) {
            table.search(val);
            Gui.isClickSearch = false;
        }
    }

    table.drawHashTable();
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