#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

#include "raylib.h"
#include "raymath.h"

class Graph {
private:
	struct Node {
		int id;
		std::vector<std::pair<int, int>> adj; //first: id, second: weight

		//int coordinateX, coordinateY;
		Vector2 pos{ -100.0f, -100.0f };
		Vector2 velocity = { 0,0 };
		Vector2 force = { 0,0 };
		
		Node() : id(-1), pos({ -100.0f, -100.0f }) {};
		Node(int id, float x = 0, float y = 0, bool is_high = false) : id(id), pos({ x,y }) {};
	};
	float node_rad = 30.0f;
	int active_node1 = -1;
	std::pair<int, int> active_edge = { -1,-1 };

	std::unordered_map <int, Node> nodes;
	bool is_directed; //directed/undirected graph

	bool is_running_dijkstra = false;
	std::unordered_map<int, bool> processed;
	std::unordered_map<int, int> previous;
	std::unordered_map<int, std::string> node_txt;
	std::vector<int> highlight_line;

	void draw_node(Node node);
	void draw_edge(int from, int to, int weight);

	float k_repulsion = 100000000.0f;
	float k_spring = 8.0f;
	float spring_length = 350.0f;
	float damping = 0.75f;
	bool is_graph_fixed = false;

	void update_attractive_force();
	void update_repulsive_force();
	void update_centering_force();
	void update_pos();

	std::vector<std::string> DijkstraSteps = {
		"while (!pq.empty()) :",
		"	int a = pq.top().second; pq.pop();",
		"	if (vis[a] == true) { continue; }",
		"	vis[a] = true;",
		"",
		"	for (auto neighbor : nodes[a].adj) {",
		"		int b = neighbor.first;",
		"		int w = neighbor.second;",
		"",
		"		if (vis[b] == true) { continue; }",
		"",
		"		if (dist[b] > dist[a] + w) {",
		"			dist[b] = dist[a] + w;",
		"			prev[b] = a;",
		"			pq.push({ dist[b], b });",
		"		}",
		"	}",
		"}"
	};
	bool is_showing_code = false;

public:
	struct GraphStage {
		std::unordered_map<int, bool> processed;
		std::unordered_map<int, int> previous;
		std::unordered_map<int, std::string> node_txt;

		int current_node = -1;
		std::pair<int, int> active_edge = { -1,-1 };

		std::vector<int> highlight_line = {};
	};

public:
	Graph(bool dir) : is_directed(dir) {}

	bool add_node(int id);
	bool add_edge(int id1, int id2, int w);
	bool delete_node(int id);
	bool delete_edge(int id1, int id2);

	void update();
	void clear();
	int get_active1();
	std::pair<int, int> get_active2();

	void set_fix_graph(bool is_fixed);

	bool rand_graph(int n_vertex, int n_edge);
	void input_graph(std::ifstream& fin);

	void dijkstra(int start);
	std::vector<GraphStage> dijkstra_steps(int start);
	std::vector<GraphStage> dijkstra_paths(int end, std::unordered_map<int, int> previous);
	void set_running_dijkstra(bool is_running);
	void set_showing_code(bool is_showing);
	void set_state(GraphStage state);

	void print_nodes();

	void draw();
};

#endif  // GRAPH_HPP