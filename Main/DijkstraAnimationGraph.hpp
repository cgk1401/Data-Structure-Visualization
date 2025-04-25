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

	float duration = 1.0f;         
	float animation_time = 0.0f;    

	bool is_auto = true;
public:
	DijkstraAnimationGraph(Graph& g) : graph(g) {}

	bool is_finnished();

	void set_auto(bool is_at);
	void set_path_shown(bool is_shown);
	void set_duration(float speed);

	void load_state_general(int start);
	void next_state();
	void prev_state();

	void load_state_paths(int end);

	void show_distance();

	void render();
	void render_path();
};

#endif // !DIJKSTRAANIMATIONGRAPH_HPP