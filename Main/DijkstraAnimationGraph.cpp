#include "DijkstraAnimationGraph.hpp"

bool DijkstraAnimationGraph::is_finnished() { 
	return (is_running == false);
}

void DijkstraAnimationGraph::load_state(int start) {
	states = graph.dijkstra_steps(start);
	/*
	for (int i = 0; i < states.size(); i++) {
		printf("State : %d\n", i);
		printf("Active Node : %d\n", states[i].current_node);
		printf("Active Edge : %d %d\n", states[i].active_edge.first, states[i].active_edge.second);
		printf("\n");
	}*/

	if (states.empty() == true) { is_running = false; return; }
	states.push_back(states.back());
	states.back().current_node = -1; states.back().active_edge = { -1,-1 };
	//blank state

	current_state = 0;
	is_running = true;
}

void DijkstraAnimationGraph::next_state() {
	if (this->frameCounter < this->delayFrame) { frameCounter++; return; }

	this->frameCounter = 0;

	if (current_state < states.size() - 1) { current_state++; }
	else { is_running = false; current_state = -1; }
}

void DijkstraAnimationGraph::prev_state() {
	if (current_state > 0) { current_state--; }
}

void DijkstraAnimationGraph::render() {
	if (is_running == false) { return; }
	graph.set_state(states[current_state]);
}
