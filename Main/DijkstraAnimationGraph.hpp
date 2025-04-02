#ifndef DIJKSTRAANIMATIONGRAPH_HPP
#define DIJKSTRAANIMATIONGRAPH_HPP

#include "Graph.hpp"

class DijkstraAnimationGraph {
private:
	Graph& graph;
	std::vector<Graph::GraphStage> states;
	int current_state = -1;
	bool is_running = false;

	int frameCounter = 0;
	int delayFrame = 40;

public:
	DijkstraAnimationGraph(Graph& g) : graph(g) {}

	bool is_finnished();

	void load_state(int start);
	void next_state();
	void prev_state();
	void render();
};

#endif // !DIJKSTRAANIMATIONGRAPH_HPP