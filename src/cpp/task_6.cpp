/*
 * Author:
 * Date:
 * Name:
 */

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>

class Problem6 {
public:
    int findShortestPath(int n, std::vector<std::vector<int>>& flights, int src, int dst, int k, int f) {
        std::vector<std::vector<std::pair<int, std::pair<int, int>>>> graph(n);

        // Create an adjacency list to represent the graph
        for (const auto& flight : flights) {
            graph[flight[0]].emplace_back(flight[1], std::make_pair(flight[2], flight[3]));
        }

        // Use Dijkstra's algorithm to find the shortest path
        std::priority_queue<std::tuple<int, int, int, int>,
                            std::vector<std::tuple<int, int, int, int>>,
                            std::greater<std::tuple<int, int, int, int>>> pq;

        pq.push({0, src, 0, f}); // {distance traveled, current city, stops made, remaining fuel}

        while (!pq.empty()) {
            auto [distance, current, stops, remainingFuel] = pq.top();
            pq.pop();

            if (current == dst) {
                return distance;
            }

            if (stops <= k) {
                for (const auto& neighbor : graph[current]) {
                    int nextCity = neighbor.first;
                    int nextDistance = neighbor.second.first;
                    int hasARS = neighbor.second.second;

                    if (remainingFuel >= nextDistance) {
                        int nextRemainingFuel = remainingFuel - nextDistance + hasARS * f;
                        pq.push({distance + nextDistance, nextCity, stops + 1, nextRemainingFuel});
                    }
                }
            }
        }

        return -1; // No valid route found
    }
};

int main() {
    Problem6 problem;

    // Example usage
    int n = 4;
    std::vector<std::vector<int>> flights = {{0, 1, 100, 0},
                                            {1, 2, 600, 1},
                                            {2, 0, 100, 1},
                                            {1, 3, 600, 0},
                                            {2, 3, 200, 0}};
    int src = 0;
    int dst = 3;
    int k = 2;
    int f = 600;

    int result = problem.findShortestPath(n, flights, src, dst, k, f);
    std::cout << "Shortest possible path from src to dst: " << result << std::endl;

    return 0;
}