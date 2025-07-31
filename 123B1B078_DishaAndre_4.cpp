#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

class Graph {
    int adj[20][20];
    int v;
    string dept[20];

public:
    Graph(string filename) {
        fstream file(filename);
        if (!file) {
            cout << "file not found.\n";
            exit(1);
        }

        file >> v;

        for (int i = 0; i < v; i++) {
            file >> dept[i];
        }

        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                file >> adj[i][j];
            }
        }

        file.close();
    }

    void prims(int start) {
        int selected[20] = {0};
        selected[start] = 1;
        int count = 0;

        cout << "\nprim's mst:\n";
        while (count < v - 1) {
            int min = INT_MAX, a = -1, b = -1;
            for (int i = 0; i < v; i++) {
                if (selected[i]) {
                    for (int j = 0; j < v; j++) {
                        if (!selected[j] && adj[i][j] && adj[i][j] < min) {
                            min = adj[i][j];
                            a = i;
                            b = j;
                        }
                    }
                }
            }
            if (a != -1 && b != -1) {
                cout << dept[a] << " - " << dept[b] << "  dist: " << min << endl;
                selected[b] = 1;
                count++;
            }
        }
    }

    void kruskals() {
        int parent[20];
        for (int i = 0; i < v; i++)
            parent[i] = i;

        cout << "\nkruskal's mst:\n";
        int edges = 0;

        while (edges < v - 1) {
            int min = INT_MAX, u = -1, vtx = -1;
            for (int i = 0; i < v; i++) {
                for (int j = 0; j < v; j++) {
                    if (adj[i][j] && parent[i] != parent[j] && adj[i][j] < min) {
                        min = adj[i][j];
                        u = i;
                        vtx = j;
                    }
                }
            }

            if (u != -1 && vtx != -1) {
                cout << dept[u] << " - " << dept[vtx] << "  dist: " << min << endl;

                int oldp = parent[vtx];
                int newp = parent[u];
                for (int i = 0; i < v; i++) {
                    if (parent[i] == oldp)
                        parent[i] = newp;
                }
                edges++;
            }
        }
    }
};

int main() {
    Graph g("matrix1.txt");
    g.prims(0);     
    g.kruskals();   

    return 0;
}







