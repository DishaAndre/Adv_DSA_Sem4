#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
public:
    int **A;
    int size;

    Graph(int z) {
        size = z;
        A = new int*[size];
        for (int i = 0; i < size; i++) {
            A[i] = new int[size];
            for (int j = 0; j < size; j++) {
                A[i][j] = 0;
            }
        }
    }

    void AddEdge(int i, int j, int w = 1) {
        if (i >= size || j >= size || i < 0 || j < 0) {
            cout << "Invalid edge!\n";
            return;
        }
        A[i][j] = w;
        A[j][i] = w;  
        cout << "Edge added successfully!\n";
    }

    void Display() {
        cout << "Graph (Adjacency Matrix):\n";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << A[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool DFSUtil(int current, int goal, vector<bool>& visited, vector<int>& parent) {
        visited[current] = true;
        if (current == goal)
            return true;
        
        for (int i = 0; i < size; i++) {
            if (A[current][i] != 0 && !visited[i]) {
                parent[i] = current;
                if (DFSUtil(i, goal, visited, parent))
                    return true;
            }
        }
        return false;
    }

    void DFS(int start, int goal) {
        vector<bool> visited(size, false);
        vector<int> parent(size, -1);
        
        if (DFSUtil(start, goal, visited, parent)) {
            cout << "Path found using DFS: ";
            vector<int> path;
            int current = goal;
            while (current != -1) {
                path.push_back(current);
                current = parent[current];
            }
            for (int i = path.size() - 1; i >= 0; i--)
                cout << path[i] << " ";
            cout << endl;
        } else {
            cout << "No path found using DFS.\n";
        }
    }

    bool BFS(int start, int goal, vector<int>& parent) {
        vector<bool> visited(size, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        parent[start] = -1;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            if (current == goal)
                return true;

            for (int i = 0; i < size; i++) {
                if (A[current][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    parent[i] = current;
                    q.push(i);
                }
            }
        }
        return false;
    }

    void BFSPath(int start, int goal) {
        vector<int> parent(size, -1);
        if (BFS(start, goal, parent)) {
            cout << "Path found using BFS: ";
            vector<int> path;
            int current = goal;
            while (current != -1) {
                path.push_back(current);
                current = parent[current];
            }
            for (int i = path.size() - 1; i >= 0; i--)
                cout << path[i] << " ";
            cout << endl;
        } else {
            cout << "No path found using BFS.\n";
        }
    }
};

int main() {
    int nodes;
    cout << "Enter the number of nodes in the graph: ";
    cin >> nodes;

    Graph g(nodes);
    
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Edge\n";
        cout << "2. Display Graph\n";
        cout << "3. DFS Search\n";
        cout << "4. BFS Search\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            int u, v;
            cout << "Enter edge (u v): ";
            cin >> u >> v;
            g.AddEdge(u, v);
        } else if (choice == 2) {
            g.Display();
        } else if (choice == 3) {
            int start, goal;
            cout << "Enter start and goal node for DFS: ";
            cin >> start >> goal;
            g.DFS(start, goal);
        } else if (choice == 4) {
            int start, goal;
            cout << "Enter start and goal node for BFS: ";
            cin >> start >> goal;
            g.BFSPath(start, goal);
        } else if (choice == 5) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}