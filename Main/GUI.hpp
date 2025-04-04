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

#include <fstream>


enum TypeDataStructure { MENU, HASHTABLE, LINKEDLIST, AVLTREE, GRAPH };
enum ActiveMenuTypeAVLTree {NONE, INIT_AVLTREE, INSERT_AVLTREE, SEARCH_AVLTREE, DELETE_AVLTREE};
enum ActiveMenuInitAVLTree{NONEINITAVLTREE, RANDOM_AVLTREE, LOADFILE_AVLTREE};

class GUI {
private:

	LinkedList list;

	AVLTree tree;
	ActiveMenuTypeAVLTree activemenu_avltree = NONE;
	ActiveMenuInitAVLTree activemenuinit_avltree = NONEINITAVLTREE;
	InsertAnimationAVLTree insertanimationavltree;

	Graph graph;
	DijkstraAnimationGraph dijkstra_animation;
	
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
	string inputstring = "";


public:
	GUI();

	void Start();
	
	void DrawHashTable();
	void DrawLinkedList();
	void DrawAVLTree();
	void DrawGraph();
	void DrawBack();

	void DrawMainMenu();
	void DrawSecondMenu();
	void DrawListMenu();
	void DrawGraphMenu();

	bool LoadFileAVLTree();
	bool LoadFileGraph();

	void InitGraph();
	void InsertGraph();
	void DeleteGraph();
	void DijkstraGraph();
	/*void StepByStep();
	void MakeImage();*/
	//void DrawListMenu();

	int Input(int posX, int posY);   
};

extern GUI Gui;

#endif // GUI_HPP