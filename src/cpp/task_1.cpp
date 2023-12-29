/*
 * Author:
 * Date:
 * Name:
 */
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

class Problem1 {
public:
    // Function to perform Dijkstra's algorithm
    void dijkstra(std::vector<std::vector<int>>& graph, int startNode) {
        int n = graph.size();

        // Initialize distance array with infinity
        std::vector<int> distance(n, std::numeric_limits<int>::max());

        // Mark the start node with distance 0
        distance[startNode] = 0;

        // Priority queue to store {distance, node} pairs
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        pq.push({0, startNode});

        // Dijkstra's algorithm
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (int v = 0; v < n; ++v) {
                if (graph[u][v] != 0 && distance[u] + graph[u][v] < distance[v]) {
                    // Relaxation step
                    distance[v] = distance[u] + graph[u][v];
                    pq.push({distance[v], v});
                }
            }
        }

        // Print the distances from the start node to all other nodes
        std::cout << "Shortest distances from node " << startNode << ":\n";
        for (int i = 0; i < n; ++i) {
            std::cout << "To node " << i << ": " << distance[i] << "\n";
        }
    }
};

int main() {
    // Example usage
    Problem1 problem;

    // Example graph represented as an adjacency matrix
    std::vector<std::vector<int>> graph = {
        {0, 2, 4, 0, 0},
        {0, 0, 1, 7, 0},
        {0, 0, 0, 0, 3},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0}
    };

    // Starting node for Dijkstra's algorithm
    int startNode = 0;

    // Perform Dijkstra's algorithm
    problem.dijkstra(graph, startNode);

    return 0;
}
