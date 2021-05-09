#pragma once

#include <iostream>
#include <vector>
#include <cassert>
#include <cstdint>

class UndirectedGraph {
public:
	UndirectedGraph(const std::vector<std::vector<int>>& adj_list);

	std::vector<int> AllDegrees() const;
	int CountVertex() const;
	int CountEdge() const;
	std::vector<std::vector<int>> AdjMatrix() const;
	const std::vector<std::vector<int>> AdjList() const;
	void PrintAdjMatrix(std::ostream& out = std::cout) const;
	static std::vector<std::vector<int>> ConvertAdjMatrixToAdjList(const std::vector<std::vector<int>>& adj_matrix);
	static std::vector<std::vector<int>> ConvertAdjListToAdjMatrix(const std::vector<std::vector<int>>& adj_list);
	void Serialize(std::ostream& out);
	bool IsConnected() const;
private:
	void DFS(int vertex, std::vector<bool>* used) const;
	int CalculateCountEdge() const;
	int count_vertex_;
	int count_edge_;
	std::vector<std::vector<int>> adj_list_;
};

UndirectedGraph GenerateKthSimpleGraph(int n_vertex, uint64_t bit_representation);
std::vector<UndirectedGraph> GenerateAllSimpleGraph(int n_vertex);
bool IsTree(const UndirectedGraph& graph);
