#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <stack>
#include <utility>
#define size 19
using namespace std;

class graph {
public:
    bool input[size][size], adj[size][size][4], adj_c[size][size][4];
	int label_source[size][size], label_sink[size][size], source_i, source_j, sink_i, sink_j;

    graph() {
        memset(label_source, 0, sizeof (int) *size * size);
        memset(label_sink, 0, sizeof (int) *size * size);
        memset(adj, 0, sizeof (int) *size * size * 4);
        source_i = 0;
		source_j = 0;
		sink_i = 17;
		sink_j = 0;
    }

    void read_input() {
        int i, j;
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) cin >> input[i][j];
        }
    }

    void make_adj() {
        int i, j;
        for (i = 0; i < size; i++) {
            adj[i][0][0] = 0;
            adj[0][i][1] = 0;
            adj[i][size - 1][2] = 0;
            adj[size - 1][i][3] = 0;
        }
        for (i = 0; i < size; i++) {
            for (j = 1; j < size; j++) {
                if (input[i][j]) adj[i][j][0] = input[i][j - 1];
            }
        }
        for (i = 1; i < size; i++) {
            for (j = 0; j < size; j++) {
                if (input[i][j]) adj[i][j][1] = input[i - 1][j];
            }
        }
        for (i = 0; i < size; i++) {
            for (j = 0; j < size - 1; j++) {
                if (input[i][j]) adj[i][j][2] = input[i][j + 1];
            }
        }
        for (i = 0; i < size - 1; i++) {
            for (j = 0; j < size; j++) {
                if (input[i][j]) adj[i][j][3] = input[i + 1][j];
            }
        }
        memcpy(adj_c, adj, sizeof (bool) * size * size * 4);
    }

    void assign_label() {
        int i, j;
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                if (input[i][j]) {
					label_source[i][j] = abs(i - source_i) + abs(j - source_j);
					label_sink[i][j] = abs(i - sink_i) + abs(j - sink_j);
                }
            }
        }
        /*for(i=0; i<size; i++) {
                for(j=0; j<size; j++) cout<<"("<<label_source[i][j]<<", "<<label_sink[i][j]<<") ";
                cout<<endl;
        }*/
    }

    int cr_b_i, cr_b_j, cr_e_i, cr_e_j, i, j, flag;

    int find_critical_edge() {
        int i, j;
        for(i=0; i<size; i++) {
                for(j=0; j<size; j++) {
                        for(int k=0; k<4; k++) cout<<adj_c[i][j][k]<<" ";
                        cout<<"  ";
                }
                cout<<endl;
        }
		cr_b_i = cr_b_j = 0;
		flag = 0;
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
				if(adj_c[i][j][0] || adj_c[i][j][1] || adj_c[i][j][2] || adj_c[i][j][3]) {
					if (input[i][j] && (label_source[cr_b_i][cr_b_j]+label_sink[cr_b_i][cr_b_j]) < (label_source[i][j] + label_sink[i][j])) {
						cr_b_i = i;
						cr_b_j = j;
					}
					flag = 1;
				}
			}
		}
		cr_e_i = cr_b_i;
		cr_e_j = cr_b_j;
		if(adj_c[cr_b_i][cr_b_j][2]) {
			cr_e_j = cr_b_j + 1;
			adj_c[cr_b_i][cr_b_j][2] = 0;
		}
		else if(adj_c[cr_b_i][cr_b_j][3]) {
			cr_e_i = cr_b_i + 1;
			adj_c[cr_b_i][cr_b_j][3] = 0;
		}
		else if(adj_c[cr_b_i][cr_b_j][0]) {
			adj_c[cr_b_i][cr_b_j][0] = 0;
			cr_e_i = cr_b_i;
			cr_e_j = cr_b_j;
			cr_b_j = cr_e_j - 1;
		}
		else if(adj_c[cr_b_i][cr_b_j][1]) {
			adj_c[cr_b_i][cr_b_j][1] = 0;
			cr_e_i = cr_b_i;
			cr_e_j = cr_b_j;
			cr_b_i = cr_e_i - 1;
		}
		//cout<<cr_b_i<<" "<<cr_b_j<<" "<<cr_e_i<<" "<<cr_e_j<<endl;
    }

    void find_paths() {
        int total_path_length = 0, count = 0, n = 5;
        make_adj();
        assign_label();
        while (n--) {

            find_critical_edge();
            if (!flag) break; //whole graph covered

            count++;

            int max_path_length = 0, path_length = 1;
            i = cr_b_i;
            j = cr_b_j;

            path_length = label_source[cr_b_i][cr_b_j] + label_sink[cr_e_i][cr_e_j] + 1;

            if (!max_path_length) max_path_length = path_length;

            total_path_length += path_length;
            stack< pair<int, int> > source;
            source.push(make_pair(cr_e_i, cr_e_j));
            /*find path from source*/
            while (i != source_i || j != source_j) {
                source.push(make_pair(i, j));
				if (adj_c[i][j][1] && (label_source[i][j] == label_source[i - 1][j] + 1)) {
                    adj_c[i][j][1] = 0;
                    adj_c[i - 1][j][3] = 0;
                    /*if(max_path_length >= path_length+2) {
                            int k = j, l = i, slag;
                            while(k>0 && k<size && adj_c[l][j][1] && slag) {k--;}
                    }*/
                    i--;
                }
                else if (adj_c[i][j][0] && (label_source[i][j] == label_source[i][j - 1] + 1)) {
                    adj_c[i][j][0] = 0;
                    adj_c[i][j - 1][2] = 0;
                    j--;
                }
                else if ((label_source[i][j] == label_source[i + 1][j] + 1) && adj_c[i][j][3]) {
					adj_c[i][j][3] = 0;
					adj_c[i + 1][j][1] = 0;
					i++;
				}
				else if ((label_source[i][j] == label_source[i][j + 1] + 1) && adj_c[i][j][2]) {
					adj_c[i][j][2] = 0;
					adj_c[i][j + 1][0] = 0;
					j++;
				}
				else if (adj[i][j][1]) i--;
				else if (adj[i][j][0]) j--;
				else if (adj[i][j][3]) i++;
				else if (adj[i][j][2]) j++;
			}

			source.push(make_pair(source_i, source_j));
			cout << "Path " << count << " : ";
			while (!source.empty()) {
				cout << "(" << source.top().first << "," << source.top().second << ") -> ";
				source.pop();
			}

			i = cr_e_i;
            j = cr_e_j;

            /*find path from sink*/
			while (i != sink_i || j != sink_j) {
				cout << "(" << i << "," << j << ") -> ";
				if ((label_sink[i][j] == label_sink[i][j - 1] + 1) && adj_c[i][j][0]) {
                    adj_c[i][j][0] = 0;
                    adj_c[i][j - 1][2] = 0;
                    j--;
                }
                else if ((label_sink[i][j] == label_sink[i+1][j] + 1) && adj_c[i][j][3]) {
					adj_c[i][j][3] = 0;
					adj_c[i + 1][j][1] = 0;
					i++;
				}
				else if ((label_sink[i][j] == label_sink[i][j + 1] + 1) && adj_c[i][j][2]) {
					adj_c[i][j][2] = 0;
					adj_c[i][j + 1][0] = 0;
					j++;
				}
				else if ((label_sink[i][j] == label_sink[i - 1][j] + 1) && adj_c[i][j][1]) {
					adj_c[i][j][3] = 0;
					adj_c[i + 1][j][1] = 0;
					i--;
				}
				else if (adj[i][j][0]) j--;
                else if (adj[i][j][3]) i++;
				else if (adj[i][j][2]) j++;
				else if (adj[i][j][1]) i--;
				if (!max_path_length) max_path_length = path_length;
            }
			cout << "(" << sink_i << "," << sink_j << ") -> ";
            cout << "(length = " << path_length << ")" << endl;
			getchar();
        }

        cout << "Number of paths : " << count << endl;
        cout << "Total path length : " << total_path_length;

    }
};

int main() {
    graph g;
    g.read_input();
    g.find_paths();
//     g.make_adj();
// 	g.assign_label();
// 	g.find_critical_edge();
	return 0;
}