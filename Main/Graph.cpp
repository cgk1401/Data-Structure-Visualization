#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstdlib>

#include "raylib.h"
#include "Graph.hpp"

void Graph::add_node(int id) {
	if (nodes.find(id) == nodes.end()) { 
		nodes.emplace(id, Node(id)); 
		nodes[id].pos.x = GetScreenWidth() / 4 + 175 * (id / 4);
		nodes[id].pos.y = GetScreenHeight() / 4 + 175 * (id % 4);
	}
}

void Graph::add_edge(int id1, int id2, int w) {
	if (nodes.find(id1) != nodes.end() && nodes.find(id2) != nodes.end()) {
		nodes[id1].adj.push_back({ id2, w });

		if (is_directed == false) {
			nodes[id2].adj.push_back({ id1, w });
		}
	}
}

void Graph::clear() {
	nodes.clear();
}

void Graph::rand_graph(int n_vertex, int n_edge) {
	/*
	int n_vertex; //nums of nodes
	int n_edge; //nums of edge
	bool is_dir; //directed/undirected graph
	
	std::cout << "Input number of vertex, edge, and directed/undirected (1/0):\n";
	std::cin >> n_vertex >> n_edge >> is_dir;
	is_directed = is_dir;
	*/

	if (is_directed == false && n_edge > ((n_vertex - 1) * n_vertex) / 2) { std::cout << "Too many edge for that number of vertex\n"; return; }
	if (is_directed == true && n_edge > (n_vertex - 1) * n_vertex) { std::cout << "Too many edge for that number of vertex\n"; return; }

	for (int i = 0; i < n_vertex; i++) { add_node(i); }

	srand(time(0));
	for (int i = 0; i < n_edge; i++) {
		int a = rand() % n_vertex;
		int b = rand() % n_vertex;

		if (a == b) { i--; continue; }
		//std::cout << a << " " << b << std::endl;
		bool neighbor_check = true; //check if have been neighbor
		for (const auto& x : nodes[a].adj) {
			if (x.first == b) { neighbor_check = false; break; }
		}
		if (neighbor_check == true) { add_edge(a, b, rand() % 10 + 1); }
		else { i--; }
	}
}

void Graph::input_graph(std::ifstream& fin) {
	int n_vertex; //nums of nodes
	int n_edge; //nums of edges
	bool is_dir; //directed/undirected graph
	fin >> n_vertex >> n_edge >> is_dir;
	is_directed = is_dir;

	for (int i = 0; i < n_vertex; i++) {
		int id; fin >> id;
		add_node(id);
	}

	for (int i = 0; i < n_edge; i++) {
		int a, b;
		int w;
		fin >> a >> b >> w;
		add_edge(a, b, w);
	}
}

void Graph::dijkstra(int id) {
	if (nodes.find(id) == nodes.end()) { std::cout << "Can not find node\n"; return; }

	int n = nodes.size(); // num of nodes
	std::vector <int> distance(n, INT_MAX);
	std::vector <bool> processed(n, false);
	distance[id] = 0;

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
	pq.push({ 0, id });

	while (pq.empty() == false) {
		int a = pq.top().second; pq.pop();
		if (processed[a] == true) { continue; }
		processed[a] = true;

		for (const auto& neighbor : nodes[a].adj) {
			int b = neighbor.first;
			int w = neighbor.second;
			if (distance[a] + w < distance[b]) {
				distance[b] = distance[a] + w;
				pq.push({ distance[b], b });
			}
		}
	}

	for (int i = 0; i < n; i++) {
		printf("%d to %d: %d\n", id, i, distance[i]);
	}
}

void Graph::print_nodes() {
	for (const auto& x : nodes) {
		std::cout << "Node: " << x.first << ":\n";
		for (const auto& neighbor : x.second.adj) {
			printf("To: %d; Weight: %d\n", neighbor.first, neighbor.second);
		}
	}
}

void Graph::draw_node(Node node) {
	float radius = 40.0;
	int width = MeasureText(std::to_string(node.id).c_str(), 20);
	int centerX = node.pos.x;
	int centerY = node.pos.y;

	DrawCircleV(node.pos, radius, WHITE);
	DrawCircleLinesV(node.pos, radius, BLACK);
	DrawText(std::to_string(node.id).c_str(), centerX - radius / 8, centerY - radius / 5, 20, BLACK);
	//std::cout << "Drawing node id: " << node.id << std::endl;
}

void Graph::draw() {
	for (auto& node : nodes) {
		for (auto& neighbor : node.second.adj) {
			int from = node.first;
			int to = neighbor.first;
			if (from > to) { continue; }
			DrawLineBezier(nodes[from].pos, nodes[to].pos, 2.0f, BLACK);
		}

		draw_node(node.second);
	}
}