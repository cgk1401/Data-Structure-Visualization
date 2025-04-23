#include "DijkstraAnimationGraph.hpp"

bool DijkstraAnimationGraph::is_finnished() { 
	return (is_running == false);
}

void DijkstraAnimationGraph::set_auto(bool is_at) {
	this->is_auto = is_at;
}

void DijkstraAnimationGraph::set_path_shown(bool is_shown) {
	this->is_path_shown = is_shown;
}

void DijkstraAnimationGraph::set_duration(float speed) {
	this->duration = speed;
}

void DijkstraAnimationGraph::load_state_general(int start) {
	states = graph.dijkstra_steps(start);

	if (states.empty() == true) { is_running = false; return; }
	states.push_back(states.back());
	states.back().current_node = -1; states.back().active_edge = { -1,-1 };
	//blank state

	animation_time = 0.0f;
	current_state = 0;
	is_running = true;
}

void DijkstraAnimationGraph::load_state_paths(int end) {
	if (states.empty()) { return; }
	std::unordered_map<int, int> previous = states.back().previous;
	std::vector<Graph::GraphStage> path_states = graph.dijkstra_paths(end, previous);

	if (path_states.empty() == true) { return; }

	path = path_states;
	animation_time = 0.0f;
	path_state = 0;
	is_path_shown = true;
}

void DijkstraAnimationGraph::next_state() {
	if (is_auto == true) {
		animation_time += GetFrameTime();
		float t = animation_time / duration;
		if (t >= 1.0f) { animation_time = 0.0f; } else { return; }
	}

	if (current_state < states.size() - 1) { current_state++; }
	else { is_running = false; current_state = -1; }
}

void DijkstraAnimationGraph::prev_state() {
	if (current_state > 0) { current_state--; }
}

void DijkstraAnimationGraph::show_distance() {
	if (states.empty()) { return; }
	graph.set_state(states.back());
}

void DijkstraAnimationGraph::render() {
	if (is_running == false) { return; }
	graph.set_state(states[current_state]);
}

void DijkstraAnimationGraph::render_path() {
	if (is_path_shown == false)  return;

	graph.set_state(path[path_state]);

	animation_time += GetFrameTime();
	float t = animation_time / duration;
	if (t >= 1.0f) { // faster than normal 
		animation_time = 0.0f;
		path_state++; path_state %= path.size(); //loop
	}
}
