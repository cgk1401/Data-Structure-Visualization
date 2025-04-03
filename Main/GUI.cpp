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
    buttonclear.DrawButton();
}

void GUI::DrawListMenu() {
    // Menu constants
    const float MENU_WIDTH = ScreenWidth / 5.0f;
    const float MENU_HEIGHT = ScreenHeight;

    // Draw menu background
    DrawRectangleRounded(
        { 0, 0, MENU_WIDTH, MENU_HEIGHT },
        0.1f, 10, C[1]
    );

    // Draw "Linked List" title inside menu
    const char* titleText = "Linked List";
    const int TITLE_FONT_SIZE = 28;
    Vector2 titleSize = MeasureTextEx(GetFontDefault(), titleText, TITLE_FONT_SIZE, 1);
    float titleX = (MENU_WIDTH - titleSize.x) / 2;
    float titleY = 20.0f; // Positioned at top of menu
    DrawText(titleText, titleX, titleY, TITLE_FONT_SIZE, C[0]);

    // Button layout constants
    const float BUTTON_WIDTH = MENU_WIDTH * 0.85f;
    const float BUTTON_HEIGHT = 40.0f;
    const float BUTTON_MARGIN_X = MENU_WIDTH * 0.075f;
    const float BUTTON_SPACING = 15.0f;
    const float BUTTON_START_Y = titleY + titleSize.y + 20.0f; // Start below title

    // Button configuration helper
    auto ConfigureButton = [&](Button& button, int position) {
        button.coordinateX = BUTTON_MARGIN_X;
        button.coordinateY = BUTTON_START_Y + position * (BUTTON_HEIGHT + BUTTON_SPACING);
        button.width = BUTTON_WIDTH;
        button.height = BUTTON_HEIGHT;
        button.DrawButton();
        };

    // Draw all buttons
    ConfigureButton(buttoninit, 0);
    ConfigureButton(buttoninsert, 1);
    ConfigureButton(buttondelete, 2);
    ConfigureButton(buttonsearch, 3);
    ConfigureButton(buttonclear, 4);
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
        inputstring = "";
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

    int val = Gui.Input(buttonclear.coordinateX, buttonclear.coordinateY + buttonclear.height + 20);

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
        inputActive = false;
        currentInputMode = NONE;
    }

    list.update();
    list.draw();

    BeginScissorMode(SecondMenuWidth, 0, ScreenWidth - SecondMenuWidth, ScreenHeight);
    {
        // Apply scroll offset to the list's drawing position
        list.setDrawOffset(linkedListScrollY);
        list.update();
        list.draw();
    }
    EndScissorMode();

    if (search_result_timer > 0.0f) {
        search_result_timer -= GetFrameTime();
        if (list.get_active() != -1 && list.get_search_state() == 1) {
            DrawText("Found", ScreenWidth / 12, ScreenHeight - 50, 20, GREEN);
        }
        else if (list.get_search_state() == 2) {
            DrawText("Not Found", ScreenWidth / 12, ScreenHeight - 50, 20, RED);
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
    // Back button constants
    const float BUTTON_WIDTH = 120.0f;
    const float BUTTON_HEIGHT = 40.0f;
    const float BUTTON_MARGIN = 20.0f;
    const float CORNER_RADIUS = 0.3f;
    const int CORNER_SEGMENTS = 10;
    const Color HOVER_COLOR = { 200, 50, 50, 255 };

    // Position at bottom of menu
    Rectangle BackButton = {
        BUTTON_MARGIN,
        ScreenHeight - BUTTON_HEIGHT - BUTTON_MARGIN,
        BUTTON_WIDTH,
        BUTTON_HEIGHT
    };

    // Hover effect
    Vector2 mouse = GetMousePosition();
    bool isHovered = CheckCollisionPointRec(mouse, BackButton);

    // Set button color
    Color buttonColor = isHovered ? HOVER_COLOR : RED;

    // Draw button
    DrawRectangleRounded(BackButton, CORNER_RADIUS, CORNER_SEGMENTS, buttonColor);

    // Center text in button
    const char* buttonText = "Back";
    Vector2 textSize = MeasureTextEx(GetFontDefault(), buttonText, 20, 1);
    DrawText(buttonText,
        BackButton.x + (BackButton.width - textSize.x) / 2,
        BackButton.y + (BackButton.height - textSize.y) / 2,
        20, WHITE);

    // Handle click
    if (isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CurrentStruture == LINKEDLIST) list.clear();
        CurrentStruture = MENU;
        inputActive = false;
        currentInputMode = NONE;
        search_result_timer = 0.0f;
    }
}

void GUI::DrawInputBox(int posX, int posY) {
    if (!inputActive) return;

    // Style constants matching other buttons
    const float MENU_WIDTH = ScreenWidth / 5.0f;
    const float BUTTON_WIDTH = MENU_WIDTH * 0.85f;
    const float BUTTON_HEIGHT = 40.0f;
    const float BUTTON_MARGIN_X = MENU_WIDTH * 0.075f;
    const float CORNER_RADIUS = 0.3f;
    const int SEGMENTS = 10;
    const float EXTRA_SPACING = 30.0f; // Increased spacing below clear button

    // Position input box lower with more spacing
    Vector2 boxPosition = {
        buttonclear.coordinateX,
        buttonclear.coordinateY + buttonclear.height + EXTRA_SPACING
    };

    // Get appropriate label text
    const char* labelText = "";
    switch (currentInputMode) {
    case INIT:    labelText = "Init Nodes: "; break;
    case INSERT:  labelText = "Insert Value: "; break;
    case DELETE:  labelText = "Delete Value: "; break;
    case SEARCH:  labelText = "Search Value: "; break;
    default:      return;
    }

    // Draw label
    DrawText(labelText, boxPosition.x, boxPosition.y - 25, 20, C[0]);

    // Create input box rectangle
    Rectangle inputBox = {
        boxPosition.x,
        boxPosition.y,
        BUTTON_WIDTH,
        BUTTON_HEIGHT
    };

    // Draw main rounded box (no border)
    DrawRectangleRounded(inputBox, CORNER_RADIUS, SEGMENTS, C[2]);

    // Draw input text (centered vertically)
    Vector2 textPosition = {
        boxPosition.x + 10,
        boxPosition.y + (BUTTON_HEIGHT - 20) / 2
    };
    DrawText(inputstring.c_str(), textPosition.x, textPosition.y, 20, C[0]);

    // Draw blinking cursor
    if ((int)(GetTime() * 2) % 2) { // Blinking effect
        int textWidth = MeasureText(inputstring.c_str(), 20);
        DrawRectangle(
            textPosition.x + 5 + textWidth,
            textPosition.y,
            2,
            20,
            C[0]
        );
    }
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