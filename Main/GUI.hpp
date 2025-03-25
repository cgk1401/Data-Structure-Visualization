#ifndef GUI_HPP
#define GUI_HPP

#include "Config.hpp"
#include "Button.hpp"
#include "LinkedList.hpp"
#include <raylib.h>

enum TypeDataStructure { MENU, HASHTABLE, LINKEDLIST, AVLTREE, GRAPH };

class GUI {
private:
    LinkedList list;

public:
    GUI() {}

    string inputstring = "";
    bool ClickInit = false;
    bool ClickInsert = false;
    bool ClickDelete = false;

    void Start();
    void DrawMainMenu();
    void DrawSecondMenu();
    void DrawHashTable();
    void DrawLinkedList();
    void DrawAVLTree();
    void DrawGraph();
    void DrawBack();

    int Input(int posX, int posY);

    void DrawListMenu();
};

extern GUI Gui;

#endif