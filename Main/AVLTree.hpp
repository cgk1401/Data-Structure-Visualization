#ifndef AVLTree_HPP
#define AVLTree_HPP

#include "Node.hpp"
#include "Config.hpp"
#include <queue>

class AVLTree {
public:
	Node* Root;
	vector <Node*> NodeList;
	float DistanceHorizontal;
	float DistanceVertical;

	AVLTree();
	//~AVLTree();

	void Insert(Node*& root, int data, vector <Node*> &NodeList);
	Node* InsertHelper(Node*& root, int data, Node* parnent, vector <Node*> &NodeList);
	void MoveTree(Node* root, bool isLeft);
	void balanceTree();
	void DrawTreeHelper(Node* node);
	void DrawTree();
	

};

#endif // !AVLTree_HPP

