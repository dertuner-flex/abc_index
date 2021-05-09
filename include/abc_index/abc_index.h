#pragma once

#include <cmath>
#include "graph.h"
#include "isomorphism.h"

double abc_index(const UndirectedGraph& graph);
std::vector<std::pair<UndirectedGraph, UndirectedGraph>> FindAllPairNonIsomorphicGraphWithSameABCIndex(int vertex);
