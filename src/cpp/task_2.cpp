/*
 * Author:
 * Date:
 * Name:
 */

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

struct Edge {
    int target;
    int capacity;
    int flow;

    Edge(int tgt, int cap, int flw) : target(tgt), capacity(cap), flow(flw) {}
};

class Problem2 {
public:
    Problem2(int numNodes) : numNodes(numNodes), graph(numNodes) {}

    void addEdge(int from, int to, int capacity) {
        graph[from].emplace_back(to, capacity, 0);
        graph[to].emplace_back(from, 0, 0); // Adding reverse edge with 0 capacity
    }

    int maxFlow(int source, int sink) {
        int maxFlow = 0;

        while (true) {
            std::queue<int> q;
            q.push(source);

            std::vector<int> pred(numNodes, -1);

            while (!q.empty() && pred[sink] == -1) {
                int current = q.front();
                q.pop();

                for (const Edge& edge : graph[current]) {
                    if (pred[edge.target] == -1 && edge.target != source && edge.capacity > edge.flow) {
                        pred[edge.target] = current;
                        q.push(edge.target);
                    }
                }
            }

            if (pred[sink] == -1) {
                break;
            }

            int pathFlow = std::numeric_limits<int>::max();

            // Find minimum residual capacity along the path
            for (int v = sink; v != source; v = pred[v]) {
                for (const Edge& edge : graph[pred[v]]) {
                    if (edge.target == v) {
                        pathFlow = std::min(pathFlow, edge.capacity - edge.flow);
                        break;
                    }
                }
            }

            // Update residual capacities and add flow to the total
            for (int v = sink; v != source; v = pred[v]) {
                for (Edge& edge : graph[pred[v]]) {
                    if (edge.target == v) {
                        edge.flow += pathFlow;
                        break;
                    }
                }

                for (Edge& edge : graph[v]) {
                    if (edge.target == pred[v]) {
                        edge.flow -= pathFlow;
                        break;
                    }
                }
            }

            maxFlow += pathFlow;
        }

        return maxFlow;
    }

private:
    int numNodes;
    std::vector<std::vector<Edge>> graph;
};

int main() {
    // Example usage
    Problem2 problem(6);
    problem.addEdge(0, 1, 16);
    problem.addEdge(0, 2, 13);
    problem.addEdge(1, 2, 10);
    problem.addEdge(1, 3, 12);
    problem.addEdge(2, 1, 4);
    problem.addEdge(2, 4, 14);
    problem.addEdge(3, 2, 9);
    problem.addEdge(3, 5, 20);
    problem.addEdge(4, 3, 7);
    problem.addEdge(4, 5, 4);

    int maxFlow = problem.maxFlow(0, 5);
    std::cout << "Maximum Flow: " << maxFlow << std::endl;

    return 0;
}
