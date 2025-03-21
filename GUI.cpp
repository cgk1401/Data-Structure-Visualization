#include <iostream>
#include <string>
#include "GUI.hpp"
#include "LinkedList.hpp"

GUI Gui;
TypeDataStructure CurrentStruture = MENU;

void GUI::Start() {
    InitWindow(ScreenWidth, ScreenHeight, "Data Structure Visualization");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(VIOLET);

        switch (CurrentStruture) {
        case MENU: DrawMainMenu(); break;
        case HASHTABLE: DrawHashTable(); break;
        case LINKEDLIST: DrawLinkedList(); break;
        case AVLTREE: DrawAVLTree(); break;
        case GRAPH: DrawGraph(); break;
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
        if (CheckCollisionPointRec(mouse, HASHTABLEBUTTON)) {
            CurrentStruture = HASHTABLE;
        }
        else if (CheckCollisionPointRec(mouse, LINKEDLISTBUTTON)) {
            CurrentStruture = LINKEDLIST;
        }
        else if (CheckCollisionPointRec(mouse, AVLTREEBUTTON)) {
            CurrentStruture = AVLTREE;
        }
        else if (CheckCollisionPointRec(mouse, GRAPHBUTTON)) {
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

    if (buttoninsert.IsClick()) {
        ClickInsert = true;
    }
    if (ClickInsert) {
        DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40,
            SecondMenuHeight + SecondMenuHeight * float(2) / 6 +
            (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, WHITE);
        InputInsert();
    }
}

void GUI::DrawLinkedListMenu() {
    DrawRectangle(0, ScreenHeight / 2, ScreenWidth / 5, ScreenHeight / 2, GRAY);
    buttoninit.DrawButton();
    buttoninsert.DrawButton();
    buttondelete.DrawButton();
    buttonsearch.DrawButton();

    static bool ClickInit = false;
    static bool ClickSearch = false;

    if (buttoninit.IsClick()) {
        ClickInit = true;
    }
    if (ClickInit) {
        DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40,
            SecondMenuHeight + SecondMenuHeight * float(0.5) / 6 +
            (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, WHITE);
        int val = Input(SecondMenuWidth * float(1) / 3 + 120,
            SecondMenuHeight + SecondMenuHeight * float(0.5) / 6 +
            (SecondMenuHeight * float(1) / 6) * float(1) / 2);
        if (val != -1) {
            list.clear();  // Clear existing list before initialization
            list.add_node(val);
            list.print_list();
            ClickInit = false;
        }
    }

    if (buttoninsert.IsClick()) {
        ClickInsert = true;
    }
    if (ClickInsert) {
        DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40,
            SecondMenuHeight + SecondMenuHeight * float(1.5) / 6 +
            (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, WHITE);
        int val = Input(SecondMenuWidth * float(1) / 3 + 120,
            SecondMenuHeight + SecondMenuHeight * float(1.5) / 6 +
            (SecondMenuHeight * float(1) / 6) * float(1) / 2);
        if (val != -1) {
            list.add_node(val);
            list.print_list();
            ClickInsert = false;
        }
    }

    if (buttondelete.IsClick()) {
        ClickDelete = true;
    }
    if (ClickDelete) {
        DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40,
            SecondMenuHeight + SecondMenuHeight * float(2.5) / 6 +
            (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, WHITE);
        int val = Input(SecondMenuWidth * float(1) / 3 + 120,
            SecondMenuHeight + SecondMenuHeight * float(2.5) / 6 +
            (SecondMenuHeight * float(1) / 6) * float(1) / 2);
        if (val != -1) {
            list.delete_node(val);
            list.print_list();
            ClickDelete = false;
        }
    }

    if (buttonsearch.IsClick()) {
        ClickSearch = true;
    }
    if (ClickSearch) {
        DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40,
            SecondMenuHeight + SecondMenuHeight * float(3.5) / 6 +
            (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, WHITE);
        int val = Input(SecondMenuWidth * float(1) / 3 + 120,
            SecondMenuHeight + SecondMenuHeight * float(3.5) / 6 +
            (SecondMenuHeight * float(1) / 6) * float(1) / 2);
        if (val != -1) {
            bool found = list.search(val);
            std::cout << "Value " << val << (found ? " found" : " not found") << std::endl;
            ClickSearch = false;
        }
    }
}

void GUI::DrawHashTable() {
    DrawSecondMenu();
    DrawBack();
}

void GUI::DrawLinkedList() {
    list.draw();
    DrawLinkedListMenu();
    DrawBack();
}

void GUI::DrawAVLTree() {
    DrawSecondMenu();
    DrawBack();
}

void GUI::DrawGraph() {
    DrawSecondMenu();
    DrawBack();
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
            list.clear();  // Clear the list when going back to menu
            ClickInsert = false;
            ClickDelete = false;
            inputstring = "";
        }
    }
}

int GUI::InputInsert() {
    int key = GetCharPressed();
    while (key > 0) {
        if (key >= '0' && key <= '9') {
            inputstring += char(key);
        }
        key = GetCharPressed();
    }
    DrawText(inputstring.c_str(), SecondMenuWidth * float(1) / 3 + 120,
        SecondMenuHeight + SecondMenuHeight * float(2) / 6 +
        (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, WHITE);

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) {
        int val = std::stoi(inputstring);
        std::cout << "Value: " << val << std::endl;
        inputstring = "";
        return val;
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !inputstring.empty()) {
        inputstring.pop_back();
    }

    return -1;
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
        std::cout << "Value: " << val << std::endl;
        inputstring = "";
        return val;
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !inputstring.empty()) {
        inputstring.pop_back();
    }

    return -1;
}