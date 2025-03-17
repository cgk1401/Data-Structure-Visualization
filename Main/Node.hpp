#ifndef NODE_HPP
#define NODE_HPP

#include "raylib.h"
#include <iostream>
#include <vector>
using namespace std;


class Node {
public :
    int val;           
    int depth;         
    int height;        
    int balanceFactor; 
    int nodeIndex;     
    bool isLeft;       
    Vector2 position;  
    Node* left;        
    Node* right;       
    Node* parent;      

    Node(int val, int depth, int height, int balanceFactor, int nodeIdex, bool isLeft, Vector2 position, Node* left, Node* right, Node* parent);

};

#endif // !NODE_HPP

