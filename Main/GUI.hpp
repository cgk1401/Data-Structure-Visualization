#ifndef GUI_HPP
#define GUI_HPP

#include "Config.hpp"
#include "Button.hpp"
#include "LinkedList.hpp"
#include <raylib.h>
#include <string>

enum TypeDataStructure { MENU, HASHTABLE, LINKEDLIST, AVLTREE, GRAPH };
enum InputMode { NONE, INIT, INSERT, DELETE, SEARCH };

class GUI {
private:
    LinkedList list;

public:
    GUI() {}

    std::string inputstring = "";
    InputMode currentInputMode = NONE;  // Tracks which operation the input box is for
    bool inputActive = false;           // Whether the input box is currently active
    float search_result_timer = 0.0f;

    void Start();
    void DrawMainMenu();
    void DrawSecondMenu();
    void DrawHashTable();
    void DrawLinkedList();
    void DrawAVLTree();
    void DrawGraph();
    void DrawBack();

    int Input(int posX, int posY);  //}
    void DrawInputBox(int posX, int posY);  // New method to draw the reusable input box

    void DrawListMenu();
};

extern GUI Gui;

#endif