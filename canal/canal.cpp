#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<string,int> si;
typedef pair<int,ii> iii;
typedef vector <si> vsi;
typedef vector <ii> vii;
typedef vector <int> vi;
typedef queue< pair<int, int> > qii;
#define INF 1000000000


int N, M, num, rmar1, cmar1, rmar2, cmar2, ar, ac;
bool visi[1001][1001];
bool negfound;
qii cola;
vector<vi> graph;
int posY[] = {0,-1,-1,-1, 0, 1, 1, 1}; // Rows de los vecinos
int posX[] = {1, 1, 0,-1,-1,-1, 0, 1}; // Cols de los vecinos

void imprimirMatriz(vector< vector<int> > matriz) {
	for(int i = 0; i < (int) matriz.size(); i++) {
		for(int j = 0; j < (int) matriz[i].size(); j++)
			printf("%10d ", matriz[i][j]);
		printf("\n");
	}
}

void fillMar(ii position, int color) {
	cola.push(position);
	graph[position.first][position.second] = color;
	while(!cola.empty()) {
		ii actual = cola.front();
		cola.pop();
		for(int i = 0; i < 8; i++) {
			ar = actual.first + posY[i];
			ac = actual.second + posX[i];
			if(ar >= 0 && ar < N && ac >= 0 && ac < M && !visi[ar][ac]) {
				if(graph[ar][ac] < 0) {
					visi[ar][ac] = 1;
					cola.push(ii(ar, ac));
					graph[ar][ac] = color;
				}
			}
		}
	}
}

bool validPos(int x, int y){
    return ((x>=0 && x<N) && (y>=0 && y<M));
}

void dijkstra(iii s, vector<vi> *dist, vector<vi> *graph){
    priority_queue< iii, vector<iii>, greater<iii> > pq; 
    pq.push(s);
    while (!pq.empty()) {
        iii front = pq.top(); 
        pq.pop();
        int d = front.first; 
        ii u = front.second;
        // if (d == dist->at(u.first)[u.second]) // No sé por qué tuve que comentarla
            for (int j = 0; j < 8; j++) {
                int newX =u.first + posX[j];
                int newY =u.second + posY[j];
                if(validPos(newX,newY)){
                    int v = graph->at(newX)[newY];                                     // all outgoing edges from u
                    if (dist->at(u.first)[u.second] + v < dist->at(newX)[newY]) {
                        dist->at(newX)[newY] = dist->at(u.first)[u.second]  + v;       // relax operation
                        ii newV (newX,newY);
                        pq.push(iii(dist->at(newX)[newY], newV));
                    }
                }
            } 
    
        	
    }
}

int main() {
	scanf("%d",&N);
	scanf("%d",&M);
	for (int i = 0; i < N; ++i) {
		vi row;
		for (int j = 0; j < M; ++j) {
			scanf("%d",&num);
			row.push_back(num);
		}
		graph.push_back(row);
	}
	// Encontrar primer mar y colorear
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			if(graph[i][j] < 0) {
				rmar1 = i;
				cmar1 = j;
				negfound = 1;
				break;
			}
		}
		if(negfound) {
			negfound = 0;
			break;
		}
	}
	fillMar(ii(rmar1, cmar1), 0);
	// Encontrar segundo mar y colorear
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			if(graph[i][j] < 0) {
				rmar2 = i;
				cmar2 = j;
				negfound = 1;
				break;
			}
		}
		if(negfound) break;
	}
	fillMar(ii(rmar2, cmar2), 0);
	// imprimirMatriz(graph);
	vi rowIni(M,INF);
	vector<vi> dist (N,rowIni);
	dist[rmar1][cmar1] = 0;
	dijkstra(iii(graph[rmar1][cmar1],ii(rmar1,cmar1)),&dist,&graph);
	// printf("DIST\n");
	// imprimirMatriz(dist);
	printf("%d\n",dist[rmar2][cmar2]);
	return 0;
}
