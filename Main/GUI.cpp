#include <iostream>
#include <string>
#include "GUI.hpp"
#include "Graph.hpp"

using namespace std;

GUI Gui;

TypeDataStructure CurrentStruture = MENU;

GUI::GUI()
	: insertanimationavltree(&tree), graph(false), dijkstra_animation(graph)
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

    for (int i = 0; i < 6; i++) { C[i] = ColorPalette[1][i]; }

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
		else if (CurrentStruture == THEME) {
			Gui.DrawThemeMenu();
		}
        EndDrawing();
    }

    CloseWindow();
}

void GUI::DrawMainMenu() {

    //Font custom = LoadFont("../../Data-Structure-Visualization/assets/PublicSans-Bold.ttf");
    //DrawTextEx(customfont, "Choose Data Structure", { ScreenWidth * float(2) / 5, ScreenHeight * float(5) / 6 }, 60, 1, C[0]);
    DrawText("Choose Data Structure", ScreenWidth * float(2) / 5, ScreenHeight * float(0.5) / 6, 40, C[0]);

   	Rectangle HASHTABLEBUTTON = { ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	Rectangle LINKEDLISTBUTTON = { ScreenWidth * float(3) / 5, ScreenHeight * float(1) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	Rectangle AVLTREEBUTTON = { ScreenWidth * float(1) / 5, ScreenHeight * float(3) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	Rectangle GRAPHBUTTON = { ScreenWidth * float(3) / 5, ScreenHeight * float(3) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	Rectangle THEMEBUTTON = { ScreenWidth * float(2.25) / 5, ScreenHeight * float(4.5) / 5, ScreenWidth * float(1) / 10, ScreenHeight * float(1) / 18 };

	DrawRectangleRounded(HASHTABLEBUTTON, 0.3f, 10, C[2]);
	DrawRectangleRounded(LINKEDLISTBUTTON, 0.3f, 10, C[2]);
	DrawRectangleRounded(AVLTREEBUTTON, 0.3f, 10, C[2]);
	DrawRectangleRounded(GRAPHBUTTON, 0.3f, 10, C[2]);

    DrawText("HASHTABLE", ScreenWidth * float(1) / 5 + 20, ScreenHeight * float(1) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2, 20, C[0]);
    DrawText("LINKEDLIST", ScreenWidth * float(3) / 5 + 20, ScreenHeight * float(1) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2, 20, C[0]);
    DrawText("AVLTREE", ScreenWidth * float(1) / 5 + 20, ScreenHeight * float(3) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2, 20, C[0]);
    DrawText("GRAPH", ScreenWidth * float(3) / 5 + 20, ScreenHeight * float(3) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2, 20, C[0]);

    DrawRectangleRounded(THEMEBUTTON, 0.3f, 10, C[2]);
    DrawText("THEME", THEMEBUTTON.x + (THEMEBUTTON.width - MeasureText("THEME", 20)) / 2, THEMEBUTTON.y + (THEMEBUTTON.height - 20) / 2, 20, C[0]);

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
        else if (CheckCollisionPointRec(mouse, THEMEBUTTON)) {
			CurrentStruture = THEME;
        }
    }
}

void GUI::DrawThemeMenu() {
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

            DrawText(std::to_string(i+j).c_str(), posX + displaceX, posY + displaceY, 20, C[0]);
        }
    }
    for (int i = 0; i < 3; i++) {
		if (i == 0) { DrawCircleV(sample[i], 35.0f, C[5]); } else { DrawCircleV(sample[i], 35.0f, C[1]); }
        DrawCircleLinesV(sample[i], 35.0f, C[3]);
        int text_width = MeasureText(std::to_string(i).c_str(), 20);
        DrawText(std::to_string(i).c_str(), sample[i].x - text_width / 2, sample[i].y - 10, 20, C[0]);
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

void GUI::DrawLinkedList(){
    Gui.DrawSecondMenu();
    Gui.DrawBack();

    // Draw the reusable input box at a fixed position
    Gui.DrawInputBox();

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

    Gui.DrawInputBox();

    if (buttoninit.IsClick()) {
        Gui.SetActiveMenuAVLTree(INIT_AVLTREE);
        currentInputMode = INIT;
        inputActive = true;
    }
    else if (buttoninsert.IsClick()) {
        Gui.SetActiveMenuAVLTree(INSERT_AVLTREE);
        currentInputMode = INSERT;
        inputActive = true;
    }
    else if (buttonsearch.IsClick()) {
        Gui.SetActiveMenuAVLTree(SEARCH_AVLTREE);
        currentInputMode = SEARCH;
        inputActive = true;
    }
    else if (buttondelete.IsClick()) {
        Gui.SetActiveMenuAVLTree(DELETE_AVLTREE);
        currentInputMode = DELETE;
        inputActive = true;
    }
    else if (buttonclear.IsClick()) {
        tree.Clear(tree.Root);
        tree.NodeList.clear();
    }

    int val = Gui.Input(buttonclear.coordinateX, buttonclear.coordinateY + buttonclear.height + 20);

    if (activemenu_avltree == INIT_AVLTREE) {
        buttonrandom.ConfigureButton(6.3);
        buttonloadfile.ConfigureButton(7.3);

        if (buttonrandom.IsClick())  Gui.SetActiveMenuInitAVLTree(RANDOM_AVLTREE);
        else if (buttonloadfile.IsClick())  Gui.SetActiveMenuInitAVLTree(LOADFILE_AVLTREE);

        if (val != -1) {
            tree.InitAVLTree(val);
            Gui.insertanimationavltree.SetTree(&tree);
            SetActiveMenuInitAVLTree(NONEINITAVLTREE);
            SetActiveMenuAVLTree(NONE_AVLTREE);
            inputActive = false;
        }
        if (activemenuinit_avltree == RANDOM_AVLTREE) {
            tree.Random();
            SetActiveMenuInitAVLTree(NONEINITAVLTREE);
            SetActiveMenuAVLTree(NONE_AVLTREE);
            inputActive = false;
        }
        else if (activemenuinit_avltree == LOADFILE_AVLTREE) {
            Gui.LoadFileAVLTree();
            Gui.insertanimationavltree.SetTree(&tree);
            SetActiveMenuInitAVLTree(NONEINITAVLTREE);
            SetActiveMenuAVLTree(NONE_AVLTREE);
            inputActive = false;
        }
    }
    else if (activemenu_avltree == INSERT_AVLTREE) {
        cout << val << " ";
        if (val != -1) {
            Gui.insertanimationavltree.StartInsertAnimation(val);
            inputActive = false;
        }
        Gui.insertanimationavltree.UpdateStep();
    }
    else if (activemenu_avltree == DELETE_AVLTREE) {
        if (val != -1) {
            Gui.insertanimationavltree.DeleteAnimation(val);
            inputActive = false;
        }
        Gui.insertanimationavltree.UpdateStepDelete();

    }
    Gui.insertanimationavltree.SetTree(&tree);
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

    int val = Gui.Input(buttonclear.coordinateX, buttonclear.coordinateY + buttonclear.height + 20);
    
    switch (currentInputMode) {
    case INIT: {
        DrawLineEx({ 0, (float)ScreenHeight / 2.36f }, { ScreenWidth / 5, (float)ScreenHeight / 2.36f }, 2.0f, C[0]);
        buttonrandom.ConfigureButton(5);
        buttonloadfile.ConfigureButton(6);

        if (buttonrandom.IsClick()) {
            GraphRandomStep = 0;
            currentInputMode = RANDOM;
        }
        if (buttonloadfile.IsClick()) {
            LoadFileGraph();

            inputActive = false;
            currentInputMode = NONE;
        }

        break;
    }
    case RANDOM: {
        static int n_vertex = -1;
        static int n_edge = -1;

        if (GraphRandomStep == 0) { GraphRandomStep = 1; }

        if (GraphRandomStep < 3) { DrawText("Generating Random Graph", buttonclear.coordinateX, buttonclear.coordinateY + 125.0f, 20, C[0]); }
        else { DrawText("Generated Random Graph", buttonclear.coordinateX, buttonclear.coordinateY + 125.0f, 20, C[0]); }
        if (GraphRandomStep > 1) {
            string text1 = to_string(n_vertex) + " Vertices";
            DrawText(text1.c_str(), buttonclear.coordinateX, buttonclear.coordinateY + 150.0f, 20, C[0]);
            if (GraphRandomStep > 2) {
                string text2 = to_string(n_edge) + " Edges";
                DrawText(text2.c_str(), buttonclear.coordinateX, buttonclear.coordinateY + 175.0f, 20, C[0]);
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
                    graph.rand_graph(n_vertex, n_edge);

                    GraphRandomStep = 3;
                }
        }
        if (GraphRandomStep == 3) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                n_vertex = -1;
                n_edge = -1;

                GraphRandomStep = 0;
                inputActive = false;
                currentInputMode = NONE;
            }
        }

        break;
    }
    case INSERT: {
        switch (activemenu_graph) {
        case DEFAULT: {
            DrawLineEx({ 0, (float)ScreenHeight / 2.36f }, { ScreenWidth / 5, (float)ScreenHeight / 2.36f }, 2.0f, C[0]);
            buttonvertex.ConfigureButton(5);
            buttonedge.ConfigureButton(6);

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

            if (GraphVertexStep < 4) { DrawText("Drawing Edge", buttonclear.coordinateX, buttonclear.coordinateY + 125.0f, 20, C[0]); }
            else { DrawText("Drawn Edge", buttonclear.coordinateX, buttonclear.coordinateY + 125.0f, 20, C[0]); }
            if (GraphVertexStep > 1) {
                string text1 = "From Vertex " + to_string(vertex1);
                DrawText(text1.c_str(), buttonclear.coordinateX, buttonclear.coordinateY + 150.0f, 20, C[0]);
                if (GraphVertexStep > 2) {
                    string text2 = "To Vertex " + to_string(vertex2);
                    DrawText(text2.c_str(), buttonclear.coordinateX, buttonclear.coordinateY + 175.0f, 20, C[0]);
                    if (GraphVertexStep > 3) {
                        string text3 = "Weight: " + to_string(weight);
                        DrawText(text3.c_str(), buttonclear.coordinateX, buttonclear.coordinateY + 200.0f, 20, C[0]);
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
                    graph.add_edge(vertex1, vertex2, weight);

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
            DrawLineEx({ 0, (float)ScreenHeight / 2.36f }, { ScreenWidth / 5, (float)ScreenHeight / 2.36f }, 2.0f, C[0]);
            buttonvertex.ConfigureButton(5);
            buttonedge.ConfigureButton(6);
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

            if (GraphVertexStep < 3) { DrawText("Deleting Edge", buttonclear.coordinateX, buttonclear.coordinateY + 125.0f, 20, C[0]); }
            else { DrawText("Deleted Edge", buttonclear.coordinateX, buttonclear.coordinateY + 125.0f, 20, C[0]); }
            if (GraphVertexStep > 1) {
                string text1 = "From Vertex " + to_string(vertex1);
                DrawText(text1.c_str(), buttonclear.coordinateX, buttonclear.coordinateY + 150.0f, 20, C[0]);
                if (GraphVertexStep > 2) {
                    string text2 = "To Vertex " + to_string(vertex2);
                    DrawText(text2.c_str(), buttonclear.coordinateX, buttonclear.coordinateY + 175.0f, 20, C[0]);
                }
            }

            if (val != -1) {
                if (GraphVertexStep == 1) {
                    vertex1 = val;
                    GraphVertexStep = 2;
                }
                else if (GraphVertexStep == 2) {
                    vertex2 = val;
                    graph.delete_edge(vertex1, vertex2);

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
            DrawLineEx({ 0, (float)ScreenHeight / 2.36f }, { ScreenWidth / 5, (float)ScreenHeight / 2.36f }, 2.0f, C[0]);
            buttonstep.ConfigureButton(5);
            buttonauto.ConfigureButton(6);
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
				activemenu_graph = DIJKSTRA_RUN;
			}
            break;
        }
        case DIJKSTRA_RUN: {
            dijkstra_animation.render();

            if (dijkstra_animation.is_finnished()) {
                activemenu_graph = DIJKSTRA_TG;
            }
            else {
				if (isAuto) {
					buttonpause.ConfigureButton(10);
					int speed = DrawSlider(5, 90);
					dijkstra_animation.set_speed(speed);

                    dijkstra_animation.next_state();

					if (buttonpause.IsClick()) { isAuto = false; dijkstra_animation.set_auto(isAuto); }
                }
                else {
					buttonfinal.ConfigureButton(9);
					buttonrun.ConfigureButton(10);
                    buttonnext.ConfigureButton(11);
					buttonprev.ConfigureButton(12);

                    if (buttonnext.IsClick()) { dijkstra_animation.next_state(); }
                    if (buttonprev.IsClick()) { dijkstra_animation.prev_state(); }
                    if (buttonfinal.IsClick()) { dijkstra_animation.show_distance(); activemenu_graph = DIJKSTRA_TG; }
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
        if (CurrentStruture == GRAPH) graph.clear();

        CurrentStruture = MENU;
        inputActive = false;
        currentInputMode = NONE;
        search_result_timer = 0.0f;
    }
}

void GUI::DrawInputBox() {
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
        case RANDOM:
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

int GUI::DrawSlider(float minValue, float maxValue) {
    float x = (ScreenWidth / 5.0f) * 0.075f;
	float y = ScreenHeight / 8.0f + 11 * 55.0f;
    float width = (ScreenWidth / 5.0f) * 0.85;
	float height = 5.0f;

	Rectangle sliderRect = { x, y, width, height };
	DrawRectangleRec(sliderRect, C[3]);

    static float handlePos = x + ((40 - minValue) / (float)(maxValue - minValue)) * width;
    DrawCircle((int)handlePos, (int)y + height / 2, height * 1.5f, C[2]);

	static bool is_dragging = false;
	Vector2 mouse = GetMousePosition();

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointCircle(mouse, { handlePos, y + height / 2 }, height * 1.5f)) { is_dragging = true; }
	if (IsMouseButtonUp(MOUSE_LEFT_BUTTON)) { is_dragging = false; }

	if (is_dragging) {
		handlePos = Clamp(mouse.x, x, x + width);
	}

    int value = minValue + (1.0f - ((handlePos - x) / (float)width)) * (maxValue - minValue);
    return value;
}