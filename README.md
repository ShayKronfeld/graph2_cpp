# Graph Library Documentation

**ID:** 322234782  
**Email:** kronfeldshay@gmail.com  

## Overview

This library provides an implementation of a Graph class in C++. The graph is represented using an adjacency matrix and supports both weighted and unweighted graphs. Various operations are supported, including addition, subtraction, comparison, and scalar multiplication/division of graphs. In addition, provides various algorithms for working with graphs, including depth-first search (DFS), Bellman-Ford algorithm, cycle detection, and bipartite graph checking.

## Assumptions
- All edges are considered directed because the provided adjacency matrix does not distinguish between undirected edges with weight -k and two directed edges with weights -k in opposite directions. Undirected edges can be treated as a special case of directed edges.
- A weight of 0 indicates the absence of an edge between two vertices (usually represented by infinity in other implementations).

## Usage

1. Create an instance of the `Graph` class, either using the default constructor or by providing an adjacency matrix.
2. use the various operators on the `Graph` instances, including: Binary Operators, Compound Assignment Operators, Increment/Decrement Operators, Comparison Operators. 
3. Even after the change in the adjacency matrix you can use the various methods provided by the `Algorithms` class to perform graph operations, such as checking connectivity, finding shortest paths, detecting cycles, and verifying if the graph is bipartite.

## Method Implementations- Graph

**Unary Operators:**

- operator+: Returns a copy of the graph (no changes).
- operator-: Returns a graph with all edge weights negated.

**Binary Operators:**

- operator+(Graph& other): Adds two graphs.
- operator-(Graph& other): Subtracts one graph from another.
- operator*(Graph& other): Multiplies two graphs using matrix multiplication. The diagonal will remain 0.

**Compound Assignment Operators:**

- operator+=(Graph& other): Adds another graph to the current graph.
- operator-=(Graph& other): Subtracts another graph from the current graph.
- operator*=(int scalar): Multiplies the graph's edges by a scalar.
- operator/=(int scalar): Divides the graph's edges by a scalar (throws an exception if the scalar is zero).

**Increment/Decrement Operators:**

- operator++: Increments all edge weights by 1. (pre-increment)
- operator--: Decrements all edge weights by 1. (pre-decrement)
- operator++(int): Increments all edge weights by 1. (post-increment)
- operator--(int): Decrements all edge weights by 1. (post-decrement)

**Comparison Operators:**

- operator==(Graph& other) const: Checks if two graphs are equal.
- operator!=(Graph& other) const: Checks if two graphs are not equal.
- operator<(Graph& other) const: Checks if the current graph is less than another graph, based on the following rules:
  - check if the other graph is contained directly in the original graph.
  - If neither graph is exactly contained in the other and the graphs are not equal then other graph is greater than original graph,
    - If the number of edges in other graph is greater than the number of edges in original graph.
    - If nevertheless the number of edges is the same, then the graph other is larger than the original graph if the representative matrix of other graph has a higher order of magnitude than original graph.
- operator>(Graph& other) const: Checks if the current graph is greater than another graph, based on the same rules, but in reverse:
 - check if the original graph is contained directly in the other graph.
  - If neither graph is exactly contained in the other and the graphs are not equal then original graph is greater than other graph,
    - If the number of edges in original graph is greater than the number of edges in other graph.
    - If nevertheless the number of edges is the same, then the original graph is larger than the other graph if the representative matrix of original graph has a higher order of magnitude than other graph.
- operator<=(Graph& other) const: Checks if the current graph is less than or equal to another graph.
- operator>=(Graph& other) const: Checks if the current graph is greater than or equal to another graph.

**Output Operator:**

- operator<<(ostream& os, Graph& graph): By using this operator, you can display the adjacency matrix representation of a graph.

 ## Method Implementations- Algorithms
 
- Bellman-Ford Algorithm: This function finds the shortest paths from a single source vertex to all other vertices in a weighted graph and handles negative edge weights and detects negative cycles.
- isConnected: This function checks if the graph is strongly connected.
- hasNegativeCycle: This function determines whether the graph contains a negative cycle. 
- ShortestPath: This function finds the shortest path between two vertices in a graph.
- isContainsCycle: This function checks if the graph contains a cycle.
- isBipartite: This function determines if the graph is bipartite.

## Code Structure
- Graph.hpp: Declaration of the Graph class, which represents a graph using an adjacency matrix.
- Graph.cpp: Implementation of the Graph class methods.
- Algorithms.hpp: Declaration of the Algorithms class, which provides various graph algorithms.
- Algorithms.cpp: Implementation of the graph algorithms in the Algorithms class.

## Testing
- The project includes a set of test cases (Test.cpp) to verify the correctness of the implemented algorithms. Run the test suite after building the project to ensure that the algorithms function as expected.


## Known Limitations
- The values in the diagonal must be 0.
- The graph must have a square matrix
