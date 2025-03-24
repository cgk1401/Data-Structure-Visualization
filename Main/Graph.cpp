#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstdlib>

#include "raylib.h"
#include "Graph.hpp"
#include "Config.hpp"

void Graph::add_node(int id) {
	if (nodes.find(id) == nodes.end()) { 
		nodes.emplace(id, Node(id)); 

		int k = nodes.size() - 1;
		nodes[id].pos.x = ScreenWidth / 4 + (ScreenWidth * 7.0f / 40) * (k / 5);
		nodes[id].pos.y = ScreenHeight / 4 + (ScreenWidth * 5.0f / 40) * (k % 5);

		if (k%5 >= 3) {
			nodes[id].pos.x += (ScreenWidth * 7.00f / 80);
			nodes[id].pos.y -= (ScreenWidth * 25.0f / 80);
		}
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

void Graph::delete_node(int id) {
	if (nodes.find(id) == nodes.end()) { std::cout << "Cant find node\n"; return; }

	if (is_directed == false) {
		for (auto& neighbor : nodes[id].adj) {
			int i = 0;
			for (auto& x : nodes[neighbor.first].adj) {
				if (x.first == id) {
					nodes[neighbor.first].adj.erase(nodes[neighbor.first].adj.begin() + i);
					break;
				}
				i++;
			}
		}
	}

	nodes.erase(id);
	if (active_node1 == id) { active_node1 = -1; }
}

void Graph::update() {
	static int cur_node = -1;

	Vector2 mouse = GetMousePosition();
	
	// update cur_node (moving)
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && cur_node == -1) { 
		for (auto& node : nodes) {
			if (CheckCollisionPointCircle(mouse, node.second.pos, node_rad)) {
				cur_node = node.first;
				break;
			}
		}
	}

	// update active_node (highlight)
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		bool miss = true;

		for (auto& node : nodes) {
			if (CheckCollisionPointCircle(mouse, node.second.pos, node_rad)) {
				if (active_node1 != node.first) {
					if (active_node1 != -1) { nodes[active_node1].is_highlighted = false; }
					active_node1 = node.first;
					node.second.is_highlighted = true;
				}
				else {
					active_node1 = -1;
					node.second.is_highlighted = false;
				}
				miss = false;
				break;
			}
		}
		if (miss == true) { nodes[active_node1].is_highlighted = false; active_node1 = -1; }
	}

	if (cur_node >= 0) {
		nodes[cur_node].pos = mouse;

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) { cur_node = -1; }
	}

	//if (active_node1 >= 0 && buttondel)
}

void Graph::clear() {
	nodes.clear();
}

int Graph::get_active1() {
	return active_node1;
}

void Graph::rand_graph(int n_vertex, int n_edge) {
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
		std::cout << "Node: " << x.first;
		//printf("(%f, %f) \n", x.second.pos.x, x.second.pos.y);
		std::cout << std::endl;
		for (const auto& neighbor : x.second.adj) {
			printf("To: %d; Weight: %d\n", neighbor.first, neighbor.second);
		}
	}
}

void Graph::draw_node(Node node) {
	int width = MeasureText(std::to_string(node.id).c_str(), 20);
	int centerX = node.pos.x;
	int centerY = node.pos.y;

	if (node.is_highlighted == false) { DrawCircleV(node.pos, node_rad, C[1]); } else { DrawCircleV(node.pos, node_rad, C[5]); }
	DrawCircleLinesV(node.pos, node_rad, C[3]);
	DrawText(std::to_string(node.id).c_str(), centerX - node_rad / 8, centerY - node_rad / 5, 20, C[0]);
	//std::cout << "Drawing node id: " << node.id << std::endl;
}

void Graph::draw_edge(int from, int to, int weight) {
	DrawLineEx(nodes[from].pos, nodes[to].pos, 3.0f, C[3]);

	// display weight
	float posX = nodes[from].pos.x + (4.45f / 10.0f) * (nodes[to].pos.x - nodes[from].pos.x) - 7.0f;
	float posY = nodes[from].pos.y + (4.45f / 10.0f) * (nodes[to].pos.y - nodes[from].pos.y) - 7.0f;

	float displaceX = nodes[from].pos.y - nodes[to].pos.y;
	float displaceY = nodes[to].pos.x - nodes[from].pos.x;
	float distance = sqrt(displaceX * displaceX + displaceY * displaceY);
	displaceX /= distance / 18; displaceY /= distance / 18;
	if (displaceX < 0) { displaceX = -displaceX; displaceY = -displaceY; } // keep the edge's weight to the right side

	DrawText(std::to_string(weight).c_str(), posX + displaceX, posY + displaceY, 20, C[0]);
}

void Graph::draw() {
	for (auto& node : nodes) {
		int from = node.first;
		for (auto& neighbor : node.second.adj) {
			int to = neighbor.first;
			int weight = neighbor.second;
			if (from < to) { draw_edge(from, to, weight); }
 		}

		draw_node(node.second);
	}
}