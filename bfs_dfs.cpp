#include <iostream> 
#include <fstream> 
#include <climits> 
  
using namespace std;
  
class Queue { 
    int *A; 
    int s, front, rear; 
  
  public: 
     Queue(int size = 100) { 
         s = size; 
         A = new int[s]; 
         front = rear = -1; 
     } 
  
     ~Queue() { delete[] A; }  // Destructor to free memory 
  
     bool isFull() { return rear == s - 1; } 
     bool isEmpty() { return front == -1; } 
  
     void enQueue(int key) { 
         if (isFull()) { 
             cout << "Queue Overflow! Cannot insert " << key << endl; 
             return; 
         } 

         if (isEmpty()) front = 0; 
         A[++rear] = key; 
     } 
  
     int deQueue() { 
         if (isEmpty()) return INT_MIN; 
         int e = A[front]; 
         if (front == rear)  // If only one element was in queue 
             front = rear = -1; 
         else 
             front++; 
         return e; 
     } 
 }; 
  
 class Stack { 
     int *A; 
     int s, top; 
  
 public: 
     Stack(int size = 100) { 
         s = size; 
         A = new int[s]; 
         top = -1; 
     } 
  
     ~Stack() { delete[] A; }  // Destructor to free memory 
  
     bool isFull() { return top == s - 1; } 
     bool isEmpty() { return top == -1; } 
  
     void push(int key) { 
         if (isFull()) { 
             cout << "Stack Overflow! Cannot push " << key << endl; 
             return; 
         } 
         A[++top] = key; 
     } 
  
     void pop() { 
         if (isEmpty()) return; 
         top--; 
     } 
  
     int peek() { 
         if (!isEmpty()) return A[top]; 
         return INT_MIN; 
     } 
 }; 
  
 class Graph { 
     int **A; 
     int v; 
  
 public: 
     Graph(string filename) { 
         fstream f(filename, ios::in); 
         if (!f) { 
             cout << "Error: File not found!" << endl; 
             exit(1); 
         } 
  
         f >> v; 
         cout << "Number of vertices = " << v << endl; 
  
         A = new int *[v]; 
         for (int i = 0; i < v; i++) { 
             A[i] = new int[v]; 
             for (int j = 0; j < v; j++) 
                 f >> A[i][j]; 
         } 
         f.close(); 
     } 
  
     ~Graph() {  // Destructor to free memory 
         for (int i = 0; i < v; i++) delete[] A[i]; 
         delete[] A; 
     } 
  
     void Display() { 
         cout << "\nAdjacency Matrix:\n"; 
         for (int i = 0; i < v; i++) { 
             for (int j = 0; j < v; j++) 
                 cout << A[i][j] << "\t"; 
             cout << endl; 
         } 
     } 
  
     void BFS(int sv) { 
         Queue Q; 
         int *visited = new int[v](); 
  
         Q.enQueue(sv); 
         visited[sv] = 1; 
  
         cout << "\nBFS Traversal: "; 
         while (!Q.isEmpty()) { 
             int x = Q.deQueue(); 
             cout << x << "\t"; 
  
             for (int j = 0; j < v; j++) { 
                 if (A[x][j] && !visited[j]) { 
                     Q.enQueue(j); 
                     visited[j] = 1; 
                 } 
             } 
         } 
         cout << endl; 
         delete[] visited; 
     } 
  
     void DFS(int sv) { 
         Stack st; 
         int *visited = new int[v](); 
  
         st.push(sv); 
         visited[sv] = 1; 
         cout << "\nDFS Traversal: " << sv << "\t"; 
  
         while (!st.isEmpty()) { 
             int x = st.peek(); 
             bool found = false; 
  
             for (int j = 0; j < v; j++) { 
                 if (A[x][j] != 0 && !visited[j]) { 
                     cout << j << "\t"; 
                     st.push(j); 
                     visited[j] = 1; 
                     found = true; 
                     break; 
                 } 
             } 
             if (!found) st.pop(); 
         } 
         cout << endl; 
         delete[] visited; 
     } 
  
     // Handles disconnected graphs by checking unvisited nodes 
     void DFS_Disconnected() { 
         int *visited = new int[v](); 
         cout << "\nDFS Traversal (for Disconnected Graphs): "; 
  
         for (int i = 0; i < v; i++) { 
             if (!visited[i]) { 
                 DFS(i); 
             } 
         } 
         cout << endl; 
         delete[] visited; 
     } 
 }; 
  
int main() { 
     Graph G("m1.txt"); 
  
     G.Display(); 
     G.DFS(0);   
     G.BFS(0);   
     G.DFS_Disconnected();   
  
     return 0; 
} 