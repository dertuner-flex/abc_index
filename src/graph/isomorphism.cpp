#include "isomorphism.h"
#include <cassert>

bool check_isomorphism(const UndirectedGraph& first, const UndirectedGraph& second) {
	if (first.CountVertex() != second.CountVertex() || first.CountEdge() != second.CountEdge()) {
		return false;
	}

	int n_vertex = first.CountVertex(), n_edge = first.CountEdge();
	std::vector<int> degrees_first = first.AllDegrees();
	std::vector<int> degrees_second = second.AllDegrees();

	std::vector<int> current_permutation(n_vertex);
	for (int i = 1; i <= n_vertex; ++i) {
		current_permutation[i - 1] = i - 1;
	}

	auto adj_matrix_first = first.AdjMatrix();
	auto adj_matrix_second = second.AdjMatrix();

	do {
		bool is_isomorphism = true;
		for (size_t i = 0; i < current_permutation.size(); ++i) {
			int first_idx = current_permutation[i];
			int second_idx = i;
			if (degrees_first[first_idx] != degrees_second[second_idx]) {
				is_isomorphism = false;
				break;
			}
		}
		if (!is_isomorphism) {
			continue;
		}

		for (int i = 0; i < n_vertex && is_isomorphism; ++i) {
			for (int j = 0; j < n_vertex; ++j) {
				int new_i = current_permutation[i];
				int new_j = current_permutation[j];
				if (adj_matrix_first[new_i][new_j] != adj_matrix_second[i][j]) {
					is_isomorphism = false;
					break;
				}
			}
		}

		if (is_isomorphism) {
			return true;
		}

	} while (std::next_permutation(current_permutation.begin(), current_permutation.end()));

	return false;
}
