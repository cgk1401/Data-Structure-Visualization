#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

class Graph {
private:
	struct Node {
		int id;
		std::vector<std::pair<int, int>> adj; //first: id, second: weight

		//int coordinateX, coordinateY;
		Vector2 pos{ -100.0f, -100.0f };
		//if the node should be highlighted or not
		bool is_highlighted = false;
		
		Node() : id(-1), pos({ -100.0f, -100.0f }), is_highlighted(false) {};
		Node(int id, float x = 0, float y = 0, bool is_high = false) : id(id), pos({ x,y }), is_highlighted(is_high) {};
	};
	float node_rad = 35.0f;
	int active_node1 = -1;

	std::unordered_map <int, Node> nodes;
	bool is_directed; //directed/undirected graph

	void draw_node(Node node);
	void draw_edge(int from, int to, int weight);

public:
	Graph(bool dir) : is_directed(dir) {}

	void add_node(int id);
	void add_edge(int id1, int id2, int w);
	void delete_node(int id);

	void update();
	void clear();
	int get_active1();

	void rand_graph(int n_vertex, int n_edge);
	void input_graph(std::ifstream& fin);

	void dijkstra(int id);

	void print_nodes();

	void draw();
};

#endif  

