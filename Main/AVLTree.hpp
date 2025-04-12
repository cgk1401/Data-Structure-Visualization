#ifndef AVLTree_HPP
#define AVLTree_HPP

#include "Node.hpp"
#include "Config.hpp"
#include <random>
#include <queue>
#include <set>
#include <string>
class AVLTree {
public:
	AVLTree();
	~AVLTree();
	Node* Root;
	vector <Node*> NodeList;
	Node* DeleteNode(Node* root, int key);

	float DistanceHorizontal;
	float DistanceVertical;

public:
	void DrawTree();
	void DrawTreeHelper(Node* root);
	void MoveTree(Node* root, bool isLeft);
	void balanceTree();

	void DeleteLeafNode(Node*& root, int key);
	void RebalanceChild(Node*& root, Node* noderotate);
	void RebalanceParent(Node*& root, Node* noderotate);

	int GetBalanceFactor(Node* node);
	int GetHeight(Node* node);

	void Insert(Node*& root, int data, vector <Node*>& NodeList, bool isNeedRotate);
	Node* InsertHelper(Node*& root, int data, Node* parnent, vector <Node*>& NodeList, bool isNeedRotate);
	Node* RotationLeft(Node*& root);
	Node* RotationRight(Node*& root);
	Node* GetNodeRotate();
	void UpdateHeightAndBalanceFactor(Node*& root);

	void Random();
	void InitAVLTree(int val);
	void Clear(Node*& root);
};

#endif // !AVLTree_HPP

