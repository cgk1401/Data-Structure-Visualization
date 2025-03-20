
#ifndef GUI_HPP
#define GUI_HPP

#include "Config.hpp"
#include "Button.hpp"
#include <raylib.h>
#include "AVLTree.hpp"


enum TypeDataStructure { MENU, HASHTABLE, LINKEDLIST, AVLTREE, GRAPH };



class GUI {
private : 
	AVLTree tree;
	
public :
	string inputstring = "";
	bool ClickInsert = false;
	bool ClickInsertEnter = false;
	bool ClickInit = false;


public:

	void Start();
	void DrawMainMenu();
	void DrawSecondMenu();
	void DrawHashTable();
	void DrawLinkedList();
	void DrawAVLTree();
	void DrawGraph();
	void DrawBack();
	

	int Input(int posX, int posY);

};

extern GUI Gui;


#endif // GUI_HPP
