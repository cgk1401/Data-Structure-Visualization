#include <iostream>
#include <string>
#include "GUI.hpp"
#include "LinkedList.hpp"

GUI Gui;

TypeDataStructure CurrentStruture = MENU;

void GUI::Start() {
    InitWindow(ScreenWidth, ScreenHeight, "Data Structure Visualization");

    for (int i = 0; i < 6; i++) { C[i] = ColorPalette[2][i]; }
    buttoninit.setColor(C[2]);
    buttoninsert.setColor(C[2]);
    buttondelete.setColor(C[2]);
    buttonsearch.setColor(C[2]);
    buttonclear.setColor(C[2]);

    SetTargetFPS(60);

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(C[4]);
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
    DrawText("Choose Data Structure", ScreenWidth * float(2) / 5, ScreenHeight * float(5) / 6, 40, C[0]);

    Rectangle HASHTABLEBUTTON = { ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };
    Rectangle LINKEDLISTBUTTON = { ScreenWidth * float(3) / 5, ScreenHeight * float(1) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };
    Rectangle AVLTREEBUTTON = { ScreenWidth * float(1) / 5, ScreenHeight * float(3) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };
    Rectangle GRAPHBUTTON = { ScreenWidth * float(3) / 5, ScreenHeight * float(3) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

    DrawRectangleRec(HASHTABLEBUTTON, C[2]);
    DrawRectangleRec(LINKEDLISTBUTTON, C[2]);
    DrawRectangleRec(AVLTREEBUTTON, C[2]);
    DrawRectangleRec(GRAPHBUTTON, C[2]);

    DrawText("HASHTABLE", ScreenWidth * float(1) / 5 + 20, ScreenHeight * float(1) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2, 20, C[0]);
    DrawText("LINKEDLIST", ScreenWidth * float(3) / 5 + 20, ScreenHeight * float(1) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2, 20, C[0]);
    DrawText("AVLTREE", ScreenWidth * float(1) / 5 + 20, ScreenHeight * float(3) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2, 20, C[0]);
    DrawText("GRAPH", ScreenWidth * float(3) / 5 + 20, ScreenHeight * float(3) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2, 20, C[0]);

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
    DrawRectangle(0, ScreenHeight / 2, ScreenWidth / 5, ScreenHeight / 2, C[1]);
    buttoninit.DrawButton();
    buttoninsert.DrawButton();
    buttondelete.DrawButton();
    buttonsearch.DrawButton();

    if (buttoninsert.IsClick()) {
        Gui.ClickInsert = true;
    }
    if (Gui.ClickInsert) {
        DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);
        int val = Gui.Input(SecondMenuWidth * float(1) / 3 + 120, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);

        if (val != -1) {
            list.add_node(val);
            Gui.ClickInsert = false;
        }
    }
}

void GUI::DrawListMenu() {
    DrawRectangle(0, ScreenHeight / 2, ScreenWidth / 5, ScreenHeight / 2, C[1]);
    buttoninit.DrawButton();
    buttoninsert.DrawButton();
    buttondelete.DrawButton();
    buttonsearch.DrawButton();
    buttonclear.DrawButton();
}

void GUI::DrawHashTable() {
    Gui.DrawSecondMenu();
    Gui.DrawBack();
}

void GUI::DrawLinkedList() {
    Gui.DrawListMenu();
    Gui.DrawBack();

    if (buttoninit.IsClick()) {
        Gui.ClickInit = true;
    }
    if (Gui.ClickInit) {
        DrawText("Nodes : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(0.7) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);
        int tmp = Input(SecondMenuWidth * float(1) / 3 + 140, SecondMenuHeight + SecondMenuHeight * float(0.7) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);

        if (tmp != -1) {
            list.clear();
            list.rand_list(tmp);
            list.print_list();
            Gui.ClickInit = false;
        }
    }

    if (buttoninsert.IsClick()) {
        Gui.ClickInsert = true;
    }
    if (Gui.ClickInsert) {
        DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);
        int val = Gui.Input(SecondMenuWidth * float(1) / 3 + 120, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);

        if (val != -1) {
            list.add_node(val);
            Gui.ClickInsert = false;
        }
    }

    if (buttondelete.IsClick()) {
        if (list.get_active() >= 0) {
            list.delete_node(list.get_active());
        }
        else {
            Gui.ClickDelete = true;
        }
    }
    if (Gui.ClickDelete) {
        DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(3) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);
        int val = Gui.Input(SecondMenuWidth * float(1) / 3 + 120, SecondMenuHeight + SecondMenuHeight * float(3) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);

        if (val != -1) {
            list.delete_node(val);
            Gui.ClickDelete = false;
        }
    }

    if (buttonclear.IsClick()) {
        list.clear();
    }

    list.update();
    list.draw();
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
    DrawText("Linked List", ScreenWidth * float(2) / 5, 100, 40, C[0]);

    Rectangle BackButton = { 50, 50, 150, 50 };
    DrawRectangleRec(BackButton, RED);
    DrawText("Back", 100, 65, 30, WHITE);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        if (CheckCollisionPointRec(mouse, BackButton)) {
            if (CurrentStruture == LINKEDLIST) {
                list.clear();
            }
            CurrentStruture = MENU;
            ClickInit = false;
            ClickInsert = false;
            ClickDelete = false;
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
    DrawText(inputstring.c_str(), posX, posY, 20, C[0]);

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