#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Graph {
private:
    int V;               // Number of vertices
    std::vector<list<int>> adjacencyList; // Array of linked lists

public:
    // Constructor
    Graph(int V) : V(V) {
        // Create a new array of linked lists of size V
        adjacencyList.resize(V);
    }

    // Function to add an edge to the graph
    void addEdge(int v, int w) {
        adjacencyList[v].push_back(w);
        // adjacencyList[w].push_back(v); // Uncomment this line for undirected graphs
    }

    // Function to print the adjacency list representation of the graph
    void printGraph() {
        for (int i = 0; i < V; ++i) {
            cout << "Adjacency list of vertex " << i << ": ";
            for (auto const &vertex : adjacencyList[i]) {
                cout << vertex << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    // Create a graph with 5 vertices
    Graph graph(5);

    // Add edges to the graph
    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    // Print the adjacency list representation of the graph
    graph.printGraph();

    return 0;
}
