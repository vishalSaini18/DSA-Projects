#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Define a triple type for convenience (destination, distance, fare)
typedef tuple<int, int, int> Triple;

// Function to find the shortest path using Dijkstra's algorithm
void dijkstra(const vector<vector<Triple>>& graph, int source) {
    int V = graph.size();
    vector<int> dist(V, INT_MAX);   // Distance array initialized to infinity
    vector<int> fare(V, INT_MAX);   // Fare array initialized to infinity
    priority_queue<Triple, vector<Triple>, greater<Triple>> pq; // Min-heap priority queue

    dist[source] = 0;
    fare[source] = 0;
    pq.push(make_tuple(0, 0, source)); // Push the source node with distance 0 and fare 0

    while (!pq.empty()) {
        int u = get<2>(pq.top());
        int current_distance = get<0>(pq.top());
        int current_fare = get<1>(pq.top());
        pq.pop();

        for (const Triple& neighbor : graph[u]) {
            int v = get<0>(neighbor);
            int weight = get<1>(neighbor);
            int fare_to_neighbor = get<2>(neighbor);

            if (current_distance + weight < dist[v]) {
                dist[v] = current_distance + weight;
                fare[v] = current_fare + fare_to_neighbor;
                pq.push(make_tuple(dist[v], fare[v], v));
            }
        }
    }

    // Print the shortest distances and fares from the source
    cout << "Stop\tDistance from Source\tFare from Source\n";
    for (int i = 0; i < V; ++i) {
        cout << i << "\t\t" << dist[i] << "\t\t\t" << fare[i] << "\n";
    }
}

int main() {
    // Number of stops in the network
    int V;
    cout << "Enter the number of stops: ";
    cin >> V;

    // Adjacency list representation of the graph (destination, distance, fare)
    vector<vector<Triple>> graph(V);

    // Number of routes in the network
    int E;
    cout << "Enter the number of routes: ";
    cin >> E;

    cout << "Enter the routes (source destination distance fare):\n";
    for (int i = 0; i < E; ++i) {
        int u, v, w, f;
        cin >> u >> v >> w >> f;
        graph[u].push_back(make_tuple(v, w, f));
        graph[v].push_back(make_tuple(u, w, f)); // If the graph is undirected
    }

    int source;
    cout << "Enter the source stop: ";
    cin >> source;

    // Find the shortest path from the source to all other stops
    dijkstra(graph, source);

    return 0;
}
