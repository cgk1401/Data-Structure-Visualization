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
    buttonclear.DrawButton(); // Added for consistency
}

void GUI::DrawListMenu() {
    DrawRectangle(0, ScreenHeight / 2, ScreenWidth / 5, ScreenHeight / 2, C[1]);
    buttoninit.DrawButton();
    buttoninsert.DrawButton();
    buttondelete.DrawButton();
    buttonsearch.DrawButton();
    buttonclear.DrawButton(); // Keep only these 5 buttons
}

void GUI::DrawHashTable() {
    Gui.DrawSecondMenu();
    Gui.DrawBack();
}

void GUI::DrawLinkedList() {
    Gui.DrawListMenu();
    Gui.DrawBack();

    // Draw the reusable input box at a fixed position
    Gui.DrawInputBox(SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + 100);

    // Handle button clicks to set input mode
    if (buttoninit.IsClick()) {
        currentInputMode = INIT;
        inputActive = true;
        inputstring = "";  // Reset input
    }
    if (buttoninsert.IsClick()) {
        currentInputMode = INSERT;
        inputActive = true;
        inputstring = "";
    }
    if (buttondelete.IsClick()) {
        if (list.get_active() >= 0) {
            list.delete_node(list.get_active());
        }
        else {
            currentInputMode = DELETE;
            inputActive = true;
            inputstring = "";
        }
    }
    if (buttonsearch.IsClick()) {
        currentInputMode = SEARCH;
        inputActive = true;
        inputstring = "";
    }
    if (buttonclear.IsClick()) {
        list.clear();
    }

    // Process input when Enter is pressed
    int val = Gui.Input(SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + 100);
    if (val != -1) {
        switch (currentInputMode) {
        case INIT:
            list.clear();
            list.rand_list(val);
            list.print_list();
            break;
        case INSERT:
            list.add_node(val);
            break;
        case DELETE:
            list.delete_node(val);
            break;
        case SEARCH:
            list.search_node(val);
            search_result_timer = 2.0f;
            break;
        default:
            break;
        }
        inputActive = false;  // Deactivate input box after processing
        currentInputMode = NONE;
    }

    list.update();
    list.draw();

    if (search_result_timer > 0.0f) {
        search_result_timer -= GetFrameTime();
        if (list.get_active() != -1 && list.get_search_state() == 1) {
            DrawText("Found", ScreenWidth * float(2) / 5, ScreenHeight - 50, 20, GREEN);
        }
        else if (list.get_search_state() == 2) {
            DrawText("Not Found", ScreenWidth * float(2) / 5, ScreenHeight - 50, 20, RED);
        }
    }
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
            inputActive = false;         // Reset input box state
            currentInputMode = NONE;     // Reset input mode
            search_result_timer = 0.0f;  // Reset timer
        }
    }
}

void GUI::DrawInputBox(int posX, int posY) {
    if (!inputActive) return;

    const char* label = "";
    switch (currentInputMode) {
    case INIT:    label = "Init Nodes: "; break;
    case INSERT:  label = "Insert Value: "; break;
    case DELETE:  label = "Delete Value: "; break;
    case SEARCH:  label = "Search Value: "; break;
    default:      return;
    }

    DrawText(label, posX, posY - 20, 20, C[0]);
    DrawRectangle(posX, posY, 100, 30, C[1]);  // Draw input box background
    DrawText(inputstring.c_str(), posX + 5, posY + 5, 20, C[0]);  // Draw current input
}

int GUI::Input(int posX, int posY) {
    if (!inputActive) return -1;

    int key = GetCharPressed();
    while (key > 0) {
        if (key >= '0' && key <= '9') {
            inputstring += char(key);
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) {
        if (inputstring.empty()) return -1;
        try {
            int val = std::stoi(inputstring);
            std::cout << "Value: " << val << std::endl;
            inputstring = "";
            return val;
        }
        catch (const std::exception& e) {
            std::cout << "Invalid input: " << e.what() << std::endl;
            inputstring = "";
            return -1;
        }
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !inputstring.empty()) {
        inputstring.pop_back();
    }

    if (IsKeyPressed(KEY_ESCAPE) && inputActive) {
        inputActive = false;
        currentInputMode = NONE;
        inputstring = "";
    }

    return -1;
}