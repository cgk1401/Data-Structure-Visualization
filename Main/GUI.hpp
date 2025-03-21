
#ifndef GUI_HPP
#define GUI_HPP

#include "Config.hpp"
#include "Button.hpp"
#include <raylib.h>
#include "AVLTree.hpp"
#include "tinyfiledialogs.h"

#include <fstream>


enum TypeDataStructure { MENU, HASHTABLE, LINKEDLIST, AVLTREE, GRAPH };
enum ActiveMenuTypeAVLTree {NONE, INIT_AVLTREE, INSERT_AVLTREE, SEARCH_AVLTREE, DELETE_AVLTREE};


class GUI {
private:

	AVLTree tree;
	ActiveMenuTypeAVLTree activemenu_avltree = NONE;

public:
	string inputstring = "";
	
public :

	void SetActiveMenuAVLTree(ActiveMenuTypeAVLTree newMenu);

public :
	bool isClickRandom = false;
	bool isClickLoadFile = false;
	bool isClickInsert = false;


public:

	void Start();
	void DrawMainMenu();
	void DrawSecondMenu();
	void DrawHashTable();
	void DrawLinkedList();
	void DrawAVLTree();
	void DrawGraph();
	void DrawBack();

	bool LoadFileAVLTree();

	int Input(int posX, int posY);

};

extern GUI Gui;


#endif // GUI_HPP
