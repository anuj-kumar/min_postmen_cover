#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <stack>
#include <queue>
#include <list>
#define SIZE 200
using namespace std;

class graph {
public:
    list<int> adj[SIZE], adj_c[SIZE];
    int numOfVertices, numOfEdges, label_source[SIZE], label_sink[SIZE], source, sink;

    graph() {
        numOfVertices = 0;
        memset(label_source, 0, sizeof (int) *SIZE);
        memset(label_sink, 0, sizeof (int) *SIZE);
        memset(adj, 0, sizeof (int) *SIZE);
        source = 0;
        sink = 0;
    }

    void read_input() {
        int i, j, m, n;
        //cin >> source >> sink;
        //cin >> numOfVertices >> numOfEdges;
        for (i = 0; i < numOfEdges; i++) {
            cin >> m >> n;
            adj[0].push_front(n);
            //adj[n].push_back(m);
            //adj_c[m].push_back(n);
            //adj_c[n].push_back(m);
        }
        for(i=0; i<numOfVertices; i++) {
			for (list<int>::iterator v = adj[i].begin(); v != adj[i].end(); ++v) {
				cout<<*v<<" ";
			}
			cout<<endl;
		}
	}

    /*void bfs(int start, char type) {
        queue<int> q;
        bool isvisited[SIZE] = {false};
        q.push(start);
        (type == 's' ? label_source[start] : label_sink[start]) = 0;
        while (!q.empty()) {
            int u, v;
            u = q.front();
            //cout<<u<<endl;
            isvisited[u] = true;
            q.pop();
            for (list<int>::iterator v = adj[u].begin(); v != adj[u].end(); ++v) {
                if (!isvisited[*v]) {
                    if (type == 's') label_source[*v] = label_source[u] + 1;
                    else label_sink[*v] = label_sink[u] + 1;
                    q.push(*v);
                }
            }
        }
        for(int i=0; i<numOfVertices; i++) cout<<label_sink[i]<<" ";
        cout<<endl;
    }

    int find_critical_vertex() {
        int i, cr_v;
        //cout<<"Size="<<adj_c[2].size()<<endl;
        for (i = 0; i < numOfVertices; i++) {
            if ((label_sink[i] + label_source[i] > label_sink[cr_v] + label_source[cr_v]) && adj_c[i].size()) cr_v = i;
        }
        return cr_v;
    }

    void find_paths() {
    }*/
};

int main() {
    graph g;
    g.read_input();
    //g.bfs(20, 'd');
	//g.find_paths();
    return 0;
}