#include "Day12.h"

#include <iostream>
#include <stack>
#include <Windows.h>

int day12P1(std::vector<std::string> input) {
	size_t start{}, end{};
	Graph graph{ getGraph(input, start, end) };

	std::array<int, N> dist{ std::array<int, N>() };
	std::array<size_t, N> prev{ std::array<size_t, N>() };

	djikstra(graph, start, end, dist, prev);	

	size_t current{ end };
	while (current != start) {
		std::cout << current << " <- ";
		current = prev[current];
	}
	std::cout << start << '\n';

	return dist[end];
}

int day12P2(std::vector<std::string> input) {
	size_t start{}, end{};
	Graph graph{ getInvertedGraph(input, end) };

	std::array<int, N> dist{ std::array<int, N>() };
	std::array<size_t, N> prev{ std::array<size_t, N>() };

	djikstra(graph, end, end, dist, prev);

	size_t nearest{ 0 };
	for (size_t i{ 0 }; i < input.size(); i++) {
		for (size_t j{ 0 }; j < input[0].size(); j++) {
			if (input[i][j] == 'a' && dist[i * input[0].size() + j] < dist[nearest])
				nearest = i * input[0].size() + j;
		}
	}

	size_t current{ nearest };
	while (current != end) {
		std::cout << current << " <- ";
		current = prev[current];
	}
	std::cout << end << '\n';

	return dist[nearest];
}

Graph getGraph(std::vector<std::string> input, size_t& start, size_t& end) {
	Graph graph{ Graph(N) };

	for (size_t i{ 0 }; i < input.size(); i++) {
		for (size_t j{ 0 }; j < input[0].size(); j++) {
			char& h = input[i][j];
			size_t pos = i * input[0].size() + j;
			if (h == 'S') {
				start = pos;
				h = 'a';
			}
			else if (h == 'E') {
				end = pos;
				h = 'z';
			}
		}
	}
	for (size_t i{ 0 }; i < input.size(); i++) {
		for (size_t j{ 0 }; j < input[0].size(); j++) {
			char& h = input[i][j];
			size_t pos = i * input[0].size() + j;
			std::vector<short>& row = graph[pos];
			row.resize(N);

			if (i > 0 && input[i - 1][j] - h < 2)
				row[pos - input[0].size()] = 1;
			if (i < input.size() - 1 && input[i + 1][j] - h < 2)
				row[pos + input[0].size()] = 1;
			if (j > 0 && input[i][j - 1] - h < 2)
				row[pos - 1] = 1;
			if (j < input[0].size() - 1 && input[i][j + 1] - h < 2)
				row[pos + 1] = 1;
		}
	}

	return graph;
}

Graph getInvertedGraph(std::vector<std::string> input, size_t& end) {
	Graph graph{ Graph(N) };

	for (size_t i{ 0 }; i < input.size(); i++) {
		for (size_t j{ 0 }; j < input[0].size(); j++) {
			char& h = input[i][j];
			size_t pos = i * input[0].size() + j;
			if (h == 'S') {
				h = 'a';
			}
			else if (h == 'E') {
				end = pos;
				h = 'z';
			}
		}
	}
	for (size_t i{ 0 }; i < input.size(); i++) {
		for (size_t j{ 0 }; j < input[0].size(); j++) {
			char& h = input[i][j];
			size_t pos = i * input[0].size() + j;
			std::vector<short>& row = graph[pos];
			row.resize(N);

			if (i > 0 && h - input[i - 1][j] < 2)
				row[pos - input[0].size()] = 1;
			if (i < input.size() - 1 && h - input[i + 1][j] < 2)
				row[pos + input[0].size()] = 1;
			if (j > 0 && h - input[i][j - 1] < 2)
				row[pos - 1] = 1;
			if (j < input[0].size() - 1 && h - input[i][j + 1] < 2)
				row[pos + 1] = 1;
		}
	}

	return graph;
}

void djikstra(Graph graph, size_t& start, size_t& end, std::array<int, N>& dist, std::array<size_t, N>& prev) {
	std::vector<size_t> Q{ std::vector<size_t>() };

	for (size_t v{ 0 }; v < N; v++) {
		dist[v] = INT_MAX - 1;
		prev[v] = -1;
		Q.push_back(v);
	}
	dist[start] = 0;
	Q.shrink_to_fit();

	while (!Q.empty()) {
		auto U{ Q.begin() };
		for (auto V{ Q.begin() }; V != Q.end(); V++)
			if (dist[*V] < dist[*U])
				U = V;

		auto u{ *U };
		Q.erase(U);

		for (auto v : Q) {
			if (graph[u][v] != 0) {
				int alt = dist[u] + graph[u][v];
				if (alt < dist[v]) {
					dist[v] = alt;
					prev[v] = u;
				}
			}
		}
	}
}
