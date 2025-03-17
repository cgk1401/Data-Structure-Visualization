
#ifndef GUI_HPP
#define GUI_HPP

#include "Config.hpp"
#include "Button.hpp"
#include <raylib.h>
#include "AVLTree.hpp"


enum TypeDataStructure { MENU, HASHTABLE, LINKEDLIST, AVLTREE, GRAPH };



class GUI {
public:
	string inputstring = "";
	bool ClickInsert = false;
	bool ClickInsertEnter = false;
	AVLTree tree;
	

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


#endif // GUI_HPP
