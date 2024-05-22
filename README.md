**Overview**
This library provides an implementation of a Graph class in C++. The graph is represented using an adjacency matrix, and supports both weighted and unweighted graphs. Various operations are supported, including addition, subtraction, comparison, and scalar multiplication/division of graphs.

**Classes**
**Graph**
The Graph class provides a comprehensive set of functionalities to work with graphs. Below are the details of its members and methods.

**Constructors**
Graph(): Default constructor that initializes an empty graph.
Graph(const std::vector<std::vector<int>>& matrix): Constructs a graph from an adjacency matrix. The matrix must be a square matrix with zeroes on the diagonal.

**Methods**
void loadGraph(const std::vector<std::vector<int>>& matrix): Loads a graph from an adjacency matrix.
void printGraph(): Prints basic information about the graph (number of vertices and edges).
size_t getNumberOfVertices(): Returns the number of vertices in the graph.
size_t getNumberOfEdge(): Returns the number of edges in the graph.
int getCellInAdjacencyMatrix(size_t i, size_t j): Returns the weight of the edge between vertices i and j.
std::vector<size_t> getNeighbors(size_t vertex) const: Returns a list of neighbors for a given vertex.

**Operators**
Unary Operators:
Graph operator+() const: Returns a copy of the graph (no changes).
Graph operator-() const: Returns a graph with all edge weights negated.

Binary Operators:
Graph operator+(const Graph& other): Adds two graphs.
Graph operator-(const Graph& other): Subtracts one graph from another.
Graph operator*(const Graph& other): Multiplies two graphs using matrix multiplication.
Compound Assignment Operators:

Graph& operator+=(const Graph& other): Adds another graph to the current graph.
Graph& operator-=(const Graph& other): Subtracts another graph from the current graph.
void operator*=(int scalar): Multiplies the graph's edges by a scalar.
Graph& operator/=(int scalar): Divides the graph's edges by a scalar (throws an exception if the scalar is zero).
Increment/Decrement Operators:

Graph& operator++(): Increments all edge weights by 1 (except the diagonal).
Graph& operator--(): Decrements all edge weights by 1.
