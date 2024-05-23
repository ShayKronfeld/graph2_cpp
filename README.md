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

- operator++: Increments all edge weights by 1 (except the diagonal).
- operator--: Decrements all edge weights by 1.

**Comparison Operators:**

- operator==(Graph& other) const: Checks if two graphs are equal.
- operator!=(Graph& other) const: Checks if two graphs are not equal.
- operator<(Graph& other) const: Checks if the current graph is less than another graph, based on the following rules:
  - If the graphs have the same number of vertices, check if both graphs have the same edges.
  - If they do, compare the weights of the edges. The graph with smaller edge weights is considered smaller.
  - If not, the graph with fewer edges is considered smaller.
  - If the graphs have different numbers of vertices, the graph with fewer vertices is considered smaller.
- operator>(Graph& other) const: Checks if the current graph is greater than another graph, based on the same rules, but in reverse:
  - If the graphs have the same number of vertices, check if both graphs have the same edges.
  - If they do, compare the weights of the edges. The graph with larger edge weights is considered greater.
  - If not, the graph with more edges is considered greater.
  - If the graphs have different numbers of vertices, the graph with more vertices is considered greater.
- operator<=(Graph& other) const: Checks if the current graph is less than or equal to another graph.
- operator>=(Graph& other) const: Checks if the current graph is greater than or equal to another graph.

**Output Operator:**

- operator<<(ostream& os, Graph& graph): By using this operator, you can display the adjacency matrix representation of a graph.

 ## Method Implementations- Algorithms
 
- Bellman-Ford Algorithm: Finds the shortest paths from a single source vertex to all other vertices in a weighted graph. Handles negative edge weights and detects negative cycles.
- Depth-First Search (DFS): Traverses a graph depth-first, visiting all reachable vertices from a given source vertex.
- Connected Components Detection: Determines if a graph is connected by checking if all vertices are reachable from each other.
- Negative Cycle Detection: Detects the presence of negative cycles in a graph.
- Shortest Path Finding: Finds the shortest path between two vertices in a graph.
- Bipartite Graph Detection: Determines if a given graph is bipartite or not.


## Code Structure
- Graph.hpp: Declaration of the Graph class, which represents a graph using an adjacency matrix.
- Graph.cpp: Implementation of the Graph class methods.
- Algorithms.hpp: Declaration of the Algorithms class, which provides various graph algorithms.
- Algorithms.cpp: Implementation of the graph algorithms in the Algorithms class.

## Testing
- The project includes a set of test cases (Test.cpp) to verify the correctness of the implemented algorithms. Run the test suite after building the project to ensure that the algorithms function as expected.


  ## Known Limitations
- The values in the diagonal must be 0. 
