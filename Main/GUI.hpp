
#ifndef GUI_HPP
#define GUI_HPP

#include "Config.hpp"
#include "Button.hpp"
#include <raylib.h>
#include "AVLTree.hpp"
#include "tinyfiledialogs.h"

#include <fstream>


enum TypeDataStructure { MENU, HASHTABLE, LINKEDLIST, AVLTREE, GRAPH };



class GUI {
private:
	AVLTree tree;

public:
	string inputstring = "";
	
public : 
	bool ClickInsert_AVLTree = false;
	bool ClickInsertEnter_AVLTree = false;

public :
	bool ClickInitEnter_AVLTree = false;
	bool ClickInit_AVLTree = false;

public : 
	bool ClickDelete_AVLTree = false;
	bool ClickDeleteEnter_AVLTree = false;

public :
	bool ClickSearch_AVLTree = false;
	bool ClickSearchEnter_AVLTree = false;

public :
	bool ClickRandom_AVLTree = false;
	bool ClickLoadFile_AVLTree = false;

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
