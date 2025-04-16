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
		delete_edge(id1, id2); // delete the edge if it already exists

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

void Graph::delete_edge(int id1, int id2) {
	if (nodes.find(id1) == nodes.end() || nodes.find(id2) == nodes.end()) { std::cout << "Cant find node\n"; return; }
	int i = 0;
	for (auto& x : nodes[id1].adj) {
		if (x.first == id2) {
			nodes[id1].adj.erase(nodes[id1].adj.begin() + i);
			break;
		}
		i++;
	}
	if (is_directed == false) {
		i = 0;
		for (auto& x : nodes[id2].adj) {
			if (x.first == id1) {
				nodes[id2].adj.erase(nodes[id2].adj.begin() + i);
				break;
			}
			i++;
		}
	}
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
					active_node1 = node.first;
				}
				else {
					active_node1 = -1;
				}
				miss = false;
				break;
			}
		}
		if (miss == true) { active_node1 = -1; }
	}

	// update active_edge (highlight)
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		bool miss = true;

		for (auto& node : nodes) {
			int from = node.first;
			for (auto& neighbor : node.second.adj) {
				int to = neighbor.first;
				if (CheckCollisionPointLine(mouse, nodes[from].pos, nodes[to].pos, 3.0f) == true) {
					if (active_edge.first != from || active_edge.second != to) {
						if (is_directed == false && from > to) { active_edge = { to, from }; }
						else { active_edge = { from, to }; }
						//std::cout << "Edge from " << active_edge.first << " to " << active_edge.second << std::endl;
					}
					else {
						active_edge = { -1, -1 };
					}
					miss = false;
					break;
				}
			}
		}
		if (miss == true) { active_edge = { -1, -1 }; }
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

std::pair<int, int> Graph::get_active2() {
	return active_edge;
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

void Graph::dijkstra(int start) {
	if (nodes.find(start) == nodes.end()) { std::cout << "Can not find node\n"; return; }

	int n = nodes.size(); // num of nodes
	std::unordered_map<int, int> distance;
	std::unordered_map<int, bool> processed;
	std::unordered_map<int, int> previous;
	for (auto& node : nodes) {
		distance[node.first] = INT_MAX;
		processed[node.first] = false;
		previous[node.first] = -1;
	}
	distance[start] = 0;

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
	pq.push({ 0, start });

	while (pq.empty() == false) {
		int a = pq.top().second; pq.pop();
		if (processed[a] == true) { continue; }
		processed[a] = true;

		for (const auto& neighbor : nodes[a].adj) {
			int b = neighbor.first;
			int w = neighbor.second;
			if (distance[a] + w < distance[b]) {
				distance[b] = distance[a] + w;
				previous[b] = a;
				pq.push({ distance[b], b });
			}
		}
	}

	for (int i = 0; i < n; i++) {
		printf("To %d: %d\n", i, distance[i]);
		int j = i;
		while (previous[j] != -1) {
			printf("%d <- ", j);
			j = previous[j];
		}
		printf("%d\n", start);
	}
}

std::vector<Graph::GraphStage> Graph::dijkstra_steps(int start) {
	std::vector<GraphStage> steps;
	if (nodes.find(start) == nodes.end()) { std::cout << "Can not find node\n"; return steps; }

	int n = nodes.size(); // num of nodes
	std::unordered_map<int, int> distance;
	std::unordered_map<int, bool> processed;
	std::unordered_map<int, int> previous;
	std::unordered_map<int, std::string> node_txt;
	for (auto& node : nodes) {
		distance[node.first] = INT_MAX;
		processed[node.first] = false;
		previous[node.first] = -1;
		node_txt[node.first] = "INF";
	}
	distance[start] = 0;
	node_txt[start] = "0";

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
	pq.push({ 0, start });

	while (pq.empty() == false) {
		int a = pq.top().second; pq.pop();
		if (processed[a] == true) { continue; }
		processed[a] = true;

		steps.push_back({ processed, previous, node_txt, a, { -1,-1 } });

		for (const auto& neighbor : nodes[a].adj) {
			int b = neighbor.first;
			int w = neighbor.second;

			if (processed[b] == true) { continue; }

			steps.push_back({ processed, previous, node_txt, a, { a, b } });

			if (distance[a] + w < distance[b]) {
				if (distance[b] == INT_MAX) {
					node_txt[b] = "INF > " + std::to_string(distance[a]) + "+" + std::to_string(w);
				}
				else {
					node_txt[b] = std::to_string(distance[b]) + " > " + std::to_string(distance[a]) + "+" + std::to_string(w);
				}
			}
			else { 
				node_txt[b] = std::to_string(distance[b]) + " < " + std::to_string(distance[a]) + "+" + std::to_string(w);
			}

			steps.push_back({ processed, previous, node_txt, a, { a, b } });
			//std::cout << node_txt[b] << std::endl;

			if (distance[a] + w < distance[b]) {
				distance[b] = distance[a] + w;
				previous[b] = a;
				pq.push({ distance[b], b });
			}
			node_txt[b] = std::to_string(distance[b]);

			steps.push_back({ processed, previous, node_txt, a, { a, b} });
		}
	}

	return steps;
}

std::vector<Graph::GraphStage> Graph::dijkstra_paths(int end, std::unordered_map<int, int> previous) {
	std::vector<GraphStage> steps;

	steps.push_back({ {}, {}, {}, end, { -1,-1 } });
	while (end != -1 && previous[end] != -1) {
		steps.push_back({ {}, {}, {}, end, {previous[end], end} });
		end = previous[end];
	}
	steps.push_back({ {}, {}, {}, end, { -1,-1 } });

	std::reverse(steps.begin(), steps.end());

	return steps;
}

void Graph::set_running_dijkstra(bool is_running) {
	is_running_dijkstra = is_running;
}

void Graph::set_showing_code(bool is_showing) {
	is_showing_code = is_showing;
}

void Graph::set_state(GraphStage state) {
	active_node1 = state.current_node;
	active_edge = state.active_edge;

	if (is_directed == false && active_edge.first > active_edge.second) {
		active_edge = { active_edge.second, active_edge.first };
	}

	this->processed = state.processed;
	this->previous = state.previous;
	this->node_txt = state.node_txt;
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

	if (node.id != active_node1) { DrawCircleV(node.pos, node_rad, C[1]); }	else { DrawCircleV(node.pos, node_rad, C[5]); }
	DrawCircleLinesV(node.pos, node_rad, C[3]);
	int text_width = MeasureText(std::to_string(node.id).c_str(), 20);
	DrawText(std::to_string(node.id).c_str(), centerX - text_width / 2, centerY - 10, 20, C[0]);
	//std::cout << "Drawing node id: " << node.id << std::endl;
}

void Graph::draw_edge(int from, int to, int weight) {
	if (from == active_edge.first && to == active_edge.second) 
		{ DrawLineEx(nodes[from].pos, nodes[to].pos, 7.5f, C[5]); }
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
			if (is_directed == false && from < to) { draw_edge(from, to, weight); }
 		}
	}


	Color tmp = Color{
		(unsigned char)fmin(C[1].r * 0.9f, 255),
		(unsigned char)fmin(C[1].g * 0.9f, 255),
		(unsigned char)fmin(C[1].b * 0.9f, 255),
		(unsigned char)fmax(C[1].a - 80, 0)
	};
	for (auto& node : nodes) {
		draw_node(node.second);

		if (is_running_dijkstra == true) { 
			// displace the distance when running dijkstra
			if (processed[node.first] == true) { DrawCircleLinesV(node.second.pos, node_rad * 1.1, C[5]); }

			DrawRectangle(node.second.pos.x + 1.25 * node_rad - 5, node.second.pos.y - 5, MeasureText(node_txt[node.first].c_str(), 20) + 10, 30, tmp);
			DrawText(node_txt[node.first].c_str(), node.second.pos.x + 1.25 * node_rad, node.second.pos.y, 20, C[0]);

			// code block
			if (is_showing_code == false) { continue; }
			float startX = (ScreenWidth / 5.0f) * 0.055f;
			float startY = ScreenHeight / 8.0f;
			float spacing = ScreenHeight / 36.0f;
			for (int i = 0; i < DijkstraSteps.size(); i++) {
				DrawText(DijkstraSteps[i].c_str(), startX, startY + spacing * i, 20, C[0]);
			}
		}
	}
}