<<<<<<< HEAD

=======
>>>>>>> LinkedList
#ifndef GUI_HPP
#define GUI_HPP

#include "Config.hpp"
#include "Button.hpp"
<<<<<<< HEAD
#include <raylib.h>
#include "AVLTree.hpp"
#include "tinyfiledialogs.h"
#include "InsertAnimationAVLTree.hpp"

#include <fstream>


enum TypeDataStructure { MENU, HASHTABLE, LINKEDLIST, AVLTREE, GRAPH };
enum ActiveMenuTypeAVLTree {NONE, INIT_AVLTREE, INSERT_AVLTREE, SEARCH_AVLTREE, DELETE_AVLTREE};


class GUI {
private:

	AVLTree tree;
	ActiveMenuTypeAVLTree activemenu_avltree = NONE;

	InsertAnimationAVLTree insertanimationavltree;

public:
	string inputstring = "";
	
public :

	void SetActiveMenuAVLTree(ActiveMenuTypeAVLTree newMenu);

public :
	bool isClickRandom = false;
	bool isClickLoadFile = false;
	bool isClickInsert = false;


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

=======
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
>>>>>>> LinkedList
};

extern GUI Gui;

<<<<<<< HEAD

#endif // GUI_HPP
=======
#endif
>>>>>>> LinkedList
