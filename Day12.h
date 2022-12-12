#pragma once

#include <string>
#include <vector>
#include <array>

constexpr size_t N = 41 * 181;

using Graph = std::vector<std::vector<short>>;

int day12P1(std::vector<std::string> input);
int day12P2(std::vector<std::string> input);

Graph getGraph(std::vector<std::string> input, size_t& start, size_t& end);
Graph getInvertedGraph(std::vector<std::string> input, size_t& end);

void djikstra(Graph graph, size_t& start, size_t& end, std::array<int, N>& dist, std::array<size_t, N>& prev);