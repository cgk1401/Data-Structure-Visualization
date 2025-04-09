#ifndef GUI_HPP
#define GUI_HPP

#include "Config.hpp"
#include "Button.hpp"
#include <raylib.h>
//#include "AVLTree.hpp"
//#include "tinyfiledialogs.h"
//#include "InsertAnimationAVLTree.hpp"
#include "HashTable.hpp"


enum TypeDataStructure { MENU, HASHTABLE, LINKEDLIST, AVLTREE, GRAPH };


class GUI {
private:
	HashTable table;

public:
	string inputstring = "";

public :
	bool isClickRandom = false;
	bool isClickLoadFile = false;
	bool isClickInsert = false;
	bool isClickDelete = false;
	bool isClickInit = false;
	bool isClickSearch = false;
	bool isClickClear = false;
	bool isClickCreate = false;

public:
	GUI();

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
