#include<iostream>
#include<fstream>
#include<climits>
using namespace std;

struct edge{
    int s, e, w;
};

struct node{
    int s, e, w;
    node* next;
};

template<class T>
class heap{
    T *A;
    int n, s;
public:
    heap(int size = 100){
        n = size;
        A = new T[n];
        s = 0;
    }

    bool isEmpty(){
        return s == 0;
    }

    void heapifyup(int i){
        while(i > 0){
            int p = (i - 1) / 2;
            if(A[p].w > A[i].w){
                swap(A[p], A[i]);
                i = p;
            } else break;
        }
    }

    void insert(T val){
        A[s] = val;
        heapifyup(s);
        s++;
    }

    void heapifydown(int i){
        while(1){
            int l = 2*i+1, r = 2*i+2, min = i;
            if(l < s && A[l].w < A[min].w) min = l;
            if(r < s && A[r].w < A[min].w) min = r;
            if(min != i){
                swap(A[i], A[min]);
                i = min;
            } else break;
        }
    }

    T deleteh(){
        T temp = A[0];
        A[0] = A[s-1];
        s--;
        heapifydown(0);
        return temp;
    }
};

class Graph{
    node **A;
    string *vname;
    int v;

public:
    Graph(string mat, string names){
        fstream fin(mat);
        fin >> v;
        A = new node*[v];
        for(int i=0; i<v; i++) A[i] = NULL;

        int val;
        for(int i=0; i<v; i++){
            for(int j=0; j<v; j++){
                fin >> val;
                if(val){
                    node *temp = new node();
                    temp->s = i;
                    temp->e = j;
                    temp->w = val;
                    temp->next = A[i];
                    A[i] = temp;
                }
            }
        }

        fstream fin2(names);
        vname = new string[v];
        int dummy; 
        fin2 >> dummy;
        for(int i=0; i<v; i++) 
        fin2 >> vname[i];
    }

    void Dijkstra(int start){
        int *dist = new int[v];
        for(int i=0; i<v; i++) dist[i] = INT_MAX;

        dist[start] = 0;
        heap<edge> pq;
        pq.insert({start, start, 0});

        while(!pq.isEmpty()){
            edge curr = pq.deleteh();
            node *ptr = A[curr.e];
            while(ptr){
                if(dist[curr.e] + ptr->w < dist[ptr->e]){
                    dist[ptr->e] = dist[curr.e] + ptr->w;
                    pq.insert({curr.e, ptr->e, dist[ptr->e]});
                }
                ptr = ptr->next;
            }
        }

        for(int i=0; i<v; i++){
            if(i != start){
                cout << vname[start] << " -> " << vname[i] << " = " << dist[i] << endl;
            }
        }
    }
};

int main(){
    Graph g("matrix3.txt", "matrix2.txt");
    g.Dijkstra(0);  
    return 0;
}

