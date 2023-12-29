/*
 * Author:
 * Date:
 * Name:
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

class Problem4 {
public:
    int networkDelayTime(std::vector<std::vector<int>>& times, int n, int k) {
        // Create an adjacency list to represent the graph
        std::unordered_map<int, std::vector<std::pair<int, int>>> graph;
        for (const auto& edge : times) {
            graph[edge[0]].emplace_back(edge[1], edge[2]);
        }

        // Use Dijkstra's algorithm to find the shortest path
        std::vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        pq.push({0, k});

        while (!pq.empty()) {
            int u = pq.top().second;
            int u_dist = pq.top().first;
            pq.pop();

            if (u_dist > dist[u]) {
                continue;
            }

            for (const auto& neighbor : graph[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                if (u_dist + weight < dist[v]) {
                    dist[v] = u_dist + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        // Find the maximum time to reach a node
        int maxTime = 0;
        for (int i = 1; i <= n; ++i) {
            if (dist[i] == INT_MAX) {
                return -1; // Not all nodes are reachable
            }
            maxTime = std::max(maxTime, dist[i]);
        }

        return maxTime;
    }
};

int main() {
    Problem4 problem;

    // Example usage
    std::vector<std::vector<int>> times = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    int n = 4;
    int k = 2;

    int result = problem.networkDelayTime(times, n, k);
    std::cout << "Minimum time to reach all nodes: " << result << std::endl;

    return 0;
}
