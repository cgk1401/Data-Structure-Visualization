#ifndef GUI_HPP
#define GUI_HPP

#include "Config.hpp"
#include "Button.hpp"
#include "raylib.h"
#include "LinkedList.hpp"
#include "AVLTree.hpp"
#include "Graph.hpp"
#include "tinyfiledialogs.h"
#include "InsertAnimationAVLTree.hpp"
#include "DijkstraAnimationGraph.hpp"
#include"HashTable.hpp"
#include <fstream>
#include <string>


enum TypeDataStructure { MENU, THEME, HASHTABLE, LINKEDLIST, AVLTREE, GRAPH };

enum ActiveMenuTypeAVLTree { NONE_AVLTREE, INIT_AVLTREE, INSERT_AVLTREE, SEARCH_AVLTREE, DELETE_AVLTREE };
enum ActiveMenuInitAVLTree { NONEINITAVLTREE, RANDOM_AVLTREE, LOADFILE_AVLTREE };

enum ActiveMenuTypeGraph { DEFAULT, INSERT_V, INSERT_E, DELETE_V, DELETE_E, DIJKSTRA_ST, DIJKSTRA_RUN, DIJKSTRA_TG, DIJKSTRA_PTH };

enum InputMode { NONE, INIT, INSERT, DELETE, SEARCH, DIJKSTRA, DIJKSTRA_AT, DIJKSTRA_SS, RANDOM };

class GUI {
private:

	LinkedList list;
    float linkedListScrollY = 0;
    float linkedListContentHeight = 0;
    const float scrollSpeed = 20.0f;

	AVLTree tree;
	ActiveMenuTypeAVLTree activemenu_avltree = NONE_AVLTREE;
	ActiveMenuInitAVLTree activemenuinit_avltree = NONEINITAVLTREE;
	InsertAnimationAVLTree insertanimationavltree;

	Graph graph;
	ActiveMenuTypeGraph activemenu_graph = DEFAULT;
	int GraphRandomStep = 0;
	int GraphVertexStep = 0;
	DijkstraAnimationGraph dijkstra_animation;
	HashTable hashtable;
public :

	void SetActiveMenuAVLTree(ActiveMenuTypeAVLTree newMenu);
	void SetActiveMenuInitAVLTree(ActiveMenuInitAVLTree newMenu);

public :
	bool isClickInit = false;
	bool isClickRandom = false;
	bool isClickLoadFile = false;
	bool isClickInsert = false;
	bool isClickDelete = false;
	bool isClickDijkstra = false;


public:
	GUI();

	std::string inputstring = "";
	InputMode currentInputMode = NONE;
	bool inputActive = false;
	float search_result_timer = 0.0f;

	void Start();
	
	void DrawHashTable();
	void DrawLinkedList();
	void DrawAVLTree();
	void DrawGraph();
	void DrawBack();

	void DrawMainMenu();
	void DrawThemeMenu();
	void DrawSecondMenu();
	void DrawListMenu();

	void ResetMenuState();

	bool LoadFileAVLTree();
	bool LoadFileGraph();

	int Input(int posX, int posY);   
    void DrawInputBox();
};

extern GUI Gui;

#endif // GUI_HPP