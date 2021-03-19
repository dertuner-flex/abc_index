#pragma once

#include <vector>
#include <cassert>

class UndirectedGraph {
public:
	UndirectedGraph(const std::vector<std::vector<int>>& adj_list);

	std::vector<int> AllDegrees() const;
	int CountVertex() const;
	int CountEdge() const;
	std::vector<std::vector<int>> AdjMatrix() const;
private:
	int CalculateCountEdge() const;
	int count_vertex_;
	int count_edge_;
	std::vector<std::vector<int>> adj_list_;
};


UndirectedGraph GenerateKthSimpleGraph(int n_vertex, uint64_t bit_representation) {
	assert(n_vertex <= 8);
	uint64_t step = 0;
	std::vector<std::vector<int>> adj_matrix(n_vertex, std::vector<int>(n_vertex, 0));
	for (int i = 0; i < n_vertex; ++i) {
		for (int j = 0; j < n_vertex - i; ++j) {
			adj_matrix[i][j] = (bit_representation >> step) & 1;
			++step;
			adj_matrix[j][i] = adj_matrix[i][j];
		}
	}


}