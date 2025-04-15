#ifndef DIJKSTRAANIMATIONGRAPH_HPP
#define DIJKSTRAANIMATIONGRAPH_HPP

#include "Graph.hpp"

class DijkstraAnimationGraph {
private:
	Graph& graph;
	std::vector<Graph::GraphStage> states;
	int current_state = -1;
	bool is_running = false;

	std::vector<Graph::GraphStage> path;
	int path_state = -1;
	bool is_path_shown = false;

	int frameCounter = 0;
	int delayFrame = 40;

	bool is_auto = true;
public:
	DijkstraAnimationGraph(Graph& g) : graph(g) {}

	bool is_finnished();

	void set_auto(bool is_at);
	void set_path_shown(bool is_shown);

	void load_state_general(int start);
	void next_state();
	void prev_state();

	void load_state_paths(int end);

	void render();
	void render_path();
};

#endif // !DIJKSTRAANIMATIONGRAPH_HPP