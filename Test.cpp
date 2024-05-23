/*
NAME: shay kronfeld
ID: 322234782
EMAIL: kronfeldshay@gmail.com
*/

#include <sstream>
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");
}
TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0->1->0");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0->1->0");

     vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {1, -1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "-1");

}
TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}. ");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "0"); 
}
TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));
}

TEST_CASE("Test hasNegativeCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0, 0, 3, 0}, 
        {0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 7}, 
        {0, 0, 0, 0, 5}, 
        {0, 0, 0, 0, 0}}; 
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::hasNegativeCycle(g) == false);

    vector<vector<int>> graph2 = {
        {0, -1, 0, 7},
        {-1, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 1, 1, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::hasNegativeCycle(g) == true);

    vector<vector<int>> graph3 = {
        {0, 0, 0, 5, 0},
        {0, 0, 0, 6, 0},
        {0, 0, 0, 1, 0},
        {0, 7, 0, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::hasNegativeCycle(g) == false); 

    vector<vector<int>> graph4 = {
        {0, 0, 0, -5, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {-5, 7, 0, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::hasNegativeCycle(g) == true); 
}

TEST_CASE("Test all the checks in the graph"){

        ariel::Graph g;
 vector<vector<int>> graph = {
        {0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true); 
    CHECK(ariel::Algorithms::hasNegativeCycle(g) == false); 
    CHECK(ariel::Algorithms::isBipartite(g) == "0"); 
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0->3->1->0"); 
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "0->3->1"); 
}

TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};

    string expectedOutput = "0\t2\t1\t\n2\t0\t3\t\n1\t3\t0\t\n";
    stringstream ss;
    ss << g3;
    CHECK_EQ(ss.str(), expectedOutput);
}

TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};

    string expectedOutput = "0\t0\t2\t\n1\t0\t1\t\n1\t0\t0\t\n";
    stringstream ss;
    ss << g4;
    CHECK_EQ(ss.str(), expectedOutput);
}

TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1},
        {3, 0, 0, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);

    // there is numbers in the diagonal
    ariel::Graph g7;
    vector<vector<int>> graph4 = {
        {1, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    CHECK_THROWS(g7.loadGraph(graph4));
}

TEST_CASE("check ex1+ex2")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, -1, 1, 1},
        {-1, 0, -1, 1},
        {-1, 1, 0, -1},
        {-1, -1, -1, 0}};

    g.loadGraph(graph);

    ariel::Graph unary = ++g;

    string expectedOutputt = "0\t0\t2\t2\t\n0\t0\t0\t2\t\n0\t2\t0\t0\t\n0\t0\t0\t0\t\n";
    stringstream sss;
    sss << unary;
    CHECK_EQ(sss.str(), expectedOutputt);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 0, 1, 1},
        {0, 0, 0, 1},
        {0, 1, 0, 0},
        {0, 0, 0, 0}};

    g2.loadGraph(graph2);

    ariel::Graph add= unary+graph2;

    CHECK(ariel::Algorithms::isBipartite(add) == "The graph is bipartite: A={0, 1}, B={2, 3}. ");
    CHECK(ariel::Algorithms::hasNegativeCycle(add) == 0);

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, -3, 0},
        {0, 0, 2},
        {0, 1, 0}};

    g3.loadGraph(graph3);

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 1, 0},
        {-2, 0, 4},
        {0, 0, 0}};

    g4.loadGraph(graph4);

    ariel::Graph sub= g3 - g4;

    string expectedOutput = "0\t-4\t0\t\n2\t0\t-2\t\n0\t1\t0\t\n";
    stringstream ss;
    ss << sub;
    CHECK_EQ(ss.str(), expectedOutput);
    CHECK(ariel::Algorithms::hasNegativeCycle(sub) == 1);
    CHECK(ariel::Algorithms::isConnected(sub) == true);
    CHECK(ariel::Algorithms::isContainsCycle(sub) == "0->1->0");
    CHECK(ariel::Algorithms::shortestPath(sub, 0, 2) == "-1");

    for (int i=0; i<4; i++){
            ++sub;
    }


    string expectedOutput2 = "0\t0\t4\t\n6\t0\t2\t\n4\t5\t0\t\n";
    stringstream ss2;
    ss2 << sub;
    CHECK_EQ(ss2.str(), expectedOutput2);
    CHECK(ariel::Algorithms::shortestPath(sub, 0, 2) == "0->2");

    // ariel::Graph originalGraph = g++;
    // originalGraph.loadGraph(g++);

    // string expectedOutput3 = "5\t1\t5\t\n7\t5\t3\t\n5\t6\t5\t\n";
    // stringstream ss3;
    // ss3 << originalGraph;
    // CHECK_EQ(ss3.str(), expectedOutput3);
}


TEST_CASE("check boolean operators"){
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g.loadGraph(graph);

    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 3, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 5, 0}};
    g1.loadGraph(graph1);

   ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g2.loadGraph(graph2);

    bool equals1= g1==g;
    bool notEquals1= g1!=g;

    bool equals2= g2==g;
    bool notEquals2= g2!=g;

    CHECK(equals1 == false);
    CHECK(notEquals1 == true);

    CHECK(equals2 == true);
    CHECK(notEquals2 == false);
    
    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1},
        {1, 0}};
    g3.loadGraph(graph3);

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g4.loadGraph(graph4);

    ariel::Graph g5;
    vector<vector<int>> graph5 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g5.loadGraph(graph5);

    bool op1 = g3 < g4;
    bool op2 = g3 > g4;
    bool op3 = g5 <= g5;
    bool op4 = g5 >= g5;
    bool op5 = g4 <= g5;
    bool op6 = g3 <= g2;

    CHECK(op1 == true);
    CHECK(op2 == false);
    CHECK(op3 == true);
    CHECK(op4 == true);
    CHECK(op5 == false);
    CHECK(op6 == true);
}
