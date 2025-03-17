#include "dijkstras.h"
using namespace std;

int main() {
    Graph G;
    file_to_graph("./src/medium.txt", G);

    int src = 3
    vector<int> prev;
    vector<int> dijkstra_path = dijkstra_shortest_path(G, src, prev);
    int destination = 1;
    vector<int> short_path = extract_shortest_path(dijkstra_path, prev, destination);
    print_path(short_path, dijkstra_path[destination]);

    return 0;
}