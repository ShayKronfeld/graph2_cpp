/*
NAME: shay kronfeld
ID: 322234782
EMAIL: kronfeldshay@gmail.com
*/

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <limits>
#include <algorithm>
#include <sstream>
#include <deque> 
#include <string>

#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

namespace ariel {

    //Going over the graph in depth
    void Algorithms::dfs(const Graph& graph, size_t start, unordered_set<int>& visited, stack<int>& st) {
        visited.insert(start); 
        st.push(start); // Push the current vertex onto the stack

        for (size_t i = 0; i < graph.getNumberOfVertices(); i++) {
            if (graph.getCellInAdjacencyMatrix(start, i) != 0) { // Check if there is an edge (0 if not)
                size_t neighbor = i;
                if (visited.count(neighbor) == 0) { // Check if the neighbor vertex has not been visited
                    dfs(graph, neighbor, visited, st); // Recursively traverse the neighbor vertex
                }
            }
        }
    }

    /*
    The first DFS and goes over all the vertices.
    If it did not go through all the vertices, the graph is not necessarily connected. 
    Then flip the ribs over and run DFS a second time.
    Only if in both passes of the graph it has passed all the vertices, 
    the graph can be said to be connected.
    */
    bool Algorithms::isConnected(const Graph& graph) {
        if (graph.getNumberOfVertices() <= 0) {
            throw runtime_error("Number of vertices must be positive.");
        }

        unordered_set<int> visited;
        stack<int> st;

        dfs(graph, 0, visited, st); // Run the DFS

        if (visited.size() != graph.getNumberOfVertices()) // dfs not visited all the vertices
            return false;

        size_t numVertices = graph.getNumberOfVertices();

        // Create a reversed graph
        vector<vector<int>> reversedGraph(numVertices, vector<int>(numVertices, 0));
        for (size_t i = 0; i < numVertices; i++) {
            for (size_t j = 0; j < numVertices; j++) {
                if (graph.getCellInAdjacencyMatrix(i, j) != 0) { // Add the edge to the reversed graph if it exists
                    reversedGraph[j][i] = graph.getCellInAdjacencyMatrix(i, j);
                }
            }
        }

        visited.clear();  // Clear visited set

        while (!st.empty()) {   
            auto currentVertex = st.top();
            st.pop();

            if (visited.count(currentVertex) == 0) { // Check if the vertex is not visited
                stack<int> dfsReversedStack;
                unordered_set<int> dfsReversed;
                Graph reversedGraphObj(reversedGraph);

                dfs(reversedGraphObj, currentVertex, dfsReversed, dfsReversedStack); // Run DFS on the reversed graph

                if (dfsReversed.size() != numVertices) {
                    return false;
                }

                // Insert visited vertices into the visited set
                for (int v : dfsReversed) {
                    visited.insert(v);
                }
            }
        }

        // If all vertices are visited, return true
        return true;
    }

    /*
    This function find the shortest paths from a single source vertex to all other vertices in a weighted graph. 
    This is occure by n-1 times of 'relax' to all the vertices in the graph.
    Each iteration attempts to improve the estimated shortest distances to all vertices by considering all edges. 
    */
    pair<vector<int>, vector<size_t>> Algorithms::bellmanFord(const Graph& graph, size_t source, bool returnParent) {
        if (graph.getNumberOfVertices() == 0) {
            throw runtime_error("Graph must have at least one vertex.");
        }

        size_t numberOfVertices = graph.getNumberOfVertices();

        vector<int> distances(numberOfVertices, numeric_limits<int>::max());
        vector<size_t> parents(numberOfVertices, numberOfVertices);

        parents[source] = source; // Set parent of source vertex to source
        distances[source] = 0;

        for (size_t i = 0; i < numberOfVertices - 1; ++i) { // n-1 relaxtion
            for (size_t u = 0; u < numberOfVertices; ++u) { // of all the vertices
                for (size_t v = 0; v < numberOfVertices; ++v) {
                    int edgeWeight = graph.getCellInAdjacencyMatrix(u, v);
                    if (edgeWeight != 0) { // If there is an edge 
                        if (distances[u] != numeric_limits<int>::max() && distances[v] > distances[u] + edgeWeight) { // If shorter path found
                            
                            parents[v] = u; // Update parent of v
                            distances[v] = distances[u] + edgeWeight; // Update distance of v
                        }
                    }
                }
            }
        }

        if (!returnParent) { 
            return make_pair(distances, vector<size_t>()); // return the distances and the empty vectors of parents

        }

        return make_pair(distances, parents); // Return the distances and the parents
    }

    /*
    This function `hasNegativeCycle` determines whether a given graph contains a negative cycle.
    It does so by performing the Bellman-Ford algorithm starting from each vertex in the graph.
    */
    bool Algorithms::hasNegativeCycle(const Graph& graph) {
        size_t numVertices = graph.getNumberOfVertices();
        
        for (size_t i = 0; i < numVertices; i++) {
            auto result = bellmanFord(graph, i, false);
            vector<int> dist = result.first;

            // the last relaxtion (This time the n)
            for (size_t u = 0; u < numVertices; u++) {
                for (size_t v = 0; v < numVertices; v++) {
                    int edgeWeight = graph.getCellInAdjacencyMatrix(u, v);
                    if (edgeWeight != 0 && dist[u] != numeric_limits<int>::max() && dist[u] + edgeWeight < dist[v]) {
                        return true; // if something has changed, there is negative cycle found
                    }
                }
            }
        }
        
        return false; // No negative cycle found
    }


    /*
    This `shortestPath` function finds the shortest path from vertex `u` to vertex `v` 
    in a given graph using the Bellman-Ford algorithm. 
    */
    string Algorithms::shortestPath(const Graph& graph, size_t u, size_t v) {
        size_t numVertices = graph.getNumberOfVertices();

        if (numVertices < 0) {
            throw std::runtime_error("Number of vertices cannot be negative.");
        }
        
         if (Algorithms::hasNegativeCycle(graph)) { //if there is a negative cycle
            return "-1"; 
        }

        // Check if both u and v are within the valid range of vertices
        if (u >= numVertices || v >= numVertices) {
            cout << "Vertex " << (u >= numVertices ? u : v) << " is out of range." << endl;
            return ""; // Return an empty string to indicate failure
        }

        auto result = bellmanFord(graph, u, true); // Use bellmanFord
        vector<int> distances = result.first; // Access the first element of the pair
        vector<size_t> parent = result.second; // Access the second element of the pair

        // Construct the shortest path from v to u using parent information
        vector<size_t> path;
        size_t current_vertex = v;
        while (current_vertex != u) {
            path.push_back(current_vertex);
            current_vertex = parent[current_vertex]; // Use parent information to backtrack the path
            if (current_vertex == numVertices) {
                // If the current vertex reaches the sentinel value numVertices, it means there's no path from v to u
                return "-1";
            }
        }

        path.push_back(u); // Add the starting vertex u to the path

        // Reverse the path to get the correct order from u to v
        reverse(path.begin(), path.end());

        // Convert the path to a string
        ostringstream oss;
        for (size_t i = 0; i < path.size(); i++) {
            if (i > 0) {
                oss << "->";
            }
            oss << path[i];
        }

        return oss.str(); // Return the shortest path as a string
    }

    /*
    This function is a helper function used to detect negative cycles in a directed graph using Depth-First Search (DFS).
    */
    string Algorithms::isContainsHelper(const Graph& graph, size_t source, vector<size_t>& visited, vector<size_t>& stackCycle, size_t parent) {
        size_t numberVertices = graph.getNumberOfVertices();

        visited[source] = 1; //  start the progress
        stackCycle.push_back(source);

        for (size_t v = 0; v < numberVertices; v++) {
            int weight = graph.getCellInAdjacencyMatrix(source, v);
            if (weight != 0) { // there is edge
                if (visited[v] == 0) { // Unvisited neighbor
                    string path = isContainsHelper(graph, v, visited, stackCycle, source);
                    if (path != "-1") {
                        return path;
                    }
                } else if (visited[v] == 1) { // Back edge, negative cycle detected
                    string path = to_string(v);
                    while (stackCycle.back() != v) { 
                        path = to_string(stackCycle.back()) + "->" + path;
                        stackCycle.pop_back();
                    }
                    path = to_string(v) + "->" + path;
                    return path;
                }
            }
        }

        visited[source] = 2; // Mark as visited and finished
        stackCycle.pop_back();

        return "-1"; 
    }

    /*
    This function, `isContainsCycle`, determines whether the given graph contains a cycle.
     It does so by performing a depth-first search (DFS) traversal starting from each vertex in the graph. During the traversal,
     it keeps track of visited vertices and maintains a stack to detect back edges, 
     which indicate the presence of a cycle
    */
    string Algorithms::isContainsCycle(const Graph& graph) {
        size_t numVertices = graph.getNumberOfVertices();
        const vector<vector<int>>& adjMatrix = graph.getAdjMatrix();
        vector<size_t> visited(numVertices, 0);
        vector<size_t> stackCycle;

        for (size_t i = 0; i < numVertices; i++) {
            if (visited[i] == 0) { // If the current vertex has not been visited
                string path = isContainsHelper(graph, i, visited, stackCycle, numVertices); // Check if there is a cycle starting from the current vertex
                if (path != "-1") {
                    return path;
                }
            }
        }

        return "-1";
    }
    /*
    This function, `isBipartite`, determines whether the given graph is bipartite or not.
    it performs a depth-first search (DFS) traversal starting from each vertex in the graph.
    During the traversal, it assigns colors to vertices such that adjacent vertices have different colors.
    If it encounters a vertex with the same color as its neighbor, it concludes that the graph is not bipartite.
    If the traversal completes without finding any conflicts in coloring, the function concludes that the graph is bipartite and returns 
    a string indicating the sets A and B along with their respective vertices
    */

    string Algorithms::isBipartite(const Graph& graph) {
        size_t numVertices = graph.getNumberOfVertices();
        vector<int> colors(numVertices, -1); // -1 represents uncolored, 0 represents one side, 1 represents the other side
        stack<size_t> st;
        bool isBipartite = true; // Flag to track overall bipartiteness
        unordered_set<int> sideA, sideB; 

        // Traverse all vertices to handle disconnected components
        for (size_t startVertex = 0; startVertex < numVertices; ++startVertex) {
            if (colors[startVertex] == -1) { // If vertex is uncolored
                colors[startVertex] = 0; // Start coloring with one side
                sideA.insert(startVertex); 

                st.push(startVertex); // Push the current vertex onto the stack

                while (!st.empty()) {
                    size_t currentVertex = st.top();
                    st.pop();

                    // Visit all neighbors of the current vertex
                    for (size_t neighbor = 0; neighbor < numVertices; ++neighbor) {
                        if (graph.getCellInAdjacencyMatrix(currentVertex, neighbor) != 0) { // There is an edge
                            if (colors[neighbor] == -1) { // If neighbor is uncolored
                                colors[neighbor] = 1 - colors[currentVertex]; // Color neighbor with the opposite side
                                if (colors[neighbor] == 0) {
                                    sideA.insert(neighbor); // Add neighbor to side A
                                } else {
                                    sideB.insert(neighbor); // Add neighbor to side B
                                }
                                st.push(neighbor); // Push neighbor onto the stack
                            } else if (colors[neighbor] == colors[currentVertex]) { // If neighbor has the same color as current vertex
                                isBipartite = false; // Graph is not bipartite
                                break; // No need to continue checking neighbors in this component
                            }
                        }
                    }
                }
            }

            if (!isBipartite) {
                break; // No need to check other connected components if one is not bipartite
            }
        }

        if (isBipartite) {
            ostringstream oss;
            oss << "The graph is bipartite: A={";
            vector<int> sortedSideA(sideA.begin(), sideA.end());
            sort(sortedSideA.begin(), sortedSideA.end());
            for (size_t i = 0; i < sortedSideA.size(); ++i) {
                if (i > 0) {
                    oss << ", ";
                }
                oss << sortedSideA[i];
            }
            oss << "}, B={";
            vector<int> sortedSideB(sideB.begin(), sideB.end());
            sort(sortedSideB.begin(), sortedSideB.end());
            for (size_t i = 0; i < sortedSideB.size(); ++i) {
                if (i > 0) {
                    oss << ", ";
                }
                oss << sortedSideB[i];
            }
            oss << "}." << " ";
            return oss.str();
        } else {
            return "0";
        }
    }



}