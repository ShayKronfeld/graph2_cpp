/*
NAME: shay kronfeld
ID: 322234782
EMAIL: kronfeldshay@gmail.com
*/

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Graph.hpp"
#include <vector>
#include <string>
#include <unordered_set>
#include <stack>

using namespace std;

namespace ariel {

        class Algorithms{

        private:
                static string isContainsHelper(const Graph& g, size_t source, vector<size_t>& visited, vector<size_t>& stack_of_cycle, size_t parent);

                
        public:
                // Depth First Search (DFS) algorithm
                static void dfs(const Graph& graph, size_t start, unordered_set<int>& visited, stack<int>& st);

                // Check if the graph is connected
                static bool isConnected(const Graph& graph);

                // Check if the graph contains a negative cycle
                static bool hasNegativeCycle(const Graph& graph);

                // Bellman-Ford algorithm to find shortest paths from a single source vertex
               static pair<std::vector<int>, std::vector<std::size_t>> bellmanFord(const Graph& graph, std::size_t start, bool returnParent = false);

                // Floyd-Warshall's algorithm to find all pairs shortest paths in a graph
                static vector<vector<int>> floydWarshall(const Graph& graph);

                // Find the shortest path between two vertices in the graph
                static string shortestPath(const Graph& graph, size_t u, size_t v);

                // check if the graph contain cycle
                static string isContainsCycle(const Graph& graph);

                // check if the graph is bipartite
                static string isBipartite (const Graph& graph);
                

        };
} // namespace ariel

#endif // ALGORITHMS_H
