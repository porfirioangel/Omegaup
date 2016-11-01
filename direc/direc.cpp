#include <cstdio>
#include <string.h>

using namespace std;

int n, m, calif[1001][1001], p, a, b, q, r, tot, prom;

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		for(int j = 1; j <= m; j++) {
			scanf("%d", &calif[i][j]);
			calif[i][j] += calif[i][j - 1];
		}
	}
	scanf("%d", &p);
	while(p--) {
		prom = 0;
		scanf("%d %d %d %d", &a, &b, &q, &r);
		tot = (b - a + 1) * (r - q + 1);
		for(int i = a - 1; i < b; i++) {
			prom += (calif[i][r] - calif[i][q - 1]);
		}
		prom /= tot;
		printf("%d\n", prom);
	}
	return 0;
}
