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

void GUI::Start() {
    InitWindow(ScreenWidth, ScreenHeight, "Data Structure Visualization");

    for (int i = 0; i < 6; i++) { C[i] = ColorPalette[3][i]; }
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
	DrawText("Choose Data Structure", ScreenWidth * float(2) / 5, ScreenHeight * float(5) / 6, 40, C[0]);

	Rectangle HASHTABLEBUTTON = { ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	Rectangle LINKEDLISTBUTTON = { ScreenWidth * float(3) / 5, ScreenHeight * float(1) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	Rectangle AVLTREEBUTTON = { ScreenWidth * float(1) / 5, ScreenHeight * float(3) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	Rectangle GRAPHBUTTON = { ScreenWidth * float(3) / 5, ScreenHeight * float(3) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	DrawRectangleRounded(HASHTABLEBUTTON, 0.3f, 10, C[2]);
	DrawRectangleRounded(LINKEDLISTBUTTON, 0.3f, 10, C[2]);
	DrawRectangleRounded(AVLTREEBUTTON, 0.3f, 10, C[2]);
	DrawRectangleRounded(GRAPHBUTTON, 0.3f, 10, C[2]);

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

void GUI::DrawHashTable() {
	Gui.DrawSecondMenu();
	Gui.DrawBack();
}

void GUI::DrawLinkedList() {
    Gui.DrawListMenu();
    Gui.DrawBack();

    if (buttoninit.IsClick()) {
        Gui.isClickInit = true;
    }
    if (Gui.isClickInit) {
        DrawText("Nodes : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(0.7) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);
        int tmp = Input(SecondMenuWidth * float(1) / 3 + 140, SecondMenuHeight + SecondMenuHeight * float(0.7) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);

        if (tmp != -1) {
            list.clear();
            list.rand_list(tmp);
            list.print_list();
            Gui.isClickInit = false;
        }
    }

    if (buttoninsert.IsClick()) {
        Gui.isClickInsert = true;
    }
    if (Gui.isClickInsert) {
        DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);
        int val = Gui.Input(SecondMenuWidth * float(1) / 3 + 120, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);

        if (val != -1) {
            list.add_node(val);
            Gui.isClickInsert = false;
        }
    }

    if (buttondelete.IsClick()) {
        if (list.get_active() >= 0) {
            list.delete_node(list.get_active());
        }
        else {
            Gui.isClickDelete = true;
        }
    }
    if (Gui.isClickDelete) {
        DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(3) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, C[0]);
        int val = Gui.Input(SecondMenuWidth * float(1) / 3 + 120, SecondMenuHeight + SecondMenuHeight * float(3) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);

        if (val != -1) {
            list.delete_node(val);
            Gui.isClickDelete = false;
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
    // Xử lý nút menu
    if (buttoninit.IsClick()) Gui.SetActiveMenuAVLTree(INIT_AVLTREE);
    else if (buttoninsert.IsClick()) Gui.SetActiveMenuAVLTree(INSERT_AVLTREE);
    else if (buttonsearch.IsClick()) Gui.SetActiveMenuAVLTree(SEARCH_AVLTREE);
    else if (buttondelete.IsClick()) Gui.SetActiveMenuAVLTree(DELETE_AVLTREE);


    if (activemenu_avltree == INIT_AVLTREE) {
        buttonrandom.DrawButton();
        buttonloadfile.DrawButton();

        if (buttonrandom.IsClick()) {
            tree.Random();

            Gui.isClickRandom = true;
            Gui.isClickLoadFile = false;
        }

        if (buttonloadfile.IsClick()) {
            // Clear the existing tree before loading from file

            Gui.LoadFileAVLTree();
            Gui.insertanimationavltree.SetTree(&tree);
            Gui.isClickLoadFile = true;
            Gui.isClickRandom = false;
        }


    }


    else if (activemenu_avltree == INSERT_AVLTREE) {
        Gui.isClickRandom = false;

        Gui.isClickLoadFile = false;
        DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, BLACK);
        int value = Gui.Input(SecondMenuWidth * float(1) / 3 + 120, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);
        if (value != -1) {
            Gui.insertanimationavltree.StartInsertAnimation(value);
            Gui.isClickInsert = true;

        }
    }
    if (Gui.isClickInsert == true) {
        Gui.insertanimationavltree.UpdateStep();

        if (Gui.insertanimationavltree.isFinished() == true) {
            Gui.isClickInsert = false;
            Gui.activemenu_avltree = NONE;
        }
    }
    tree.DrawTree();


    Gui.DrawBack();
}

void GUI::DrawGraph() {
	Gui.DrawGraphMenu();
	Gui.DrawBack();

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

//------------

void GUI::DrawSecondMenu() {
    DrawRectangle(0, ScreenHeight / 2, ScreenWidth / 5, ScreenHeight / 2, C[1]);
    buttoninit.DrawButton();
    buttoninsert.DrawButton();
    buttondelete.DrawButton();
    buttonsearch.DrawButton();
}

void GUI::DrawListMenu() {
    DrawRectangle(0, ScreenHeight / 2, ScreenWidth / 5, ScreenHeight / 2, C[1]);
    buttoninit.DrawButton();
    buttoninsert.DrawButton();
    buttondelete.DrawButton();
    buttonsearch.DrawButton();
    buttonclear.DrawButton();
}

void GUI::DrawGraphMenu() {
	DrawRectangle(0, ScreenHeight / 2, ScreenWidth / 5, ScreenHeight / 2, C[1]);

	buttoninit.DrawButton();
	buttoninsert.DrawButton();
	buttondelete.DrawButton();
	buttondijkstra.DrawButton();
	buttonclear.DrawButton();
}

void GUI::DrawBack() {
	if (CurrentStruture == HASHTABLE) { DrawText("Hash Table", ScreenWidth * float(2) / 5, 100, 40, C[0]); }
	else if (CurrentStruture == LINKEDLIST) { DrawText("Linked List", ScreenWidth * float(2) / 5, 100, 40, C[0]); }
	else if (CurrentStruture == AVLTREE) { DrawText("AVL Tree", ScreenWidth * float(2) / 5, 100, 40, C[0]); }
	else if (CurrentStruture == GRAPH) { DrawText("Graph", ScreenWidth * float(2) / 5, 100, 40, C[0]); }

    Rectangle BackButton = { 50, 50, 150, 50 };
    DrawRectangleRec(BackButton, RED);
    DrawText("Back", 100, 65, 30, C[0]);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        if (CheckCollisionPointRec(mouse, BackButton)) {
            if (CurrentStruture == LINKEDLIST) {
                list.clear();
            }
			if (CurrentStruture == AVLTREE) {
				tree.Clear(tree.Root);
				tree.NodeList.clear();
			}
			if (CurrentStruture == GRAPH) {
				graph.clear();
			}

            CurrentStruture = MENU;
            isClickInit = false;
            isClickInsert = false;
            isClickDelete = false;
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