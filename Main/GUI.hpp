
﻿#ifndef GUI_HPP
#define GUI_HPP

#include "Config.hpp"
#include "Button.hpp"
#include <raylib.h>
<<<<<<< HEAD
=======


enum TypeDataStructure { MENU, HASHTABLE, LINKEDLIST, AVLTREE, GRAPH };
>>>>>>> d3ef482 (Fix gitignore and update demo menu)

enum TypeDataStructure { MENU, HASHTABLE, LINKEDLIST, AVLTREE, GRAPH };

<<<<<<< HEAD
class GUI {
public:
    string inputstring = "";
    bool ClickInsert;
    bool ClickInit;
    bool ClickDelete;
    bool ClickSearch;
    void Start();
    void DrawMainMenu();
    void DrawSecondMenu();
    void DrawHashTable();
    void DrawLinkedList();
    void DrawAVLTree();
    void DrawGraph();
    void DrawBack();
    void InputInsert();
    void InputInit();
    void InputSearch();
    void InputDelete();
};

extern GUI Gui;
=======

class GUI {
public:
	string inputstring = "";
	bool ClickInsert;

	void Start();
	void DrawMainMenu();
	void DrawSecondMenu();
	void DrawHashTable();
	void DrawLinkedList();
	void DrawAVLTree();
	void DrawGraph();
	void DrawBack();
	void InputInsert();

};

extern GUI Gui;


>>>>>>> d3ef482 (Fix gitignore and update demo menu)
#endif // GUI_HPP
