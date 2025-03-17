#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int graph_size = G.size();
    vector<int> distance(graph_size, numeric_limits<int>::max());
    vector<bool> visited_nodes(graph_size, false);
    previous.assign(graph_size, -1);
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    distance[source] = 0;
    pq.push({0, source});
    
    while (!pq.empty()) {
        auto [current_distance, current_vertex] = pq.top();
        pq.pop();

        if (visited_nodes[current_vertex]) continue;
        visited_nodes[current_vertex] = true;

        for (const Edge &edge : G[current_vertex]) {
            int adjacent_vertex = edge.dst;
            int edge_weight = edge.weight;

            if (!visited_nodes[adjacent_vertex] && distance[current_vertex] + edge_weight < distance[adjacent_vertex]) {
                distance[adjacent_vertex] = distance[current_vertex] + edge_weight;
                previous[adjacent_vertex] = current_vertex;
                pq.push({distance[adjacent_vertex], adjacent_vertex});
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {

}

void print_path(const vector<int>& v, int total) {
    
}