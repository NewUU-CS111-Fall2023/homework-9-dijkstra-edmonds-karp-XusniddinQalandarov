/*
 * Author:
 * Date:
 * Name:
 */

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

class Problem3 {
public:
    Problem3(const std::vector<std::string>& maze) : maze(maze) {
        rows = maze.size();
        cols = maze[0].size();
    }

    int findShortestPath() {
        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
        std::queue<std::pair<int, int>> q;

        // Find the starting point
        int startRow, startCol;
        findStart(startRow, startCol);

        q.push({startRow, startCol});
        visited[startRow][startCol] = true;

        int steps = 0;

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                int row = q.front().first;
                int col = q.front().second;
                q.pop();

                if (maze[row][col] == 'E') {
                    return steps;
                }

                // Explore neighbors (up, down, left, right)
                exploreNeighbor(row - 1, col, q, visited);
                exploreNeighbor(row + 1, col, q, visited);
                exploreNeighbor(row, col - 1, q, visited);
                exploreNeighbor(row, col + 1, q, visited);
            }

            steps++; // Increment steps after processing each level of the BFS
        }

        // If we reach here, there is no path from 'S' to 'E'
        return -1;
    }

private:
    const std::vector<std::string>& maze;
    int rows;
    int cols;

    void findStart(int& startRow, int& startCol) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (maze[i][j] == 'S') {
                    startRow = i;
                    startCol = j;
                    return;
                }
            }
        }
    }

    void exploreNeighbor(int row, int col, std::queue<std::pair<int, int>>& q, std::vector<std::vector<bool>>& visited) {
        if (row >= 0 && row < rows && col >= 0 && col < cols && maze[row][col] != '#' && !visited[row][col]) {
            q.push({row, col});
            visited[row][col] = true;
        }
    }
};

int main() {
    std::vector<std::string> maze = {
        "S..#...",
        "...#...",
        "###....",
        "...#...",
        "...#..E"
    };

    Problem3 problem(maze);
    int shortestPath = problem.findShortestPath();

    if (shortestPath != -1) {
        std::cout << "Shortest path from S to E: " << shortestPath << " steps" << std::endl;
    } else {
        std::cout << "No path from S to E exists." << std::endl;
    }

    return 0;
}
