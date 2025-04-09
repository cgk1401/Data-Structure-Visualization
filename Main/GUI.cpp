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

    for (int i = 0; i < 6; i++) { C[i] = ColorPalette[2][i]; }
    buttoninit.setColor(C[2]);
    buttoninsert.setColor(C[2]);
    buttondelete.setColor(C[2]);
    buttonsearch.setColor(C[2]);
    buttonclear.setColor(C[2]);
    buttonrandom.setColor(C[2]);
    buttonloadfile.setColor(C[2]);
	buttonvertex.setColor(C[2]);
	buttonedge.setColor(C[2]);
	buttondijkstra.setColor(C[2]);

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

    //Font custom = LoadFont("../../Data-Structure-Visualization/assets/PublicSans-Bold.ttf");
    //DrawTextEx(customfont, "Choose Data Structure", { ScreenWidth * float(2) / 5, ScreenHeight * float(5) / 6 }, 60, 1, C[0]);
    DrawText("Choose Data Structure", ScreenWidth * float(2) / 5, ScreenHeight * float(5) / 6, 40, C[0]);

   	Rectangle HASHTABLEBUTTON = { ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	Rectangle LINKEDLISTBUTTON = { ScreenWidth * float(3) / 5, ScreenHeight * float(1) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	Rectangle AVLTREEBUTTON = { ScreenWidth * float(1) / 5, ScreenHeight * float(3) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	Rectangle GRAPHBUTTON = { ScreenWidth * float(3) / 5, ScreenHeight * float(3) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	DrawRectangleRounded(HASHTABLEBUTTON, 0.3f, 10, C[2]);
	DrawRectangleRounded(LINKEDLISTBUTTON, 0.3f, 10, C[2]);
	DrawRectangleRounded(AVLTREEBUTTON, 0.3f, 10, C[2]);
	DrawRectangleRounded(GRAPHBUTTON, 0.3f, 10, C[2]);

    /*
    DrawTextEx(customfont, "HashTable", { ScreenWidth * float(1) / 5 + 20, ScreenHeight * float(1) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2 }, 30, 1, C[0]);
    DrawTextEx(customfont, "AVL", { ScreenWidth * float(1) / 5 + 20, ScreenHeight * float(3) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2 }, 30, 1, C[0]);
    DrawTextEx(customfont, "LINKEDLIST", { ScreenWidth * float(3) / 5 + 20, ScreenHeight * float(1) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2 }, 30, 1, C[0]);
    DrawTextEx(customfont, "GRAPH", { ScreenWidth * float(3) / 5 + 20, ScreenHeight * float(3) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2 }, 30, 1, C[0]);
    */
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

void GUI::DrawGraphMenu() {
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

void GUI::DrawLinkedList(){
    Gui.DrawSecondMenu();
    Gui.DrawBack();

    // Draw the reusable input box at a fixed position
    Gui.DrawInputBox(SecondMenuWidth* float(1) / 3 + 40, SecondMenuHeight + 100);

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

    Gui.DrawInputBox(SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + 100);

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

    Gui.DrawInputBox(SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + 100);

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
        if (graph.get_active1() >= 0) { graph.delete_node(graph.get_active1()); }
        else if (graph.get_active2().first >= 0 && graph.get_active2().second >= 0) { graph.delete_edge(graph.get_active2().first, graph.get_active2().second); }
        else {
            currentInputMode = DELETE;
            inputActive = true;
            inputstring = "";
        }
    }
    if (buttondijkstra.IsClick()) {
        currentInputMode = DIJKSTRA;
        inputActive = true;
        inputstring = "";
    }
    if (buttonclear.IsClick()) {
        graph.clear();
    }

    int val = Gui.Input(buttonclear.coordinateX, buttonclear.coordinateY + buttonclear.height + 20);

    /*
	if (buttoninit.IsClick() == true) {
		Gui.isClickInit = true;
	}
	if (Gui.isClickInit == true) {
		Gui.InitGraph();
	}

	if (buttoninsert.IsClick() == true) {
		Gui.isClickInsert = true;
	}
	if (Gui.isClickInsert == true) {
		Gui.InsertGraph();
	}

	if (buttondelete.IsClick() == true) {
		if (graph.get_active1() >= 0) { graph.delete_node(graph.get_active1()); }
		else
			if (graph.get_active2().first >= 0 && graph.get_active2().second >= 0) { graph.delete_edge(graph.get_active2().first, graph.get_active2().second); }
			else { Gui.isClickDelete = true; }
	}
	if (Gui.isClickDelete == true) {
		Gui.DeleteGraph();
	}

	if (buttondijkstra.IsClick() == true) {
		Gui.isClickDijkstra = true;
	}
	if (Gui.isClickDijkstra == true) {
		Gui.DijkstraGraph();
	}

	if (buttonclear.IsClick() == true) {
		graph.clear();
	}
    */

    if (val != -1) {
        switch (currentInputMode) {
        case INIT: {
            break;
        }
        case INSERT: {
            break;
        }
        case DELETE: {
            break;
        }
        case SEARCH: {
            break;
        }
        default: {
            break;
        }
        }
        inputActive = false;
        currentInputMode = NONE;
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

void GUI::InitGraph() {
	if (Gui.isClickRandom == false && Gui.isClickLoadFile == false) {
		buttonrandom.DrawButton();
		buttonloadfile.DrawButton();

		if (buttonrandom.IsClick() == true) { Gui.isClickRandom = true; }
		if (buttonloadfile.IsClick() == true) { Gui.isClickLoadFile = true; }
	}

	if (Gui.isClickRandom == true) {
		static int n_vertex = -1;
		static int n_edge = -1;
		static bool for_vertex = true;
        static bool for_edge = false;

        DrawText("Vertex : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(0.7) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);
        DrawText("Edge : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(1.1) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);

        if (for_vertex == true) {
            int tmp = Input(SecondMenuWidth * float(1) / 3 + 140, SecondMenuHeight + SecondMenuHeight * float(0.7) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);

            if (tmp != -1) {
                n_vertex = tmp;
                for_vertex = false;
                for_edge = true;
            }
        }

		if (for_edge == true) {
			DrawText(std::to_string(n_vertex).c_str(), SecondMenuWidth * float(1) / 3 + 140, SecondMenuHeight + SecondMenuHeight * float(0.7) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);

			int tmp = Input(SecondMenuWidth * float(1) / 3 + 140, SecondMenuHeight + SecondMenuHeight * float(1.1) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);

			if (tmp != -1) {
				n_edge = tmp;
				for_vertex = true;
				for_edge = false;

				graph.clear();
				graph.rand_graph(n_vertex, n_edge);
				//graph.print_nodes();

				Gui.isClickRandom = false;
				Gui.isClickInit = false;
			}
		}

		if (Gui.isClickLoadFile == true) {
			Gui.isClickLoadFile = false;
			Gui.isClickInit = false;
		}
	}

	if (Gui.isClickLoadFile == true) {
		LoadFileGraph();
		Gui.isClickLoadFile = false;
		Gui.isClickInit = false;
	}
}

void GUI::InsertGraph() {
	static bool isClickVertex = false;
	static bool isClickEdge = false;

	if (isClickVertex == false && isClickEdge == false) {
		buttonvertex.DrawButton();
		buttonedge.DrawButton();

		if (buttonvertex.IsClick() == true) { isClickVertex = true; }
		if (buttonedge.IsClick() == true) { isClickEdge = true; }
	}	

	if (isClickVertex == true) {
		DrawText("Vertex : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);
		int val = Gui.Input(SecondMenuWidth * float(1) / 3 + 130, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);

		if (val != -1) {
			graph.add_node(val);
			isClickVertex = false;
			Gui.isClickInsert = false;
		}
	}

	if (isClickEdge == true) {
		static int id1 = -1;
		static int id2 = -1;
		static int w = -1;
		static bool for_id1 = true;
		static bool for_id2 = false;
		static bool for_w = false;

		DrawText("From : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(1.75) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);
		DrawText("To : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);
		DrawText("Weight : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(2.25) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);
		
		if (for_id1 == true) {
			int val = Gui.Input(SecondMenuWidth * float(1) / 3 + 120, SecondMenuHeight + SecondMenuHeight * float(1.75) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);
		
			if (val != -1) {
				id1 = val;
				for_id1 = false;
				for_id2 = true;
			}
		}
		if (for_id2 == true) {
			DrawText(std::to_string(id1).c_str(), SecondMenuWidth * float(1) / 3 + 140, SecondMenuHeight + SecondMenuHeight * float(1.75) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);

			int val = Gui.Input(SecondMenuWidth * float(1) / 3 + 120, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);
			
			if (val != -1) {
				id2 = val;
				for_id2 = false;
				for_w = true;
			}
		}
		if (for_w == true) {
			DrawText(std::to_string(id1).c_str(), SecondMenuWidth * float(1) / 3 + 140, SecondMenuHeight + SecondMenuHeight * float(1.75) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);
			DrawText(std::to_string(id2).c_str(), SecondMenuWidth * float(1) / 3 + 140, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);

			int val = Gui.Input(SecondMenuWidth * float(1) / 3 + 120, SecondMenuHeight + SecondMenuHeight * float(2.25) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);
			
			if (val != -1) {
				w = val;
				for_w = false;
				for_id1 = true;

				graph.add_edge(id1, id2, w);
				isClickEdge = false;
				Gui.isClickInsert = false;
			}
		}
	}
}

void GUI::DeleteGraph() {
	static bool isClickVertex = false;
	static bool isClickEdge = false;

	if (isClickVertex == false && isClickEdge == false) {
		buttonvertex.DrawButton();
		buttonedge.DrawButton();

		if (buttonvertex.IsClick() == true) { isClickVertex = true; }
		if (buttonedge.IsClick() == true) { isClickEdge = true; }
	}

	if (isClickVertex == true) {
		DrawText("Vertex : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(3) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);
		int val = Gui.Input(SecondMenuWidth * float(1) / 3 + 130, SecondMenuHeight + SecondMenuHeight * float(3) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);

		if (val != -1) {
			graph.delete_node(val);
			isClickVertex = false;
			Gui.isClickDelete = false;
		}
	}

	if (isClickEdge == true) {
		static int id1 = -1;
		static int id2 = -1;
		static bool for_id1 = true;
		static bool for_id2 = false;

		DrawText("From : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(2.85) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);
		DrawText("To : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(3.15) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);
		
		if (for_id1 == true) {
			int val = Gui.Input(SecondMenuWidth * float(1) / 3 + 120, SecondMenuHeight + SecondMenuHeight * float(2.85) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);

			if (val != -1) {
				id1 = val;
				for_id1 = false;
				for_id2 = true;
			}
		}
		if (for_id2 == true) {
			DrawText(std::to_string(id1).c_str(), SecondMenuWidth * float(1) / 3 + 140, SecondMenuHeight + SecondMenuHeight * float(2.85) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);

			int val = Gui.Input(SecondMenuWidth * float(1) / 3 + 120, SecondMenuHeight + SecondMenuHeight * float(3.2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);

			if (val != -1) {
				id2 = val;
				for_id2 = false;
				for_id1 = true;

				graph.delete_edge(id1, id2);
				isClickEdge = false;
				Gui.isClickDelete = false;
			}
		}
	}
}

void GUI::DijkstraGraph() {
	static bool firstRun = true;

	if (firstRun == true) {
		DrawText("Vertex : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(4) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);
		int val = Gui.Input(SecondMenuWidth * float(1) / 3 + 130, SecondMenuHeight + SecondMenuHeight * float(4) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);
		
		if (val != -1) {
			dijkstra_animation.load_state(val);
			firstRun = false;
			graph.set_running_dijkstra(true);
		}
	}

	if (firstRun != false) { return; }

	dijkstra_animation.render();

	static bool for_click = false;

	if (dijkstra_animation.is_finnished()) { for_click = true; }

	if (for_click && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		Gui.isClickDijkstra = false;
		graph.set_running_dijkstra(false);
		for_click = false; firstRun = true;
	}
	else if (!dijkstra_animation.is_finnished()) {
		dijkstra_animation.next_state();
	}
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
        case INIT:    labelText = "Init Nodes: "; break;
        case INSERT:  labelText = "Insert Value: "; break;
        case DELETE:  labelText = "Delete Value: "; break;
        case SEARCH:  labelText = "Search Value: "; break;
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