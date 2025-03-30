#ifndef AVLTree_HPP
#define AVLTree_HPP

#include "Node.hpp"
#include "Config.hpp"
#include <random>
#include <queue>

class AVLTree {
public :

	AVLTree();
	Node* Root;
	vector <Node*> NodeList;

	float DistanceHorizontal;
	float DistanceVertical;

public :
	void MoveTree(Node* root, bool isLeft);
	void balanceTree();
public :
	void DrawTreeHelper(Node* root);
	void DrawTree();
	
	void DrawLevelOrder(Node* root);
	void DeleteLeafNode(Node*& root, int key);
	bool RebalanceChild(Node*& root);
	bool RebalanceParent(Node*& root);
	int GetBalanceFactor(Node* node);


public:
	void Insert(Node*& root, int data, vector <Node*> &NodeList, bool isNeedRotate);
	Node* InsertHelper(Node*& root, int data, Node* parnent, vector <Node*> &NodeList, bool isNeedRotate);
	int GetHeight(Node* node);
	Node* RotationLeft(Node*& root);
	Node* RotationRight(Node*& root);

	void UpdateHeightAndBalanceFactor(Node*& root);
	Node* GetNodeRotate();

	void Random();
	void Clear(Node* &root);

	

};

#endif // !AVLTree_HPP

