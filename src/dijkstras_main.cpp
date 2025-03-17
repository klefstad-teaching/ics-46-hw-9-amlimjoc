#include "dijkstras.h"

int main() {
    Graph G;
    file_to_graph("graph.txt", G); // Load graph from file

    int source = 0, destination = 4;
    vector<int> previous;
    
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    vector<int> shortestPath = extract_shortest_path(distances, previous, destination);

    print_path(shortestPath, distances[destination]);

    return 0;
}