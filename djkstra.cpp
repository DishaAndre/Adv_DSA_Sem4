#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

class Graph {
    int v;            // Number of vertices
    int A[20][20];    // Adjacency matrix
    string city[20];  // City names

    public:
    
    Graph(string matrixFile, string nameFile) {
        ifstream fin(matrixFile);
        if (!fin) {
            cout << "Error opening matrix file!" << endl;
            exit(1);
        }

        fin >> v;
        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                fin >> A[i][j];
        fin.close();

        ifstream fin2(nameFile);
        if (!fin2) {
            cout << "Error opening name file!" << endl;
            exit(1);
        }

        int dummy;
        fin2 >> dummy;
        for (int i = 0; i < v; i++)
            fin2 >> city[i];
        fin2.close();
    }


    void dijkstra(int start) {
        int dist[20], visited[20];
        for (int i = 0; i < v; i++) {
            dist[i] = INT_MAX;
            visited[i] = 0;
        }

        dist[start] = 0;
        int count = 0;

        while (count < v - 1) {
            int u = -1, min = INT_MAX;
            for (int i = 0; i < v; i++) {
                if (!visited[i] && dist[i] < min) {
                    min = dist[i];
                    u = i;
                }
            }

            visited[u] = 1;

            for (int i = 0; i < v; i++) {
                if (A[u][i] && !visited[i] && dist[u] + A[u][i] < dist[i]) {
                    dist[i] = dist[u] + A[u][i];
                }
            }
            count++;
        }

        for (int i = 0; i < v; i++) {
            if (i != start) {
                cout << city[start] << " -> " << city[i] << " = " << dist[i] << endl;
            }
        }
    }
};

int main() {
    Graph g("matrix3.txt", "matrix2.txt");
    g.dijkstra(0); 
    return 0;
}

