#include <iostream>
#include <string>
#include "GUI.hpp"

using namespace std;

GUI Gui;

TypeDataStructure CurrentStruture = MENU;

GUI::GUI()
	: insertanimationavltree(&tree)
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

    Font customfont = LoadFont("../../PublicSans-Bold.ttf");
    DrawTextEx(customfont, "Choose Data Structure", { ScreenWidth * float(2) / 5, ScreenHeight * float(5) / 6 }, 60, 1, C[0]);

   	Rectangle HASHTABLEBUTTON = { ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	Rectangle LINKEDLISTBUTTON = { ScreenWidth * float(3) / 5, ScreenHeight * float(1) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	Rectangle AVLTREEBUTTON = { ScreenWidth * float(1) / 5, ScreenHeight * float(3) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	Rectangle GRAPHBUTTON = { ScreenWidth * float(3) / 5, ScreenHeight * float(3) / 5, ScreenWidth * float(1) / 5, ScreenHeight * float(1) / 6 };

	DrawRectangleRounded(HASHTABLEBUTTON, 0.3f, 10, C[2]);
	DrawRectangleRounded(LINKEDLISTBUTTON, 0.3f, 10, C[2]);
	DrawRectangleRounded(AVLTREEBUTTON, 0.3f, 10, C[2]);
	DrawRectangleRounded(GRAPHBUTTON, 0.3f, 10, C[2]);
    
    DrawTextEx(customfont, "HashTable", { ScreenWidth * float(1) / 5 + 20, ScreenHeight * float(1) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2 }, 30, 1, C[0]);
    DrawTextEx(customfont, "AVL", { ScreenWidth * float(1) / 5 + 20, ScreenHeight * float(3) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2 }, 30, 1, C[0]);
    DrawTextEx(customfont, "LINKEDLIST", { ScreenWidth * float(3) / 5 + 20, ScreenHeight * float(1) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2 }, 30, 1, C[0]);
    DrawTextEx(customfont, "GRAPH", { ScreenWidth * float(3) / 5 + 20, ScreenHeight * float(3) / 5 + ScreenHeight * float(1) / 5 * float(1) / 2 }, 30, 1, C[0]);

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
    if (buttoninit.IsClick()) Gui.SetActiveMenuAVLTree(INIT_AVLTREE);
    else if (buttoninsert.IsClick()) Gui.SetActiveMenuAVLTree(INSERT_AVLTREE);
    else if (buttonsearch.IsClick()) Gui.SetActiveMenuAVLTree(SEARCH_AVLTREE);
    else if (buttondelete.IsClick()) Gui.SetActiveMenuAVLTree(DELETE_AVLTREE);


    if (activemenu_avltree == INIT_AVLTREE) {
        buttoninit.DrawClickEffect();
        buttonrandom.DrawButton();
        buttonloadfile.DrawButton();

        if (buttonrandom.IsClick())  Gui.SetActiveMenuInitAVLTree(RANDOM_AVLTREE);
        else if (buttonloadfile.IsClick())  Gui.SetActiveMenuInitAVLTree(LOADFILE_AVLTREE);
        

        if (activemenuinit_avltree == RANDOM_AVLTREE) {
            buttonrandom.DrawClickEffect();
            tree.Random();
            SetActiveMenuInitAVLTree(NONEINITAVLTREE);
        }
        else if (activemenuinit_avltree == LOADFILE_AVLTREE) {
            buttonloadfile.DrawClickEffect();
            Gui.LoadFileAVLTree();
            Gui.insertanimationavltree.SetTree(&tree);
            SetActiveMenuInitAVLTree(NONEINITAVLTREE);
        }
    }
    else if (activemenu_avltree == INSERT_AVLTREE) {
        buttoninsert.DrawClickEffect();

        DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, BLACK);
        int value = Gui.Input(SecondMenuWidth * float(1) / 3 + 120, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);
        if (value != -1) {
            Gui.insertanimationavltree.StartInsertAnimation(value);

        }
        Gui.insertanimationavltree.UpdateStep();
        
        if (Gui.insertanimationavltree.isFinished() == true) {
            //Gui.isClickInsert = false;
            SetActiveMenuInitAVLTree(NONEINITAVLTREE);
        }

    }

    else if (activemenu_avltree == SEARCH_AVLTREE) {
    }

    else if (activemenu_avltree == DELETE_AVLTREE) {
        buttondelete.DrawClickEffect();
        DrawText("Value : ", SecondMenuWidth * float(1) / 3 + 40, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2, 20, BLACK);
        int value = Gui.Input(SecondMenuWidth * float(1) / 3 + 120, SecondMenuHeight + SecondMenuHeight * float(2) / 6 + (SecondMenuHeight * float(1) / 6) * float(1) / 2);
        tree.Root = tree.DeleteNode(tree.Root, value);
        tree.UpdateHeightAndBalanceFactor(tree.Root);
        tree.balanceTree();
    }

    tree.DrawTree();


    Gui.DrawBack();
}

void GUI::DrawGraph() {
	Gui.DrawSecondMenu();
	Gui.DrawBack();
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

void GUI::DrawBack() {

    Image image = LoadImage("../../Arrow_Back.png");
    ImageResize(&image, 70, 70);
    Texture2D texture = LoadTextureFromImage(image);

    Vector2 pos = { 50, 50 };
    DrawTexture(texture, pos.x, pos.y, WHITE);
    Rectangle arrowback = {
        pos.x,
        pos.y,
        (float)texture.width,
        (float)texture.height
    };

    UnloadImage(image);
    if (CheckCollisionPointRec(GetMousePosition(), arrowback)) {
        DrawTexture(texture, pos.x, pos.y, Color{ 200, 200, 255, 255 }); // hơi xanh nhẹ
    }
    else {
        DrawTexture(texture, pos.x, pos.y, WHITE);
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        if (CheckCollisionPointRec(mouse, arrowback)) {
            if (CurrentStruture == LINKEDLIST) {
                list.clear();
            }
			if (CurrentStruture == AVLTREE) {
				tree.Clear(tree.Root);
				tree.NodeList.clear();
			}

            CurrentStruture = MENU;


            SetActiveMenuAVLTree(NONE);
            SetActiveMenuInitAVLTree(NONEINITAVLTREE);
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

//void GUI::StepByStep() {
//
//}