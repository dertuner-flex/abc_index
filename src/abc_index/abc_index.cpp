#include "abc_index.h"

double abc_index(const UndirectedGraph& graph) {
	auto degrees = graph.AllDegrees();
	auto f = [](double x, double y) {
		return sqrt((x + y - 2) / (x * y));
	};
	double index = 0;
	auto adj_list = graph.AdjList();
	for (int i = 0; i < adj_list.size(); ++i) {
		for (int j = 0; j < adj_list[i].size(); ++j) {
			int u = i, v = adj_list[i][j];
			index += f(degrees[u], degrees[v]);
		}
	}

	return index / 2;
}
