#include <cstdio>
#include <queue>
#include <vector>
#include <string.h>
#include <stdlib.h>

using namespace std;

#define INF 1250005

typedef queue< pair<int, int> > qii;
typedef pair<int, int> ii;
typedef vector< pair<int, int> > vii;

int r, c, nv, ri, ci, vi, nr, ar, ac, rmin, cmin, mini;
int grafo[501][501], visi[501][501];
long long peso[501][501], aux[501][501];
int vr[] = {0,-1, 0, 1}; // Rows de los vecinos (right, up, left, down)
int vc[] = {1, 0,-1, 0}; // Cols de los vecinos
qii cola;
vii vivs;
vii visi_def; // Los que estarán visitados por default

void bfs(ii position) {
	peso[position.first][position.second] = 0;
	aux[position.first][position.second] = 0;
	cola.push(position);
	while(!cola.empty()) {
		ii actual = cola.front();
		cola.pop();
		for(int i = 0; i < 4; i++) {
			ar = actual.first + vr[i];
			ac = actual.second + vc[i];
			if(ar >= 0 && ar < r && ac >= 0 && ac < c && !visi[ar][ac]) {
				visi[ar][ac] = 1;
				cola.push(ii(ar, ac));
				aux[ar][ac] += aux[actual.first][actual.second] 
					+ grafo[position.first][position.second];
				peso[ar][ac] += aux[ar][ac];
			}
		}
	}
	for(int i = 0; i < r; i++)
		for(int j = 0; j < c; j++) 
			if(!visi[i][j])
				peso[i][j] = INF;
	peso[position.first][position.second] = INF;
	aux[position.first][position.second] = INF;
}

void imprimirMatriz(long long matriz[][501], int rows, int cols) {
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++)
			printf("%8lld ", matriz[i][j]);
		printf("\n");
	}
}

void imprimirMatriz(int matriz[][501], int rows, int cols) {
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++)
			printf("%8d ", matriz[i][j]);
		printf("\n");
	}
}

int main() {
	scanf("%d %d", &r, &c);
	scanf("%d", &nv);
	for(int i = 0; i < nv; i++) {
		scanf("%d %d %d", &ri, &ci, &vi);
		grafo[ri - 1][ci - 1] = vi;
		visi_def.push_back(ii(ri - 1, ci - 1));
		vivs.push_back(ii(ri - 1, ci - 1));
	}
	scanf("%d", &nr);
	for(int i = 0; i < nr; i++) {
		scanf("%d %d", &ri, &ci);
		grafo[ri - 1][ci - 1] = INF;
		visi_def.push_back(ii(ri - 1, ci - 1));
	}
	for(int i = 0; i < (int) vivs.size(); i++) {
		memset(visi, 0, sizeof(visi));
		memset(aux, 0, sizeof(aux));
		for(int j = 0; j < (int) visi_def.size(); j++) {
			visi[visi_def[j].first][visi_def[j].second] = 1;
			peso[visi_def[j].first][visi_def[j].second] = INF;
			aux[visi_def[j].first][visi_def[j].second] = INF;
		}
		bfs(vivs[i]);
	}
	mini = peso[0][0];
	cmin = 0;
	rmin = 0;
	for (int i = 0; i < r; i++) 
		for(int j = 0; j < c; j++)
			if(peso[i][j] < mini) {
				mini = peso[i][j];
				rmin = i;
				cmin = j;
			}
	printf("%d\n", mini);
	for (int i = rmin; i < r; i++) 
		for(int j = 0; j < c; j++) 
			if(peso[i][j] == mini) printf("%d %d\n", i + 1, j + 1);
}
