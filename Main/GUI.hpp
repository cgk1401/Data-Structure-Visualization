
#ifndef GUI_HPP
#define GUI_HPP

#include "Config.hpp"
#include "Button.hpp"
#include "Graph.hpp"
#include <raylib.h>


enum TypeDataStructure { MENU, HASHTABLE, LINKEDLIST, AVLTREE, GRAPH };

struct GraphInitState {
	bool waitingForVertex = true;
	bool waitingForEdge = false;
	int n_vertex = -1;
	int n_edge = -1;
};

class GUI {
private:
	Graph graph;
	GraphInitState gr_init_state;

public:
	GUI(): graph(false) {}

	string inputstring = "";
	bool ClickInit = false;
	bool ClickInsert = false;

	void Start();
	void DrawMainMenu();
	void DrawSecondMenu();
	void DrawHashTable();
	void DrawLinkedList();
	void DrawAVLTree();
	void DrawGraph();
	void DrawBack();

	int InputInsert();
	int Input(int posX, int posY);

	void DrawGraphMenu();

};

extern GUI Gui;


#endif // GUI_HPP
