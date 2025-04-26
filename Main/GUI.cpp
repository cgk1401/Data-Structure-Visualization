#include <iostream>
#include <string>
#include "GUI.hpp"
#include "Graph.hpp"
#include "HashTable.hpp"
using namespace std;

GUI Gui;

TypeDataStructure CurrentStruture = MENU;


GUI::GUI()
	: table(60), AnimationAVLTree(&tree), graph(false), dijkstra_animation(graph)
{}


void GUI::SetActiveMenuAVLTree(ActiveMenuTypeAVLTree newMenu) {
    if (activemenu_avltree == newMenu) {
        activemenu_avltree = newMenu;
    }
    else {
        activemenu_avltree = newMenu;
    }
}

void GUI::SetActiveMenuInitAVLTree(ActiveMenuInitAVLTree newMenu) {
    if (activemenuinit_avltree == newMenu) {
        activemenuinit_avltree = newMenu;
    }
    else {
        activemenuinit_avltree = newMenu;
    }
}

void GUI::Start() {
    InitWindow(ScreenWidth, ScreenHeight, "Data Structure Visualization");
    LoadSource();
    for (int i = 0; i < 6; i++) { C[i] = ColorPalette[1][i]; }

    // Set icon
	Image icon = LoadImage("../../Data-Structure-Visualization/assets/Icon1.png");
	SetWindowIcon(icon);
    UnloadImage(icon);

    //Set music
	InitAudioDevice();
	music = LoadMusicStream("../../Data-Structure-Visualization/assets/BackgroundMusic.mp3");
    PlayMusicStream(music);
	SetMusicVolume(music, 0.5f);

    SetTargetFPS(60);

    while (WindowShouldClose() == false) {
        UpdateMusicStream(music);

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
		else if (CurrentStruture == SETTING) {
			Gui.DrawSettingMenu();
		}
        else if (CurrentStruture == CREDIT) {
            Gui.DrawCreditMenu();
        }
        EndDrawing();
    }

    UnloadMusicStream(music);
    CloseAudioDevice();

    UnloadTexture(ImageBack);
    CloseWindow();
}

void GUI::DrawMainMenu() {
    DrawText("Choose Data Structure", ScreenWidth * float(2) / 5, ScreenHeight * float(5) / 6, 40, WHITE);

    //Font custom = LoadFont("../../Data-Structure-Visualization/assets/PublicSans-Bold.ttf");
    //DrawTextEx(customfont, "Choose Data Structure", { ScreenWidth * float(2) / 5, ScreenHeight * float(5) / 6 }, 60, 1, C[0]);
    DrawText("Choose Data Structure", ScreenWidth * float(2) / 5, ScreenHeight * float(0.5) / 6, 40, C[0]);

    Rectangle HASHTABLEBUTTON = { ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

    Rectangle LINKEDLISTBUTTON = { ScreenWidth * float(3) / 5, ScreenHeight * float(1) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

    Rectangle AVLTREEBUTTON = { ScreenWidth * float(1) / 5, ScreenHeight * float(3) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

    Rectangle GRAPHBUTTON = { ScreenWidth * float(3) / 5, ScreenHeight * float(3) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

    Rectangle SETTINGBUTTON = { ScreenWidth * float(2.25) / 5, ScreenHeight * float(4.5) / 5, ScreenWidth * float(1) / 10, ScreenHeight * float(1) / 18 };

    Rectangle CREDITBUTTON = { ScreenWidth * 0.015f, ScreenHeight - ScreenWidth * 0.045f, ScreenWidth * 0.02, ScreenWidth * 0.02 };

    DrawRectangleRounded(HASHTABLEBUTTON, 0.3f, 10, C[2]);
    DrawRectangleRounded(LINKEDLISTBUTTON, 0.3f, 10, C[2]);
    DrawRectangleRounded(AVLTREEBUTTON, 0.3f, 10, C[2]);
    DrawRectangleRounded(GRAPHBUTTON, 0.3f, 10, C[2]);

    DrawText("HASHTABLE", ScreenWidth * float(1) / 5 + 20, ScreenHeight * float(1) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2, 20, C[0]);
    DrawText("LINKEDLIST", ScreenWidth * float(3) / 5 + 20, ScreenHeight * float(1) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2, 20, C[0]);
    DrawText("AVLTREE", ScreenWidth * float(1) / 5 + 20, ScreenHeight * float(3) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2, 20, C[0]);
    DrawText("GRAPH", ScreenWidth * float(3) / 5 + 20, ScreenHeight * float(3) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2, 20, C[0]);

    DrawRectangleRounded(SETTINGBUTTON, 0.3f, 10, C[2]);
    DrawText("SETTING", SETTINGBUTTON.x + (SETTINGBUTTON.width - MeasureText("SETTING", 20)) / 2, SETTINGBUTTON.y + (SETTINGBUTTON.height - 20) / 2, 20, C[0]);

    DrawRectangleRounded(CREDITBUTTON, 0.5f, 15, C[2]);
    DrawText("i", CREDITBUTTON.x + (CREDITBUTTON.width - MeasureText("i", ScreenWidth * 0.016f)) / 2, CREDITBUTTON.y + (CREDITBUTTON.height - ScreenWidth * 0.016f) / 2, ScreenWidth * 0.016f, C[0]);

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
        else if (CheckCollisionPointRec(mouse, SETTINGBUTTON)) {
            CurrentStruture = SETTING;
        }
        else if (CheckCollisionPointRec(mouse, CREDITBUTTON)) {
            CurrentStruture = CREDIT;
        }
    }
}

void GUI::DrawSettingMenu() {

    // Draw Theme choices
    for (int i = 0; i < 4; i++) {
        Rectangle themeRect = { ScreenWidth * 0.05f, ScreenHeight * 0.3f + i * 80, ScreenWidth * 0.1f, ScreenHeight * 0.05f };

        // Background of theme preview
        DrawRectangleRounded(themeRect, 0.2f, 6, ColorPalette[i][1]);
        // A strip or smaller rectangle to show accent color
        DrawRectangle(themeRect.x + 10, themeRect.y + 10, 30, 30, ColorPalette[i][5]);
        // Optional label
        DrawText(TextFormat("Theme %d", i + 1), themeRect.x + 50, themeRect.y + 15, 20, C[0]);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), themeRect)) {
            for (int j = 0; j < 6; j++) C[j] = ColorPalette[i][j];
        }
    }

    //Draw Sample (logic copy from Graph.cpp)
    Vector2 sample[3];
    sample[0] = { ScreenWidth * 0.5f, ScreenHeight * 0.4f };
    sample[1] = { ScreenWidth * 0.65f, ScreenHeight * 0.5f };
    sample[2] = { ScreenWidth * 0.45f, ScreenHeight * 0.65f };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < i; j++) {
            if (i + j == 3) { DrawLineEx(sample[i], sample[j], 7.5f, C[5]); }
            DrawLineEx(sample[i], sample[j], 3.0f, C[3]);

            // display weight
            float posX = sample[i].x + (4.45f / 10.0f) * (sample[j].x - sample[i].x) - 7.0f;
            float posY = sample[i].y + (4.45f / 10.0f) * (sample[j].y - sample[i].y) - 7.0f;

            float displaceX = sample[i].y - sample[j].y;
            float displaceY = sample[j].x - sample[i].x;
            float distance = sqrt(displaceX * displaceX + displaceY * displaceY);
            displaceX /= distance / 18; displaceY /= distance / 18;
            if (displaceX < 0) { displaceX = -displaceX; displaceY = -displaceY; } // keep the edge's weight to the right side

            DrawText(std::to_string(i + j).c_str(), posX + displaceX, posY + displaceY, 20, C[0]);
        }
    }
    for (int i = 0; i < 3; i++) {
        if (i == 0) { DrawCircleV(sample[i], 35.0f, C[5]); }
        else { DrawCircleV(sample[i], 35.0f, C[1]); }
        DrawCircleLinesV(sample[i], 35.0f, C[3]);
        int text_width = MeasureText(std::to_string(i).c_str(), 20);
        DrawText(std::to_string(i).c_str(), sample[i].x - text_width / 2, sample[i].y - 10, 20, C[0]);
    }

	// Draw Music Volume Slider
    Rectangle volumeRect = { ScreenWidth * 0.05f, ScreenHeight * 0.15f, ScreenWidth * 0.1f, ScreenHeight * 0.05f };
    DrawRectangleRounded(volumeRect, 0.2f, 6, C[1]);

    int textWidth = MeasureText("Music Volume", 20);

    DrawText("Music Volume", volumeRect.x + (volumeRect.width - textWidth) / 2, volumeRect.y + (volumeRect.height - 20) / 2, 20, C[0]);

	float volume = DrawVolumeSlider();
	SetMusicVolume(music, volume);

    DrawBack();
}

void GUI::DrawCreditMenu() {
    std::vector<std::string> credit = {
        "Data Structure Visualizer ",
        "HCMUS - VNU | CS163 Project",
        "Supervising Teachers :",
        "   MSc. Truong Phuoc Loc   ",
        "   MSc. Ho Tuan Thanh      ",
        "",
        "This project purpose is to visualize fundamental data structures and algorithms for educational purpose using C++",
        "",
        "",
        "",
        "",
        "Member:",
        "  Tran Le Anh Tuan : HashTable         ",
        "  Huynh Huu Phuc Minh : Linked List    ",
        "  Do Manh Cuong : AVL Tree             ",
        "  Nguyen Cong Kien : Graph             ",
        "",
        "",
        "",
        "Window icon by Dewi Sari - Flaticon",
        "Music track: Horizon by Zambolino"
        "",
        "",
        "",
        "Thank you for taking your time to look at our product.",
        "Have a nice day!"
    };

    float startY = ScreenHeight * 0.5f / 6 + 60;
    float spacing = ScreenHeight / 36.0f;
    for (int i = 0; i < credit.size(); i++) {
        int tw = MeasureText(credit[i].c_str(), 20);
        DrawText(credit[i].c_str(), (ScreenWidth - tw) / 2, startY + i * spacing, 20, C[0]);
    }

    DrawBack();
}

void GUI::DrawSecondMenu() {
    // Menu constants
    const float MENU_WIDTH = ScreenWidth / 5.0f;
    const float MENU_HEIGHT = ScreenHeight;

    // Draw menu background
    DrawRectangleRounded(
        { 0, 0, MENU_WIDTH, MENU_HEIGHT },
        0.1f, 10, C[1]
    );

    // Draw title inside menu
    const char* titleText;
    if (CurrentStruture == HASHTABLE) { titleText = "Hash Table"; }
    else if (CurrentStruture == LINKEDLIST) { titleText = "Linked List"; }
    else if (CurrentStruture == AVLTREE) { titleText = "AVL Tree"; }
    else if (CurrentStruture == GRAPH) { titleText = "Graph"; }
    else { titleText = "Data Structure"; }

    const int TITLE_FONT_SIZE = 28;
    Vector2 titleSize = MeasureTextEx(GetFontDefault(), titleText, TITLE_FONT_SIZE, 1);
    float titleX = (MENU_WIDTH - titleSize.x) / 2;
    float titleY = 20.0f; // Positioned at top of menu
    DrawText(titleText, titleX, titleY, TITLE_FONT_SIZE, C[0]);

    buttonscreen.ConfigureButton(18);

    if (buttonscreen.IsClick()) {
        graph.set_fix_graph(true); is_graph_fixed = true;
        ExportScreenshot();
    }

    if (CurrentStruture == GRAPH && currentInputMode == DIJKSTRA && activemenu_graph != DEFAULT) { return; }
    // Draw all buttons
    if (CurrentStruture == LINKEDLIST) {
        buttoninit.ConfigureButton(0);
        buttoninsert.ConfigureButton(1);
        buttondelete.ConfigureButton(2);
        buttonsearch.ConfigureButton(3);
        buttonclear.ConfigureButton(4);
    }
    else if (CurrentStruture == AVLTREE) {
        buttoninit.ConfigureButton(0);
        buttoninsert.ConfigureButton(1);
        buttondelete.ConfigureButton(2);
        buttonsearch.ConfigureButton(3);
        buttonclear.ConfigureButton(4);
    }
    else if (CurrentStruture == GRAPH) {
        buttoninit.ConfigureButton(0);
        buttoninsert.ConfigureButton(1);
        buttondelete.ConfigureButton(2);
        buttondijkstra.ConfigureButton(3);
        buttonclear.ConfigureButton(4);

        if (currentInputMode != DIJKSTRA) {
            if (is_graph_fixed == true) { buttonunfix.ConfigureButton(16); } else
            if (is_graph_fixed == false) { buttonfix.ConfigureButton(17); }
        }
    }
    else if (CurrentStruture == HASHTABLE) {
        buttoninit.ConfigureButton(0);
        buttoninsert.ConfigureButton(1);
        buttondelete.ConfigureButton(2);
        buttonsearch.ConfigureButton(3);
        buttonclear.ConfigureButton(4);
    }
}

void GUI::ResetMenuState() {
    activemenu_avltree = NONE_AVLTREE;
    activemenuinit_avltree = NONEINITAVLTREE;

    activemenu_graph = DEFAULT;
    GraphRandomStep = 0;
    GraphVertexStep = 0;
    graph.set_running_dijkstra(false);

    inputActive = false;
    currentInputMode = NONE;
}
   
void GUI::DrawHashTable() {
    DrawSecondMenu();
    DrawBack();
    float speedValue = DrawSlider(); // Slider tốc độ luôn hiển thị
    DrawInputBox();

    static Pseudocode pseudocode;
    static ExplanationCode explanationcode;
    static bool firstFrame = true;
    static int currentStep = -1;
    static int pendingKey = -1;
    static bool isStepping = false;
    static bool isStepByStepMode = false;
    static string currentOperation = "";
    static bool isAutoHighlighting = false;
    static int autoStep = -1;
    static float timer = 0.0f;

    // Khởi tạo trạng thái ban đầu
    if (firstFrame) {
        pseudocode.SetstringPseudocode("");
        explanationcode.Setstringexplancode("Select Action To Start");
        explanationcode.SetHighLight(0);
        isStepByStepMode = false;
        currentInputMode = NONE;
        inputActive = false;
        firstFrame = false;
    }

    // Xử lý các nút chính
    if (buttoninit.IsClick()) {
        hashtable.setInitMode(HashTable::NONE_INIT);
        currentInputMode = INIT;
        inputActive = true;
        inputstring = "";
        pseudocode.SetstringPseudocode("");
        explanationcode.Setstringexplancode("INIT");
        explanationcode.SetHighLight(1);
        isStepping = false;
        currentStep = -1;
        pendingKey = -1;
        currentOperation = "";
        isAutoHighlighting = false;
        autoStep = -1;
        timer = 0.0f;
    }
    else if (buttoninsert.IsClick()) {
        hashtable.setInitMode(HashTable::NONE_INIT);
        currentInputMode = INSERT;
        inputActive = true;
        inputstring = "";
        pseudocode.SetstringPseudocode("INSERT_HASHTABLE");
        explanationcode.Setstringexplancode("INSERT");
        explanationcode.SetHighLight(1);
        isStepping = false;
        currentStep = -1;
        pendingKey = -1;
        currentOperation = "INSERT";
        isAutoHighlighting = false;
        autoStep = -1;
        timer = 0.0f;
    }
    else if (buttondelete.IsClick()) {
        hashtable.setInitMode(HashTable::NONE_INIT);
        currentInputMode = DELETE;
        inputActive = true;
        inputstring = "";
        pseudocode.SetstringPseudocode("DELETE_HASHTABLE");
        explanationcode.Setstringexplancode("DELETE");
        explanationcode.SetHighLight(1);
        isStepping = false;
        currentStep = -1;
        pendingKey = -1;
        currentOperation = "DELETE";
        isAutoHighlighting = false;
        autoStep = -1;
        timer = 0.0f;
    }
    else if (buttonsearch.IsClick()) {
        hashtable.setInitMode(HashTable::NONE_INIT);
        currentInputMode = SEARCH;
        inputActive = true;
        inputstring = "";
        pseudocode.SetstringPseudocode("SEARCH_HASHTABLE");
        explanationcode.Setstringexplancode("SEARCH");
        explanationcode.SetHighLight(1);
        isStepping = false;
        currentStep = -1;
        pendingKey = -1;
        currentOperation = "SEARCH";
        isAutoHighlighting = false;
        autoStep = -1;
        timer = 0.0f;
    }
    else if (buttonclear.IsClick()) {
        hashtable.clear();
        pseudocode.SetstringPseudocode("");
        explanationcode.Setstringexplancode("Table Deleted.");
        explanationcode.SetHighLight(-1);
        isStepping = false;
        currentStep = -1;
        pendingKey = -1;
        currentOperation = "";
        isAutoHighlighting = false;
        autoStep = -1;
        timer = 0.0f;
        currentInputMode = NONE;
        inputActive = false;
        inputstring = "";
    }

    // Hiển thị nút pause
    if (currentInputMode == INSERT || currentInputMode == DELETE || currentInputMode == SEARCH) {
        buttonpause.ConfigureButton(6.2); // Nút pause ở vị trí 6.2 khi bắt đầu
    }
    else if (isStepByStepMode && !currentOperation.empty()) {
        buttonpause.ConfigureButton(7); // Nút pause ở vị trí 7.5 khi ở step-by-step và có thao tác
    }

    // Hiển thị nút next, prev khi ở chế độ step-by-step và isStepping
    if (isStepByStepMode && isStepping) {
        buttonnext.ConfigureButton(5);  // Nút next ở vị trí 6.4
        buttonprev.ConfigureButton(6);  // Nút prev ở vị trí 6.6
    }

    // Hiển thị nút random và loadfile khi ở chế độ INIT
    if (currentInputMode == INIT) {
        buttonrandom.ConfigureButton(6.3); // Hiển thị nút random
        buttonloadfile.ConfigureButton(7.3); // Hiển thị nút loadfile
    }

    // Xử lý input
    int val = Input(buttonclear.coordinateX, buttonclear.coordinateY + buttonclear.height + 20);

    // Xử lý chế độ INIT
    if (currentInputMode == INIT) {
        if (buttonrandom.IsClick()) {
            hashtable.setInitMode(HashTable::RANDOM_HASHTABLE);
            pseudocode.SetstringPseudocode("");
            explanationcode.Setstringexplancode("INIT");
            explanationcode.SetHighLight(2);
        }
        else if (buttonloadfile.IsClick()) {
            hashtable.setInitMode(HashTable::LOADFILE_HASHTABLE);
            pseudocode.SetstringPseudocode("");
            explanationcode.Setstringexplancode("INIT");
            explanationcode.SetHighLight(3);
        }

        if (val != -1) {
            hashtable.init(val);
            hashtable.setInitMode(HashTable::NONE_INIT);
            inputActive = false;
            currentInputMode = NONE;
            pseudocode.SetstringPseudocode("");
            explanationcode.Setstringexplancode("Initialize table with dimensions " + std::to_string(val) + ".");
            explanationcode.SetHighLight(-1);
        }

        if (hashtable.getInitMode() == HashTable::RANDOM_HASHTABLE) {
            hashtable.handleRandom();
            hashtable.setInitMode(HashTable::NONE_INIT);
            inputActive = false;
            currentInputMode = NONE;
            pseudocode.SetstringPseudocode("");
            explanationcode.Setstringexplancode("Random table generated.");
            explanationcode.SetHighLight(-1);
        }
        else if (hashtable.getInitMode() == HashTable::LOADFILE_HASHTABLE) {
            hashtable.LoadFromFile();
            hashtable.setInitMode(HashTable::NONE_INIT);
            inputActive = false;
            currentInputMode = NONE;
            pseudocode.SetstringPseudocode("");
            explanationcode.Setstringexplancode("Loaded table from file.");
            explanationcode.SetHighLight(-1);
        }
    }
    // Xử lý INSERT, SEARCH, DELETE
    else if (currentInputMode == INSERT && val != -1) {
        if (isStepByStepMode) {
            pendingKey = val;
            isStepping = true;
            currentStep = 0;
            pseudocode.SetHighLight(currentStep);
            hashtable.startInsertStep(pendingKey);
            explanationcode.Setstringexplancode("Starting insertion of value " + std::to_string(val) + ".");
            explanationcode.SetHighLight(0);
            inputActive = false;
            currentInputMode = NONE;
        }
        else {
            if (!isAutoHighlighting) {
                pendingKey = val;
                isAutoHighlighting = true;
                autoStep = 0;
                timer = 0.0f;
                pseudocode.SetHighLight(autoStep);
                explanationcode.Setstringexplancode("Starting insertion of value " + std::to_string(val) + ".");
                explanationcode.SetHighLight(0);
                hashtable.startInsertStep(val);
                inputActive = false;
                currentInputMode = NONE;
            }
        }
    }
    else if (currentInputMode == SEARCH && val != -1) {
        if (isStepByStepMode) {
            pendingKey = val;
            isStepping = true;
            currentStep = 0;
            pseudocode.SetHighLight(currentStep);
            hashtable.startSearchStep(pendingKey);
            explanationcode.Setstringexplancode("Starting search for value " + std::to_string(val) + ".");
            explanationcode.SetHighLight(0);
            inputActive = false;
            currentInputMode = NONE;
        }
        else {
            if (!isAutoHighlighting) {
                pendingKey = val;
                isAutoHighlighting = true;
                autoStep = 0;
                timer = 0.0f;
                pseudocode.SetHighLight(autoStep);
                explanationcode.Setstringexplancode("Starting search for value " + std::to_string(val) + ".");
                explanationcode.SetHighLight(0);
                hashtable.startSearchStep(val);
                inputActive = false;
                currentInputMode = NONE;
            }
        }
    }
    else if (currentInputMode == DELETE && val != -1) {
        if (isStepByStepMode) {
            pendingKey = val;
            isStepping = true;
            currentStep = 0;
            pseudocode.SetHighLight(currentStep);
            hashtable.startDeleteStep(pendingKey);
            explanationcode.Setstringexplancode("Starting deletion of value " + std::to_string(val) + ".");
            explanationcode.SetHighLight(0);
            inputActive = false;
            currentInputMode = NONE;
        }
        else {
            if (!isAutoHighlighting) {
                pendingKey = val;
                isAutoHighlighting = true;
                autoStep = 0;
                timer = 0.0f;
                pseudocode.SetHighLight(autoStep);
                explanationcode.Setstringexplancode("Starting deletion of value " + std::to_string(val) + ".");
                explanationcode.SetHighLight(0);
                hashtable.startDeleteStep(val);
                inputActive = false;
                currentInputMode = NONE;
            }
        }
    }

    // Xử lý nút pause
    if (buttonpause.IsClick()) {
        isStepByStepMode = !isStepByStepMode;
        if (!isStepByStepMode && isStepping) {
            if (pendingKey != -1) {
                if (currentOperation == "INSERT") {
                    hashtable.insert(pendingKey);
                    explanationcode.Setstringexplancode("Inserted value " + std::to_string(pendingKey) + ".");
                }
                else if (currentOperation == "SEARCH") {
                    hashtable.search(pendingKey);
                    explanationcode.Setstringexplancode(hashtable.getStepSearchIndex() != -1 ? "Value " + std::to_string(pendingKey) + " found." : "Value " + std::to_string(pendingKey) + " not found.");
                }
                else if (currentOperation == "DELETE") {
                    hashtable.remove(pendingKey);
                    explanationcode.Setstringexplancode(hashtable.getStepDeleteIndex() != -1 ? "Value " + std::to_string(pendingKey) + " deleted." : "Value " + std::to_string(pendingKey) + " not found.");
                }
                explanationcode.SetHighLight(-1);
                pseudocode.SetHighLight(-1);
            }
            isStepping = false;
            currentStep = -1;
            pendingKey = -1;
            currentOperation = "";
            hashtable.resetStepState();
        }
        explanationcode.Setstringexplancode(isStepByStepMode ? "Switched to Step-by-Step mode." : "Switched to At-Once mode.");
        explanationcode.SetHighLight(-1);
    }

    // Xử lý nút next và prev trong chế độ step-by-step
    if (isStepping && isStepByStepMode) {
        if (buttonnext.IsClick()) {
            currentStep++;
            if (currentOperation == "INSERT") {
                if (currentStep >= 3) {
                    if (hashtable.getStepInsertIndex() != -1) {
                        hashtable.performInsertStep(3);
                        explanationcode.Setstringexplancode("Inserted value " + std::to_string(pendingKey) + " into slot.");
                        explanationcode.SetHighLight(3);
                    }
                    else {
                        explanationcode.Setstringexplancode("Table is full, cannot insert.");
                        explanationcode.SetHighLight(-1);
                    }
                    currentStep = -1;
                    isStepping = false;
                    pseudocode.SetHighLight(-1);
                    hashtable.resetStepState();
                    pendingKey = -1;
                    currentOperation = "";
                }
                else {
                    pseudocode.SetHighLight(currentStep);
                    hashtable.performInsertStep(currentStep);
                    if (currentStep == 1) {
                        explanationcode.Setstringexplancode("Computed index for value " + std::to_string(pendingKey) + ".");
                        explanationcode.SetHighLight(1);
                    }
                    else if (currentStep == 2) {
                        explanationcode.Setstringexplancode(hashtable.getStepCollisionDetected() ? "Collision detected, probing next slot." : "No collision, ready to insert.");
                        explanationcode.SetHighLight(2);
                    }
                }
            }
            else if (currentOperation == "SEARCH") {
                if (currentStep >= 3) {
                    if (hashtable.getStepSearchIndex() != -1) {
                        explanationcode.Setstringexplancode("Value " + std::to_string(pendingKey) + " found.");
                        explanationcode.SetHighLight(3);
                    }
                    else {
                        explanationcode.Setstringexplancode("Value " + std::to_string(pendingKey) + " not found.");
                        explanationcode.SetHighLight(-1);
                    }
                    currentStep = -1;
                    isStepping = false;
                    pseudocode.SetHighLight(-1);
                    hashtable.resetStepState();
                    pendingKey = -1;
                    currentOperation = "";
                }
                else {
                    pseudocode.SetHighLight(currentStep);
                    hashtable.performSearchStep(currentStep);
                    if (currentStep == 1) {
                        explanationcode.Setstringexplancode("Computed index for value " + std::to_string(pendingKey) + ".");
                        explanationcode.SetHighLight(1);
                    }
                    else if (currentStep == 2) {
                        explanationcode.Setstringexplancode(hashtable.getStepCollisionDetected() ? "Collision detected, probing next slot." : "Value not found after probing.");
                        explanationcode.SetHighLight(2);
                    }
                }
            }
            else if (currentOperation == "DELETE") {
                if (currentStep >= 3) {
                    if (hashtable.getStepDeleteIndex() != -1) {
                        hashtable.performDeleteStep(3);
                        explanationcode.Setstringexplancode("Value " + std::to_string(pendingKey) + " deleted from slot.");
                        explanationcode.SetHighLight(3);
                    }
                    else {
                        explanationcode.Setstringexplancode("Value " + std::to_string(pendingKey) + " not found.");
                        explanationcode.SetHighLight(-1);
                    }
                    currentStep = -1;
                    isStepping = false;
                    pseudocode.SetHighLight(-1);
                    hashtable.resetStepState();
                    pendingKey = -1;
                    currentOperation = "";
                }
                else {
                    pseudocode.SetHighLight(currentStep);
                    hashtable.performDeleteStep(currentStep);
                    if (currentStep == 1) {
                        explanationcode.Setstringexplancode("Computed index for value " + std::to_string(pendingKey) + ".");
                        explanationcode.SetHighLight(1);
                    }
                    else if (currentStep == 2) {
                        explanationcode.Setstringexplancode(hashtable.getStepCollisionDetected() ? "Collision detected, probing next slot." : "Value not found after probing.");
                        explanationcode.SetHighLight(2);
                    }
                }
            }
        }
        else if (buttonprev.IsClick()) {
            if (currentStep > 0) {
                currentStep--;
                pseudocode.SetHighLight(currentStep);
                if (currentOperation == "INSERT") {
                    hashtable.revertInsertStep(currentStep);
                    if (currentStep == 0) {
                        explanationcode.Setstringexplancode("Starting insertion of value " + std::to_string(pendingKey) + ".");
                        explanationcode.SetHighLight(0);
                    }
                    else if (currentStep == 1) {
                        explanationcode.Setstringexplancode("Computed index for value " + std::to_string(pendingKey) + ".");
                        explanationcode.SetHighLight(1);
                    }
                    else if (currentStep == 2) {
                        explanationcode.Setstringexplancode(hashtable.getStepCollisionDetected() ? "Collision detected, probing next slot." : "No collision, ready to insert.");
                        explanationcode.SetHighLight(2);
                    }
                }
                else if (currentOperation == "SEARCH") {
                    hashtable.revertSearchStep(currentStep);
                    if (currentStep == 0) {
                        explanationcode.Setstringexplancode("Starting search for value " + std::to_string(pendingKey) + ".");
                        explanationcode.SetHighLight(0);
                    }
                    else if (currentStep == 1) {
                        explanationcode.Setstringexplancode("Computed index for value " + std::to_string(pendingKey) + ".");
                        explanationcode.SetHighLight(1);
                    }
                    else if (currentStep == 2) {
                        explanationcode.Setstringexplancode(hashtable.getStepCollisionDetected() ? "Collision detected, probing next slot." : "Value not found after probing.");
                        explanationcode.SetHighLight(2);
                    }
                }
                else if (currentOperation == "DELETE") {
                    hashtable.revertDeleteStep(currentStep);
                    if (currentStep == 0) {
                        explanationcode.Setstringexplancode("Starting deletion of value " + std::to_string(pendingKey) + ".");
                        explanationcode.SetHighLight(0);
                    }
                    else if (currentStep == 1) {
                        explanationcode.Setstringexplancode("Computed index for value " + std::to_string(pendingKey) + ".");
                        explanationcode.SetHighLight(1);
                    }
                    else if (currentStep == 2) {
                        explanationcode.Setstringexplancode(hashtable.getStepCollisionDetected() ? "Collision detected, probing next slot." : "Value not found after probing.");
                        explanationcode.SetHighLight(2);
                    }
                }
            }
            else {
                currentStep = -1;
                isStepping = false;
                explanationcode.Setstringexplancode(currentOperation == "INSERT" ? "Insertion cancelled." :
                    currentOperation == "SEARCH" ? "Search cancelled." :
                    "Deletion cancelled.");
                explanationcode.SetHighLight(-1);
                pseudocode.SetHighLight(-1);
                hashtable.resetStepState();
                pendingKey = -1;
                currentOperation = "";
            }
        }
    }

    // Xử lý highlight tự động trong chế độ at-once
    if (!isStepByStepMode && isAutoHighlighting) {
        timer += GetFrameTime();
        float timePerStep = 1.0f / speedValue;
        if (timer >= timePerStep) {
            autoStep++;
            timer = 0.0f;

            if (currentOperation == "INSERT") {
                if (autoStep == 1) {
                    hashtable.performInsertStep(1);
                    pseudocode.SetHighLight(1);
                    explanationcode.Setstringexplancode("Computed index for value " + std::to_string(pendingKey) + ".");
                    explanationcode.SetHighLight(1);
                }
                else if (autoStep == 2) {
                    hashtable.performInsertStep(2);
                    pseudocode.SetHighLight(2);
                    if (hashtable.getStepCollisionDetected()) {
                        explanationcode.Setstringexplancode("Collision detected, probing next slot.");
                        explanationcode.SetHighLight(2);
                        autoStep = 1; // Quay lại bước 1 để thăm dò tiếp
                    }
                    else {
                        explanationcode.Setstringexplancode("No collision, ready to insert.");
                        explanationcode.SetHighLight(2);
                    }
                }
                else if (autoStep == 3) {
                    if (hashtable.getStepInsertIndex() != -1) {
                        hashtable.performInsertStep(3);
                        pseudocode.SetHighLight(3);
                        explanationcode.Setstringexplancode("Inserted value " + std::to_string(pendingKey) + " into slot.");
                        explanationcode.SetHighLight(3);
                    }
                    else {
                        pseudocode.SetHighLight(-1);
                        explanationcode.Setstringexplancode("Table is full, cannot insert.");
                        explanationcode.SetHighLight(-1);
                    }
                    isAutoHighlighting = false;
                    autoStep = -1;
                    pendingKey = -1;
                    currentOperation = "";
                    hashtable.resetStepState();
                }
            }
            else if (currentOperation == "SEARCH") {
                if (autoStep == 1) {
                    hashtable.performSearchStep(1);
                    pseudocode.SetHighLight(1);
                    explanationcode.Setstringexplancode("Computed index for value " + std::to_string(pendingKey) + ".");
                    explanationcode.SetHighLight(1);
                }
                else if (autoStep == 2) {
                    hashtable.performSearchStep(2);
                    pseudocode.SetHighLight(2);
                    if (hashtable.getStepCollisionDetected()) {
                        explanationcode.Setstringexplancode("Collision detected, probing next slot.");
                        explanationcode.SetHighLight(2);
                        autoStep = 1;
                    }
                    else {
                        explanationcode.Setstringexplancode(hashtable.getStepSearchIndex() != -1 ? "Value found in slot." : "Value not found after probing.");
                        explanationcode.SetHighLight(2);
                    }
                }
                else if (autoStep == 3) {
                    if (hashtable.getStepSearchIndex() != -1) {
                        pseudocode.SetHighLight(3);
                        explanationcode.Setstringexplancode("Value " + std::to_string(pendingKey) + " found.");
                        explanationcode.SetHighLight(3);
                    }
                    else {
                        pseudocode.SetHighLight(-1);
                        explanationcode.Setstringexplancode("Value " + std::to_string(pendingKey) + " not found.");
                        explanationcode.SetHighLight(-1);
                    }
                    isAutoHighlighting = false;
                    autoStep = -1;
                    pendingKey = -1;
                    currentOperation = "";
                    hashtable.resetStepState();
                }
            }
            else if (currentOperation == "DELETE") {
                if (autoStep == 1) {
                    hashtable.performDeleteStep(1);
                    pseudocode.SetHighLight(1);
                    explanationcode.Setstringexplancode("Computed index for value " + std::to_string(pendingKey) + ".");
                    explanationcode.SetHighLight(1);
                }
                else if (autoStep == 2) {
                    hashtable.performDeleteStep(2);
                    pseudocode.SetHighLight(2);
                    if (hashtable.getStepCollisionDetected()) {
                        explanationcode.Setstringexplancode("Collision detected, probing next slot.");
                        explanationcode.SetHighLight(2);
                        autoStep = 1;
                    }
                    else {
                        explanationcode.Setstringexplancode(hashtable.getStepDeleteIndex() != -1 ? "Value found in slot, ready to delete." : "Value not found after probing.");
                        explanationcode.SetHighLight(2);
                    }
                }
                else if (autoStep == 3) {
                    if (hashtable.getStepDeleteIndex() != -1) {
                        hashtable.performDeleteStep(3);
                        pseudocode.SetHighLight(3);
                        explanationcode.Setstringexplancode("Value " + std::to_string(pendingKey) + " deleted from slot.");
                        explanationcode.SetHighLight(3);
                    }
                    else {
                        pseudocode.SetHighLight(-1);
                        explanationcode.Setstringexplancode("Value " + std::to_string(pendingKey) + " not found.");
                        explanationcode.SetHighLight(-1);
                    }
                    isAutoHighlighting = false;
                    autoStep = -1;
                    pendingKey = -1;
                    currentOperation = "";
                    hashtable.resetStepState();
                }
            }
        }
    }

    // Vẽ HashTable, pseudocode và explanation
    hashtable.draw(isStepByStepMode ? currentStep : autoStep);
    explanationcode.area_text.y = 570;
    pseudocode.area_text.y = explanationcode.area_text.y + explanationcode.area_text.height + 10;
    pseudocode.DrawPseudocode();
    explanationcode.DrawExplancodeArea();
}

void GUI::DrawLinkedList() {
    DrawSecondMenu();
    DrawBack();
    DrawInputBox();
    
    float durationtime = DrawSlider();
    list.SetanimationDurationLinkedList(durationtime);

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

    if (currentInputMode == INIT) {
        buttonloadfile.ConfigureButton(5.3f + 1.0f);
        if (buttonloadfile.IsClick() && LoadFileLinkedList()) {
            inputActive = false;
            currentInputMode = NONE;
        }
    }

    if (inputActive) {
        int val = Input(buttonclear.coordinateX, buttonclear.coordinateY + buttonclear.height + 20);
        if (val != -1) {
            switch (currentInputMode) {
            case INIT: list.clear(); list.rand_list(val); break;
            case INSERT: list.start_animation(LinkedList::AnimationType::INSERT, val); break;
            case DELETE: list.start_animation(LinkedList::AnimationType::DELETE, val); break;
            case SEARCH: list.start_animation(LinkedList::AnimationType::SEARCH, val); search_result_timer = 2.0f; break;
            }
            currentInputMode = NONE;
            inputActive = false;
        }
    }

    if (list.get_search_state() != -1 || list.get_active() != -1) {
        buttonBackward.ConfigureButton(10.0f);
        buttonForward.ConfigureButton(11.0f);
        buttonPausePlay.ConfigureButton(12.0f);
        buttonPausePlay.s = list.get_paused() ? "Play" : "Pause";

        if (buttonBackward.IsClick()) {
            list.step_backward();
        }
        if (buttonForward.IsClick()) {
            list.step_forward();
        }
        if (buttonPausePlay.IsClick()) {
            list.set_paused(!list.get_paused());
        }
    }
    list.update();
    BeginScissorMode(SecondMenuWidth, 0, ScreenWidth - SecondMenuWidth, ScreenHeight);
    list.setDrawOffset(linkedListScrollY);
    list.draw();
    list.descriptionBox.DrawDescriptionBox();
    EndScissorMode();
}

void GUI::DrawAVLTree() {
    Gui.DrawSecondMenu();
    Gui.DrawBack();
    float durationtime = DrawSlider();
    Gui.AnimationAVLTree.SetTime(durationtime);
       
    Gui.DrawInputBox();

    if (buttoninit.IsClick()) {
        Gui.SetActiveMenuAVLTree(INIT_AVLTREE);
        Gui.AnimationAVLTree.pseudocode.SetstringPseudocode("");
        currentInputMode = INIT;
        inputActive = true;
    }
    else if (buttoninsert.IsClick()) {
        Gui.SetActiveMenuAVLTree(INSERT_AVLTREE);
        Gui.AnimationAVLTree.pseudocode.SetstringPseudocode("INSERT");
        currentInputMode = INSERT;
        inputActive = true;
    }
    else if (buttonsearch.IsClick()) {
        Gui.SetActiveMenuAVLTree(SEARCH_AVLTREE);
        Gui.AnimationAVLTree.pseudocode.SetstringPseudocode("SEARCH");
        currentInputMode = SEARCH;
        inputActive = true;
    }
    else if (buttondelete.IsClick()) {
        Gui.SetActiveMenuAVLTree(DELETE_AVLTREE);
        Gui.AnimationAVLTree.pseudocode.SetstringPseudocode("DELETE");
        currentInputMode = DELETE;
        inputActive = true;
    }
    else if (buttonclear.IsClick()) {
        Gui.AnimationAVLTree.explanationcode.Setstringexplancode("");
        tree.Clear(tree.Root);
        tree.NodeList.clear();
    }

    int val = Gui.Input(buttonclear.coordinateX, buttonclear.coordinateY + buttonclear.height + 20);

    if (activemenu_avltree == INIT_AVLTREE) {
        Gui.AnimationAVLTree.explanationcode.Setstringexplancode("Starting Initialization.");
        buttonrandom.ConfigureButton(6.3);
        buttonloadfile.ConfigureButton(7.3);

        if (buttonrandom.IsClick())  Gui.SetActiveMenuInitAVLTree(RANDOM_AVLTREE);
        else if (buttonloadfile.IsClick())  Gui.SetActiveMenuInitAVLTree(LOADFILE_AVLTREE);

        if (val != -1) {
            Gui.AnimationAVLTree.explanationcode.Setstringexplancode("Init : " + to_string(val) + " Node");
            tree.InitAVLTree(val);
            Gui.AnimationAVLTree.SetTree(&tree);
            SetActiveMenuInitAVLTree(NONEINITAVLTREE);
            SetActiveMenuAVLTree(NONE_AVLTREE);
            inputActive = false;
        }
        if (activemenuinit_avltree == RANDOM_AVLTREE) {
            Gui.AnimationAVLTree.explanationcode.Setstringexplancode("Starting Random.");
            tree.Random();
            SetActiveMenuInitAVLTree(NONEINITAVLTREE);
            SetActiveMenuAVLTree(NONE_AVLTREE);
            inputActive = false;
        }
        else if (activemenuinit_avltree == LOADFILE_AVLTREE) {
            Gui.AnimationAVLTree.explanationcode.Setstringexplancode("Starting LoadFile.");
            Gui.LoadFileAVLTree();
            Gui.AnimationAVLTree.SetTree(&tree);
            SetActiveMenuInitAVLTree(NONEINITAVLTREE);
            SetActiveMenuAVLTree(NONE_AVLTREE);
            inputActive = false;
        }
    }
    else if (activemenu_avltree == INSERT_AVLTREE) {
        Gui.AnimationAVLTree.explanationcode.Setstringexplancode("Starting Insertion.");
        if (val != -1) {
            Gui.AnimationAVLTree.StartInsertAnimation(val);
            inputActive = false;
        }
        Gui.AnimationAVLTree.UpdateStepInsert();
    }
    else if (activemenu_avltree == DELETE_AVLTREE) {
        Gui.AnimationAVLTree.explanationcode.Setstringexplancode("Starting Deletion.");
        if (val != -1) {
            Gui.AnimationAVLTree.StartDeleteAnimation(val);
            inputActive = false;
        }
        if (!Gui.AnimationAVLTree.isFinished()) {
            Gui.AnimationAVLTree.UpdateStepDelete();
        }
    }
    else if (activemenu_avltree == SEARCH_AVLTREE) {
        Gui.AnimationAVLTree.explanationcode.Setstringexplancode("Starting Search.");
        cout << val << " ";
        if (val != -1) {
            Gui.AnimationAVLTree.StartSearchAnimation(val); 
            inputActive = false;
        }
        Gui.AnimationAVLTree.UpdateStepSearch(val);
    }
    Gui.AnimationAVLTree.explanationcode.DrawExplancodeArea();
    Gui.AnimationAVLTree.pseudocode.DrawPseudocode();
    Gui.AnimationAVLTree.SetTree(&tree);
    tree.DrawTree();
}

void GUI::DrawGraph() {
    Gui.DrawSecondMenu();
    Gui.DrawBack();

    Gui.DrawInputBox();

    if (buttoninit.IsClick()) {
        ResetMenuState();
        currentInputMode = INIT;
        inputActive = true;
        inputstring = "";
    }
    if (buttoninsert.IsClick()) {
        ResetMenuState();
        currentInputMode = INSERT;
        inputActive = true;
        inputstring = "";
    }
    if (buttondelete.IsClick()) {
        if (graph.get_active1() >= 0) { graph.delete_node(graph.get_active1()); }
        else if (graph.get_active2().first >= 0 && graph.get_active2().second >= 0) { graph.delete_edge(graph.get_active2().first, graph.get_active2().second); }
        else {
            ResetMenuState();
            currentInputMode = DELETE;
            inputActive = true;
            inputstring = "";
        }
    }
    if (buttondijkstra.IsClick()) {
        ResetMenuState();
        currentInputMode = DIJKSTRA;
        inputActive = true;
        inputstring = "";
    }
    if (buttonclear.IsClick()) {
        ResetMenuState();
        graph.clear();
        currentInputMode = NONE;
    }
    if (is_graph_fixed == false && buttonfix.IsClick()) { is_graph_fixed = true; graph.set_fix_graph(true); }
    if (is_graph_fixed == true && buttonunfix.IsClick()) { is_graph_fixed = false; graph.set_fix_graph(false); }

    int val = Gui.Input(buttonclear.coordinateX, buttonclear.coordinateY + buttonclear.height + 20);

    switch (currentInputMode) {
    case INIT: {
        switch (activemenu_graph) {
        case DEFAULT: {
            buttonrandom.ConfigureButton(5.5);
            buttonloadfile.ConfigureButton(6.5);

            if (buttonrandom.IsClick()) {
                GraphRandomStep = 0;
				activemenu_graph = INIT_RAND;
            }
            if (buttonloadfile.IsClick()) {
                LoadFileGraph();

                inputActive = false;
                currentInputMode = NONE;
            }

            break;
        }
        case INIT_RAND: {
            static int n_vertex = -1;
            static int n_edge = -1;

            if (GraphRandomStep == 0) { GraphRandomStep = 1; }

            float startY = buttonclear.coordinateY + ScreenHeight / 4.5f;
			float spacing = ScreenHeight / 36.0f;
            if (GraphRandomStep < 3) { DrawText("Generating Random Graph", buttonclear.coordinateX, startY, 20, C[0]); }
            else { DrawText("Generated Random Graph", buttonclear.coordinateX, startY, 20, C[0]); }
            if (GraphRandomStep > 1) {
                string text1 = to_string(n_vertex) + " Vertices";
                DrawText(text1.c_str(), buttonclear.coordinateX, startY + spacing * 1, 20, C[0]);
                if (GraphRandomStep > 2) {
                    string text2 = to_string(n_edge) + " Edges";
                    DrawText(text2.c_str(), buttonclear.coordinateX, startY + spacing * 2, 20, C[0]);
                }
            }

            if (val != -1) {
                if (GraphRandomStep == 1) {
                    n_vertex = val;
                    GraphRandomStep = 2;
                }
                else
                    if (GraphRandomStep == 2) {
                        n_edge = val;

                        graph.clear();
                        if (!graph.rand_graph(n_vertex, n_edge)) { ResetMenuState(); }

                        GraphRandomStep = 3;
                    }
            }
            if (GraphRandomStep == 3) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    n_vertex = -1;
                    n_edge = -1;

                    GraphRandomStep = 0;
					activemenu_graph = DEFAULT;
                    inputActive = false;
                    currentInputMode = NONE;
                }
            }

            break;
        }
		default: break;
        }
        break;
    }
    case INSERT: {
        switch (activemenu_graph) {
        case DEFAULT: {
            buttonvertex.ConfigureButton(5.5);
            buttonedge.ConfigureButton(6.5);

            if (buttonvertex.IsClick()) {
                activemenu_graph = INSERT_V;
            }
            if (buttonedge.IsClick()) {
                GraphVertexStep = 0;
                activemenu_graph = INSERT_E;
            }

            break;
        }
        case INSERT_V: {
            if (val != -1) {
                graph.add_node(val);

                activemenu_graph = DEFAULT;
                inputActive = false;
                currentInputMode = NONE;
            }

            break;
        }
        case INSERT_E: {
            static int vertex1 = -1;
            static int vertex2 = -1;
            static int weight = -1;

            if (GraphVertexStep == 0) { GraphVertexStep = 1; }

            float startY = buttonclear.coordinateY + ScreenHeight / 4.5f;
            float spacing = ScreenHeight / 36.0f;
            if (GraphVertexStep < 4) { DrawText("Drawing Edge", buttonclear.coordinateX, startY, 20, C[0]); }
            else { DrawText("Drawn Edge", buttonclear.coordinateX, startY, 20, C[0]); }
            if (GraphVertexStep > 1) {
                string text1 = "From Vertex " + to_string(vertex1);
                DrawText(text1.c_str(), buttonclear.coordinateX, startY + spacing * 1, 20, C[0]);
                if (GraphVertexStep > 2) {
                    string text2 = "To Vertex " + to_string(vertex2);
                    DrawText(text2.c_str(), buttonclear.coordinateX, startY + spacing * 2, 20, C[0]);
                    if (GraphVertexStep > 3) {
                        string text3 = "Weight: " + to_string(weight);
                        DrawText(text3.c_str(), buttonclear.coordinateX, startY + spacing * 3, 20, C[0]);
                    }
                }
            }

            if (val != -1) {
                if (GraphVertexStep == 1) {
                    vertex1 = val;
                    GraphVertexStep = 2;
                }
                else if (GraphVertexStep == 2) {
                    vertex2 = val;
                    GraphVertexStep = 3;
                }
                else if (GraphVertexStep == 3) {
                    weight = val;
                    if (!graph.add_edge(vertex1, vertex2, weight)) { ResetMenuState(); }

                    GraphVertexStep = 4;

                }
            }
            if (GraphVertexStep == 4) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    vertex1 = -1;
                    vertex2 = -1;
                    weight = -1;

                    GraphVertexStep = 0;
                    activemenu_graph = DEFAULT;
                    inputActive = false;
                    currentInputMode = NONE;
                }
            }

            break;
        }
        default: break;
        }
        break;
    }
    case DELETE: {
        switch (activemenu_graph) {
        case DEFAULT: {
            buttonvertex.ConfigureButton(5.5);
            buttonedge.ConfigureButton(6.5);
            if (buttonvertex.IsClick()) {
                activemenu_graph = DELETE_V;
            }
            if (buttonedge.IsClick()) {
                GraphVertexStep = 0;
                activemenu_graph = DELETE_E;
            }
            break;
        }
        case DELETE_V: {
            if (val != -1) {
                graph.delete_node(val);

                activemenu_graph = DEFAULT;
                inputActive = false;
                currentInputMode = NONE;
            }
            break;
        }
        case DELETE_E: {
            static int vertex1 = -1;
            static int vertex2 = -1;

            if (GraphVertexStep == 0) { GraphVertexStep = 1; }

            float startY = buttonclear.coordinateY + ScreenHeight / 4.5f;
            float spacing = ScreenHeight / 36.0f;
            if (GraphVertexStep < 3) { DrawText("Deleting Edge", buttonclear.coordinateX, startY, 20, C[0]); }
            else { DrawText("Deleted Edge", buttonclear.coordinateX, startY, 20, C[0]); }
            if (GraphVertexStep > 1) {
                string text1 = "From Vertex " + to_string(vertex1);
                DrawText(text1.c_str(), buttonclear.coordinateX, startY + spacing * 1, 20, C[0]);
                if (GraphVertexStep > 2) {
                    string text2 = "To Vertex " + to_string(vertex2);
                    DrawText(text2.c_str(), buttonclear.coordinateX, startY + spacing * 2, 20, C[0]);
                }
            }

            if (val != -1) {
                if (GraphVertexStep == 1) {
                    vertex1 = val;
                    GraphVertexStep = 2;
                }
                else if (GraphVertexStep == 2) {
                    vertex2 = val;
					if (!graph.delete_edge(vertex1, vertex2)) { ResetMenuState(); }

                    GraphVertexStep = 3;
                }
            }
            if (GraphVertexStep == 3) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    vertex1 = -1;
                    vertex2 = -1;

                    GraphVertexStep = 0;
                    activemenu_graph = DEFAULT;
                    inputActive = false;
                    currentInputMode = NONE;
                }
            }
            break;
        }
        default: break;
        }
        break;
    }
    case DIJKSTRA: {
        static bool isAuto = true;

        switch (activemenu_graph) {
        case DEFAULT: {
            buttonstep.ConfigureButton(5.5);
            buttonauto.ConfigureButton(6.5);
            if (buttonstep.IsClick()) {
                isAuto = false;
                activemenu_graph = DIJKSTRA_ST;
            }
            if (buttonauto.IsClick()) {
                isAuto = true;
                activemenu_graph = DIJKSTRA_ST;
            }
            break;
        }
        case DIJKSTRA_ST: {
            if (val != -1) {
                dijkstra_animation.load_state_general(val);
                dijkstra_animation.set_auto(isAuto);
				graph.set_running_dijkstra(true);
				graph.set_showing_code(true);
				activemenu_graph = DIJKSTRA_RUN;
			}
            break;
        }
        case DIJKSTRA_RUN: {
            dijkstra_animation.render();

            if (dijkstra_animation.is_finnished()) {
                graph.set_showing_code(false);
                activemenu_graph = DIJKSTRA_TG;
            }
            else {
				if (isAuto) {
					buttonpause.ConfigureButton(13);
					float speed = DrawSlider();
					//dijkstra_animation.set_speed(speed);
					dijkstra_animation.set_duration(speed);

                    dijkstra_animation.next_state();

					if (buttonpause.IsClick()) { isAuto = false; dijkstra_animation.set_auto(isAuto); }
                }
                else {
					buttonfinal.ConfigureButton(12);
					buttonrun.ConfigureButton(13);
                    buttonnext.ConfigureButton(14);
					buttonprev.ConfigureButton(15);

                    if (buttonnext.IsClick()) { dijkstra_animation.next_state(); }
                    if (buttonprev.IsClick()) { dijkstra_animation.prev_state(); }
                    if (buttonfinal.IsClick()) { dijkstra_animation.show_distance(); graph.set_showing_code(false); activemenu_graph = DIJKSTRA_TG; }
                    if (buttonrun.IsClick()) { isAuto = true; dijkstra_animation.set_auto(isAuto); }
                }
            }
            break;
        }
        case DIJKSTRA_TG: {
            if (val != -1) {
                dijkstra_animation.load_state_paths(val);
                activemenu_graph = DIJKSTRA_PTH;
            }

            buttonreturn.ConfigureButton(12);
            if (buttonreturn.IsClick()) {
                ResetMenuState();
            }
            break;
        }
        case DIJKSTRA_PTH: {
            dijkstra_animation.render_path();

            buttonreturn.ConfigureButton(12);
            if (buttonreturn.IsClick()) {
				dijkstra_animation.show_distance();
				activemenu_graph = DIJKSTRA_TG;
            }
            break;
        }

        default: break;
        }
        break;
    }

    default: break;
    }

    graph.update();
    graph.draw();
}

bool GUI::LoadFileLinkedList() {
    list.clear();
    const char* path = tinyfd_openFileDialog(
        "Open LinkedList File", "", 0, nullptr, nullptr, 0
    );
    if (path == nullptr) return false; 
    ifstream ifs(path);
    if (!ifs.is_open()) return false;
    int x;
    while (ifs >> x) list.add_node(x);
    ifs.close();
    return true;
}

bool GUI::LoadFileAVLTree() {
    tree.Clear(tree.Root);
    tree.NodeList.clear();
    const char* path = tinyfd_openFileDialog(
        "Open AVL File", "", 0, nullptr, nullptr, 0
    );
    if (path == nullptr) return false;

    ifstream ifs(path);

    if (ifs.is_open() == false) return false;


    int x;
    while (ifs >> x) {
        tree.Insert(tree.Root, x, tree.NodeList, true);
        tree.balanceTree();
    }
    ifs.close();
    return true;

}

bool GUI::LoadFileGraph() {
    const char* path = tinyfd_openFileDialog("Open Graph File", "", 0, nullptr, nullptr, 0);

    if (path == nullptr) return false;

    ifstream ifs(path);

    if (ifs.is_open() == false) return false;

    graph.input_graph(ifs);

    ifs.close();

    return true;
}

bool GUI::ExportScreenshot() {
    const char* filterPatterns[1] = { "*.png" };
    const char* savePath = tinyfd_saveFileDialog("Save Screenshot", "screenshot.png", 1, filterPatterns, NULL);

    if (savePath) {
        // Create a RenderTexture and copy screen contents
        RenderTexture2D target = LoadRenderTexture(ScreenWidth, ScreenHeight);
        BeginTextureMode(target);
        ClearBackground(C[4]); 
        switch (CurrentStruture) {
        case HASHTABLE: DrawHashTable(); break;
        case LINKEDLIST: DrawLinkedList(); break;
        case AVLTREE: DrawAVLTree(); break;
        case GRAPH: DrawGraph(); break;
        default: break;
        }
        EndTextureMode();

        // Extract image and export
        Image screenshot = LoadImageFromTexture(target.texture);
        ImageFlipVertical(&screenshot);
        bool success = ExportImage(screenshot, savePath);

        // Cleanup
        UnloadImage(screenshot);
        UnloadRenderTexture(target);

        return success;
    }

    return false;
}

void GUI::DrawBack() {

    Vector2 BackPos = { ScreenWidth / 5.0f * 0.075f , 25 };
    float backWidth = ImageBack.width;
    float backHeight = ImageBack.height;
    Rectangle backbutton = { BackPos.x, BackPos.y, backWidth, backHeight };

    bool isHovered = CheckCollisionPointRec(GetMousePosition(), backbutton);

    Color tintColor = isHovered ? Color{ 255, 255, 255, 200 } : C[1];
    DrawTexturePro(
        ImageBack,
        { 0, 0, (float)ImageBack.width, (float)ImageBack.height },
        {BackPos.x, BackPos.y,50, 50 },
        { 0, 0 },
        0.0f,
        tintColor
    );

    if (isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CurrentStruture == LINKEDLIST) list.clear();
        if (CurrentStruture == AVLTREE) {
            tree.Clear(tree.Root);
            tree.NodeList.clear();
            Gui.AnimationAVLTree.explanationcode.Setstringexplancode("");
            activemenu_avltree = NONE_AVLTREE;
        }
        if (CurrentStruture == GRAPH) graph.clear();

        CurrentStruture = MENU;
        inputActive = false;
        currentInputMode = NONE;
        search_result_timer = 0.0f;
    }
}

void GUI::DrawInputBox() {
    if (!inputActive && currentInputMode != INIT) return;

    // Style constants matching other buttons
    const float MENU_WIDTH = ScreenWidth / 5.0f;
    const float BUTTON_WIDTH = MENU_WIDTH * 0.85f;
    const float BUTTON_HEIGHT = 30.0f;
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
    if (CurrentStruture == LINKEDLIST) {
        switch (currentInputMode) {
        case INIT:    labelText = "Init Nodes: "; break;
        case INSERT:  labelText = "Insert Value: "; break;
        case DELETE:  labelText = "Delete Value: "; break;
        case SEARCH:  labelText = "Search Value: "; break;
        default:      return;
        }
    }
    if (CurrentStruture == AVLTREE) {
        switch (currentInputMode) {
        case INIT:    labelText = "Init Value: "; break;
        case INSERT:  labelText = "Insert Value: "; break;
        case DELETE:  labelText = "Delete Value: "; break;
        case SEARCH:  labelText = "Search Value: "; break;
        default:      return;
        }
    }
    if (CurrentStruture == GRAPH) {
        switch (currentInputMode) {
        case INIT:
            if (activemenu_graph == DEFAULT) { return; }
            switch (GraphRandomStep) { 
			case 1: labelText = "Number of Vertex: "; break;
			case 2: labelText = "Number of Edges: "; break;
			default: return;
            }
            break;
        case INSERT:
            switch (activemenu_graph) {
            case INSERT_V: labelText = "Insert Vertex: "; break;
            case INSERT_E:
                switch (GraphVertexStep) {
                case 1: labelText = "From Vertex: "; break;
                case 2: labelText = "To Vertex: "; break;
                case 3: labelText = "Weight: "; break;
                default: return;
                }
                break;
            default: return;
            }
            break;
        case DELETE:
            switch (activemenu_graph) {
            case DELETE_V: labelText = "Delete Vertex: "; break;
                //case DELETE_E: labelText = (GraphVertexStep == 1) ? "From Vertex: " : "To Vertex: "; break;
            case DELETE_E:
                switch (GraphVertexStep) {
                case 1: labelText = "From Vertex: "; break;
                case 2: labelText = "To Vertex: "; break;
                default: return;
                }
                break;
            default: return;
            }
            break;
        case DIJKSTRA:
            switch (activemenu_graph) {
            case DIJKSTRA_ST: labelText = "Starting Vertex: "; break;
            case DIJKSTRA_TG: labelText = "Target Vertex: "; break;
            default: return;
            }
            break;
        default:      return;
        }
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
    //DrawText(inputstring.c_str(), posX, posY, 20, BLACK);

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) {
        if (inputstring.empty()) return -1;
        try {
            int val = std::stoi(inputstring);
            //std::cout << "Value: " << val << std::endl;
            inputstring = "";
            return val;
        }
        catch (const std::exception& e) {
            //std::cout << "Invalid input: " << e.what() << std::endl;
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

float GUI::DrawSlider() {
    const float minValue = 0.1f;
    const float maxValue = 2.0f;

    float x = (ScreenWidth / 5.0f) * 0.075f;
    float y = ScreenHeight - 30;
    float width = (ScreenWidth / 5.0f) * 0.85;
    float height = 7.0f;

    Rectangle sliderRect = { x, y, width, height };
    DrawRectangleRec(sliderRect, C[3]);

    static float handlePos = x + ((1 - minValue) / (float)(maxValue - minValue)) * width;
    DrawCircle((int)handlePos, (int)y + height / 2, height * 1.5f, C[2]);

    static bool is_dragging = false;
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointCircle(mouse, { handlePos, y + height / 2 }, height * 1.5f)) { is_dragging = true; }
    if (IsMouseButtonUp(MOUSE_LEFT_BUTTON)) { is_dragging = false; }

    if (is_dragging) {
        handlePos = Clamp(mouse.x, x, x + width);
    }

    float value = minValue + (((handlePos - x) / (float)width)) * (maxValue - minValue);
    char buffer[32];
    sprintf_s(buffer, sizeof(buffer), "%.3f", value);

	DrawText(buffer, handlePos - MeasureText(buffer, 20) / 2, y - 30, 20, C[0]);
    return maxValue - value;
}

float GUI::DrawVolumeSlider() {
    const float minValue = 0.0f;
    const float maxValue = 1.0f;

    float x = ScreenWidth * 0.30f;
    float y = ScreenHeight * 0.17f;
    float width = (ScreenWidth) * 0.45;
    float height = 7.0f;

    Rectangle sliderRect = { x, y, width, height };
    DrawRectangleRec(sliderRect, C[3]);

    static float handlePos = x + ((1 - minValue) / (float)(maxValue - minValue)) * width;
    DrawCircle((int)handlePos, (int)y + height / 2, height * 1.5f, C[2]);

    static bool is_dragging = false;
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointCircle(mouse, { handlePos, y + height / 2 }, height * 1.5f)) { is_dragging = true; }
    if (IsMouseButtonUp(MOUSE_LEFT_BUTTON)) { is_dragging = false; }

    if (is_dragging) {
        handlePos = Clamp(mouse.x, x, x + width);
    }

    float value = minValue + (((handlePos - x) / (float)width)) * (maxValue - minValue);
    char buffer[32];
    sprintf_s(buffer, sizeof(buffer), "%.2f", value);

    DrawText(buffer, handlePos - x / float(width) - minValue, ScreenHeight - 80, 20, WHITE);
    return value;
}

void GUI::LoadSource() {
    ImageBack = LoadTexture("../assets/Arrow_Back.png");
}