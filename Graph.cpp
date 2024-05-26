/*
NAME: shay kronfeld
ID: 322234782
EMAIL: kronfeldshay@gmail.com
*/

#include <iostream>
#include <vector>
#include "Graph.hpp"

using namespace std;

namespace ariel {
    // Empty constructor
    Graph::Graph() : numberOfVertices(0), numberOfEdge(0), isWeighted(false) {}

    // Constructor
    Graph:: Graph(const vector<vector<int>>& matrix) {
        loadGraph(matrix);
    }


    // Load graph from an adjacency matrix
    void Graph::loadGraph(const vector<vector<int>>& matrix) {
    numberOfVertices=0;
    numberOfEdge=0;
    isWeighted=false;


    // If the matrices are not the same size
    for (const auto& row : matrix) { 
        if (row.size() != matrix.size()) {
            throw invalid_argument("Invalid graph: The graph is not a square matrix");
        }
    }

    for (int i=0; i<matrix.size(); i++){
        if (matrix[i][i]!=0){
            throw invalid_argument("Invalid graph: The diagonal has a value other than 0");
        }
    }
    
    adjacencyMatrix = matrix;
    numberOfVertices= matrix.size();
    
        for (size_t i=0; i< matrix.size(); i++){
                for (size_t j=0; j< matrix.size(); j++){
                
                    if (matrix[i][j]!=0) // check if there is edge
                        numberOfEdge++; 

                    if (matrix[i][j]!=0 && matrix[i][j]!=1) // check if the graph is weighted
                        isWeighted= true;

                }
        }

    }

    // Print the graph
    void Graph::printGraph() const {
        cout << "Graph with " << numberOfVertices << " vertices and " << numberOfEdge << " edges:" << endl;
    }

    // Get the number of vertices in the graph
    size_t Graph::getNumberOfVertices() const {
            return numberOfVertices;
        }

    // Get the number of edges in the graph
    size_t Graph::getNumberOfEdge() const {
            return numberOfEdge;
        }

    //  Get cell in the adjacency matrix
    int Graph::getCellInAdjacencyMatrix(size_t i, size_t j) const {
        return adjacencyMatrix[i][j];
    }

    // Function to get the adjacency matrix
    const vector<vector<int>>& Graph::getAdjMatrix() const {
        return adjacencyMatrix;
    }

     vector<size_t> Graph::getNeighbors(size_t vertex) const {
            vector<size_t> neighbors;
            if (vertex < 0 || vertex >= adjacencyMatrix.size()) {
                return neighbors; // Return empty vector if vertex is out of bounds
            }
            for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
                if (adjacencyMatrix[vertex][i] != 0) {
                    neighbors.push_back(i); // Add neighbor to the vector if there is an edge
                }
            }
            return neighbors;
        }


        
    Graph Graph::operator+(const Graph& other) const {
        // Check if the dimensions are same
        if (numberOfVertices != other.numberOfVertices) {
            throw invalid_argument("Graph dimensions are not compatible for addition.");
        }

        vector<vector<int>> resultMatrix(numberOfVertices, vector<int>(numberOfVertices, 0));

        // add all the cells
        for (size_t i = 0; i < numberOfVertices; ++i) {
            for (size_t j = 0; j < numberOfVertices; ++j) {
                resultMatrix[i][j] = adjacencyMatrix[i][j] + other.adjacencyMatrix[i][j];
            }
        }

        return Graph(resultMatrix);
    }

    Graph Graph::operator-(const Graph& other) const {
        // Check if the dimensions are same
        if (numberOfVertices != other.numberOfVertices) {
            throw invalid_argument("Graph dimensions are not compatible for subtraction.");
        }

        vector<vector<int>> resultMatrix(numberOfVertices, vector<int>(numberOfVertices, 0));

        // subtract add all the cells
        for (size_t i = 0; i < numberOfVertices; ++i) {
            for (size_t j = 0; j < numberOfVertices; ++j) {
                resultMatrix[i][j] = adjacencyMatrix[i][j] - other.adjacencyMatrix[i][j];
            }
        }

        return Graph(resultMatrix);
    }

    Graph& Graph::operator+=(const Graph& other) {
        // Check if the dimensions are same
        if (numberOfVertices != other.numberOfVertices) {
            throw invalid_argument("Graph dimensions are not compatible for addition.");
        }

        // add other to the original matrix
        for (size_t i = 0; i < numberOfVertices; ++i) {
            for (size_t j = 0; j < numberOfVertices; ++j) {
                adjacencyMatrix[i][j] += other.adjacencyMatrix[i][j];
            }
        }

        return *this; // Return reference to the modified object
    }

    Graph& Graph::operator-=(const Graph& other) {
        // Check if the dimensions are same
        if (numberOfVertices != other.numberOfVertices) {
            throw invalid_argument("Graph dimensions are not compatible for addition.");
        }

        // add other to the original matrix
        for (size_t i = 0; i < numberOfVertices; ++i) {
            for (size_t j = 0; j < numberOfVertices; ++j) {
                adjacencyMatrix[i][j] -= other.adjacencyMatrix[i][j];
            }
        }

        return *this; // Return reference to the modified object
    }

    //unary
    Graph Graph::operator+() const {
        // No changes required for unary plus, return a copy of the original graph
        return *this;
    }

    // Unary minus operator
    Graph Graph::operator-() const {
        vector<vector<int>> negatedMatrix(numberOfVertices, vector<int>(numberOfVertices, 0));

        // Negate all elements of the adjacency matrix
        for (size_t i = 0; i < numberOfVertices; ++i) {
            for (size_t j = 0; j < numberOfVertices; ++j) {
                negatedMatrix[i][j] = -adjacencyMatrix[i][j];
            }
        }

        return Graph(negatedMatrix);
    }

    // Comparison operators
    bool Graph::operator==(const Graph& other) const {
        if (numberOfVertices != other.numberOfVertices || numberOfEdge != other.numberOfEdge) {
            return false; // Graphs have different number of vertices or edges, they are not equal
        }

        // Check if the adjacency matrices are equal
        for (size_t i = 0; i < numberOfVertices; ++i) {
            for (size_t j = 0; j < numberOfVertices; ++j) {
                if (adjacencyMatrix[i][j] != other.adjacencyMatrix[i][j]) {
                    return false; // Found a mismatched edge weight, graphs are not equal
                }
            }
        }

        // if g1<g2 or g2<g1 they not equals
        if (this->getAdjMatrix() < other.getAdjMatrix() || other.getAdjMatrix() < this->getAdjMatrix())
            return false;

        return true; // Graphs are equal
    }


    bool Graph::operator!=(const Graph& other) const {
        if (*this==other)
            return false; // Use the operator== to implement this function
        return true;
    }

    //check if the original graph < other graph
    bool Graph::operator<(const Graph& other) const {
    
        // if the matrixs not in the same size
        if (numberOfVertices != other.numberOfVertices){

            // if the new graph (other) has more edges
            if (numberOfEdge < other.numberOfEdge) {
                return true; // original graph has less or equal edges.
            }

            // if the new graph (other) has more vertices
            if (numberOfVertices < other.numberOfVertices){
                return true; // original graph has less or equal vertices.
            }
        } else {
            for (int i=0; i<numberOfVertices; i++){
                for (int j=0; j<numberOfVertices; j++){
                    if (adjacencyMatrix[i][j] != 0 && other.adjacencyMatrix[i][j] == 0) {
                        return false;
                    }
                }
            }
            return true; 
        }

        return false; 

    }

    //check if the original graph > other graph
    bool Graph::operator>(const Graph& other) const {
       // if the matrixs not in the same size
        if (numberOfVertices != other.numberOfVertices){

            // if the new graph (other) has more edges
            if (numberOfEdge > other.numberOfEdge) {
                return true; // original graph has less or equal edges.
            }

            // if the new graph (other) has more vertices
            if (numberOfVertices > other.numberOfVertices){
                return true; // original graph has less or equal vertices.
            }
        } else {
            for (int i=0; i<numberOfVertices; i++){
                for (int j=0; j<numberOfVertices; j++){
                    if (other.adjacencyMatrix[i][j] != 0 && adjacencyMatrix[i][j] == 0) {
                        return false;
                    }
                }
            }
            return true; 
        }

        return false; 
    
    }

    // if the original graph <= other graph
    bool Graph::operator<=(const Graph& other) const {
        if (*this < other || *this == other)
            return true;
        return false;
    }

    // if the original graph >= other graph
    bool Graph::operator>=(const Graph& other) const {
        if (*this > other || *this == other)
            return true;
        return false;  
    }

    // ++g - increase all edge weights by 1
    Graph& Graph::operator++() {
        for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) {
                if (adjacencyMatrix[i][j] != 0) {
                    adjacencyMatrix[i][j]++;
                }
            }
        }
        return *this; // return the value before the increase
    }


    // --g - decrease all edge weights by 1
    Graph& Graph::operator--() {
         for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) {
                if (adjacencyMatrix[i][j] != 0) {
                    adjacencyMatrix[i][j]--;
                }
            }
        }
        return *this; // return the value after the decrease
    }


    // g++ - increase all edge weights by 1 (post-decrement)
    Graph Graph::operator++(int) {
        Graph temp (*this);
        ++(*this);
        return temp; // return the value before the increase
    }


    // g-- - decrease all edge weights by 1 (post-decrement)
    Graph Graph::operator--(int) {
        Graph temp (*this);
        --(*this);
        return temp; // return the value before the decrease
    }

    
    // multy graph in scalar
   void Graph::operator*=(int scalar) {
        // Multiply each element of the adjacency matrix by the scalar
        for (size_t i = 0; i < numberOfVertices; ++i) {
            for (size_t j = 0; j < numberOfVertices; ++j) {
                adjacencyMatrix[i][j] *= scalar;
            }
        }
    }


    Graph& Graph::operator/=(int scalar) {
        // Check if the scalar is not zero
        if (scalar == 0) {
            throw invalid_argument("Cannot divide by zero.");
        }

        // Divide each element of the adjacency matrix by the scalar
        for (size_t i = 0; i < numberOfVertices; ++i) {
            for (size_t j = 0; j < numberOfVertices; ++j) {
                adjacencyMatrix[i][j] /= scalar;
            }
        }

        // Return reference to the modified object
        return *this;
    }



    // Graph multiplication
    Graph Graph::operator*(const Graph& other) const {
        if (numberOfVertices != other.numberOfVertices) {
            throw invalid_argument("Graph dimensions are not compatible for multiplication.");
        }

        vector<vector<int>> resultMatrix(numberOfVertices, vector<int>(numberOfVertices, 0));
        for (size_t i = 0; i < numberOfVertices; ++i) {
            for (size_t j = 0; j < numberOfVertices; ++j) {
                for (size_t k = 0; k < numberOfVertices; ++k) {
                    resultMatrix[i][j] += adjacencyMatrix[i][k] * other.adjacencyMatrix[k][j]; // Matrix multiplication
                }
            }
        }

        for (int i=0; i<numberOfVertices; i++){ // if the multiplication return number in the diagonal
            resultMatrix[i][i]=0;
        }

        return Graph(resultMatrix); // Return the resulting graph
    }

   // Print the adjacency matrix of the graph
    ostream& operator<<(ostream& os, const Graph& graph) {
        const vector<vector<int>>& adjacencyMatrix = graph.getAdjMatrix();
        for (const auto& row : adjacencyMatrix) {
            for (int weight : row) {
                os << weight << "\t"; // Print edge weights
            }
            os << "\n"; // Correctly add newline character
        }
        return os; // Return the output stream
    }




}


