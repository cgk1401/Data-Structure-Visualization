#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstdlib>

#include "raylib.h"
#include "Graph.hpp"
#include "Config.hpp"

// ------------------------- Graph class -----------------------
bool Graph::add_node(int id) {
	if (nodes.find(id) == nodes.end()) {
		nodes.emplace(id, Node(id));

		float minX = ScreenWidth / 5.0f;
		float maxX = ScreenWidth;
		float minY = 0.0f;
		float maxY = ScreenHeight;
		nodes[id].pos.x = minX + GetRandomValue(0, 10000) / 10000.0f * (maxX - minX);
		nodes[id].pos.y = minY + GetRandomValue(0, 10000) / 10000.0f * (maxY - minY);

		return true;
	}
	return false;
}

bool Graph::add_edge(int id1, int id2, int w) {
	if (nodes.find(id1) != nodes.end() && nodes.find(id2) != nodes.end()) {
		delete_edge(id1, id2); // delete the edge if it already exists

		nodes[id1].adj.push_back({ id2, w });

		if (is_directed == false) {
			nodes[id2].adj.push_back({ id1, w });
		}
		return true;
	}
	return false;
}

bool Graph::delete_node(int id) {
	if (nodes.find(id) == nodes.end()) { std::cout << "Cant find node\n"; return false; }

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
	return true;
}

bool Graph::delete_edge(int id1, int id2) {
	if (nodes.find(id1) == nodes.end() || nodes.find(id2) == nodes.end()) { std::cout << "Cant find node\n"; return false; }
	int i = 0;
	bool found = false;
	for (auto& x : nodes[id1].adj) {
		if (x.first == id2) {
			nodes[id1].adj.erase(nodes[id1].adj.begin() + i); // it work?
			found = true;
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

	return found;
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

bool Graph::rand_graph(int n_vertex, int n_edge) {
	if (is_directed == false && n_edge > ((n_vertex - 1) * n_vertex) / 2) { std::cout << "Too many edge for that number of vertex\n"; return false; }
	if (is_directed == true && n_edge > (n_vertex - 1) * n_vertex) { std::cout << "Too many edge for that number of vertex\n"; return false; }

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
	return true;
}

void Graph::input_graph(std::ifstream& fin) {
	int n_vertex; //nums of nodes
	int n_edge; //nums of edges
	bool is_dir; //directed/undirected graph
	fin >> n_vertex >> n_edge;
	is_directed = false;

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

// ------------------------- Force directed -----------------------
void Graph::set_fix_graph(bool is_fixed) {
	this->is_graph_fixed = is_fixed;
}

void Graph::update_repulsive_force() {
	for (auto it1 = nodes.begin(); it1 != nodes.end(); ++it1) {
		for (auto it2 = std::next(it1); it2 != nodes.end(); ++it2) {
			Node& a = it1->second;
			Node& b = it2->second;

			Vector2 delta = Vector2Subtract(a.pos, b.pos);
			float distance = Vector2Length(delta) + 0.01f; // avoid division by zero
			float force_magnitude = k_repulsion / (distance * distance);
			Vector2 force = Vector2Scale(Vector2Normalize(delta), force_magnitude);

			a.force = Vector2Add(a.force, force);
			b.force = Vector2Subtract(b.force, force);
		}
	}
}

void Graph::update_attractive_force() {
	for (auto& node : nodes) {
		Node& a = node.second;
		for (auto& neighbor : a.adj) {
			Node& b = nodes[neighbor.first];
			if (a.id < b.id) { continue; } // avoid double counting

			Vector2 delta = Vector2Subtract(a.pos, b.pos);
			float distance = Vector2Length(delta) + 0.01f; // avoid div by zero
			float force_magnitude = k_spring * (distance - spring_length);
			Vector2 force = Vector2Scale(Vector2Normalize(delta), -force_magnitude);

			a.force = Vector2Add(a.force, force);
			b.force = Vector2Subtract(b.force, force);
		}
	}
}

void Graph::update_centering_force() {
	Vector2 center = { ScreenWidth * 0.6f, ScreenHeight * 0.5f };
	float centering_strength = 10.0f;

	for (auto& nd : nodes) {
		Node& node = nd.second;
		Vector2 delta = Vector2Subtract(center, node.pos);
		Vector2 centering_force = Vector2Scale(delta, centering_strength);
		node.force = Vector2Add(node.force, centering_force);
	}
}

void Graph::update_pos() {
	float dt = GetFrameTime();
	for (auto& nd : nodes) {
		Node& node = nd.second;
		node.velocity = Vector2Add(node.velocity, Vector2Scale(node.force, dt));
		node.velocity = Vector2Scale(node.velocity, damping); // to stabilize
		node.pos = Vector2Add(node.pos, Vector2Scale(node.velocity, dt));
		node.force = { 0, 0 }; // reset force
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

	if (is_graph_fixed == false) {
		update_attractive_force();
		update_repulsive_force();
		update_centering_force();
		update_pos();
	}
}

// ------------------------- Dijkstra's algorithm -----------------------
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
		steps.push_back({ processed, previous, node_txt, a, { -1, -1 }, { 0, 1 } });

		steps.push_back({ processed, previous, node_txt, a, { -1, -1 }, { 0, 2 } });
		if (processed[a] == true) { continue; }
		processed[a] = true;

		steps.push_back({ processed, previous, node_txt, a, { -1, -1 }, { 0, 3 } });

		for (const auto& neighbor : nodes[a].adj) {
			int b = neighbor.first;
			int w = neighbor.second;
			steps.push_back({ processed, previous, node_txt, a, { a, b }, { 5, 6, 7 } });

			steps.push_back({ processed, previous, node_txt, a, { a, b }, { 5, 9 } });
			if (processed[b] == true) { continue; }

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
			steps.push_back({ processed, previous, node_txt, a, { a, b }, { 5, 11 } });
			//std::cout << node_txt[b] << std::endl;

			if (distance[a] + w < distance[b]) {
				distance[b] = distance[a] + w;
				previous[b] = a;
				pq.push({ distance[b], b });
				node_txt[b] = std::to_string(distance[b]);

				steps.push_back({ processed, previous, node_txt, a, { a, b }, { 5, 12, 13, 14 } });
			}
			else { node_txt[b] = std::to_string(distance[b]); }

			steps.push_back({ processed, previous, node_txt, a, { -1, -1 }, { 5 } });
		}
		steps.push_back({ processed, previous, node_txt, -1, { -1, -1 }, { 0 } });
		//kind of wasteful, but it works
	}

	return steps;
}

std::vector<Graph::GraphStage> Graph::dijkstra_paths(int end, std::unordered_map<int, int> previous) {
	std::vector<GraphStage> steps;

	if (nodes.size() == 0) { std::cout << "Graph is empty\n"; return steps; }
	if (previous.find(end) == previous.end()) { std::cout << "Can not find node\n"; return steps; }
	if (previous[end] == -1) { std::cout << "No path\n"; return steps; }

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
	this->highlight_line = state.highlight_line;
}

// ------------------------- Drawing -----------------------
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
			float startX = (ScreenWidth / 260.0f) + 12.5f;
			float startY = ScreenHeight / 10.0f;
			float spacing = ScreenHeight / 36.0f;
			DrawRectangleRounded({ startX - 10, startY - 20, ScreenWidth / 5.2f - 5, spacing * DijkstraSteps.size() + 30 }, 0.1f, 10, C[2]); // Background for the code
			for (int i = 0; i < DijkstraSteps.size(); i++) {
				for (int j = 0; j < highlight_line.size(); j++) {
					if (i == highlight_line[j]) {
						DrawRectangle(startX - 10, startY + spacing * i - 5, ScreenWidth / 5.2f - 4, 28, tmp);
						break;
					}
				}
				DrawText(DijkstraSteps[i].c_str(), startX, startY + spacing * i, 19, C[0]);
			}
		}
	}
}