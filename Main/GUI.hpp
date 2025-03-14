
#ifndef GUI_HPP
#define GUI_HPP

enum TypeDataStructure{MENU, HASHTABLE, LINKEDLIST, AVLTREE, GRAPH};



struct GUI {

	void Start();
	void DrawMainMenu();
	void DrawHashTable();
	void DrawLinkedList();
	void DrawAVLTree();
	void DrawGraph();
	void DrawBack();

};

extern GUI Gui;


#endif // !GUI_HPP
