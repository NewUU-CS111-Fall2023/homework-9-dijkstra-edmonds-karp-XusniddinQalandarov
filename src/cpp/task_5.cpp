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

class Problem5 {
public:
    int findCheapestPrice(int n, std::vector<std::vector<int>>& flights, int src, int dst, int k) {
        std::unordered_map<int, std::vector<std::pair<int, int>>> graph;

        // Create an adjacency list to represent the graph
        for (const auto& flight : flights) {
            graph[flight[0]].emplace_back(flight[1], flight[2]);
        }

        // Use Dijkstra's algorithm to find the cheapest price
        std::priority_queue<std::tuple<int, int, int>,
                            std::vector<std::tuple<int, int, int>>,
                            std::greater<std::tuple<int, int, int>>> pq;

        pq.push({0, src, 0}); // {cost, current city, stops made so far}

        while (!pq.empty()) {
            auto [cost, current, stops] = pq.top();
            pq.pop();

            if (current == dst) {
                return cost;
            }

            if (stops <= k) {
                for (const auto& neighbor : graph[current]) {
                    int nextCity = neighbor.first;
                    int nextCost = cost + neighbor.second;
                    pq.push({nextCost, nextCity, stops + 1});
                }
            }
        }

        return -1; // No valid route found
    }
};

int main() {
    Problem5 problem;

    // Example usage
    int n = 3;
    std::vector<std::vector<int>> flights = {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}};
    int src = 0;
    int dst = 2;
    int k = 1;

    int result = problem.findCheapestPrice(n, flights, src, dst, k);
    std::cout << "Cheapest price from src to dst: " << result << std::endl;

    return 0;
}
