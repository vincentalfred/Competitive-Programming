#include <bits/stdc++.h>
using namespace std;

#define pb push_back

const int N = (int)1e5+5;
const int INF = (int)1e9+5;
int n, dist[N], diameter, p[N];
vector<int> adj[N], center;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n-1; i++) {
		int u, v;
		scanf("%d %d", &u, &v);	
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	for (int i = 1; i <= n; i++) dist[i] = INF;
	queue<int> q; q.push(1); dist[1] = 0;
	int ff1 = 1;	// "furthest from 1" node
	
	while (!q.empty()) {
		int u = q.front(); q.pop();
		ff1 = u;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if (dist[u]+1 < dist[v]) {
				dist[v] = dist[u]+1;
				q.push(v);
			}
		}
	}
	
	for (int i = 1; i <= n; i++) dist[i] = INF;
	q.push(ff1); dist[ff1] = 0;
	int fff1;	// "furthest from ff1" node
	
	while (!q.empty()) {
		int u = q.front(); q.pop();
		fff1 = u;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if (dist[u]+1 < dist[v]) {
				dist[v] = dist[u]+1;
				q.push(v);	
			}
		}
	}
	
	diameter = dist[fff1];
	printf("diameter = %d\n", diameter);
	
	for (int i = 1; i <= n; i++) {
		dist[i] = INF;
		p[i] = -1;
	}
	q.push(fff1); dist[fff1] = 0; p[fff1] = fff1;
	
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (u == ff1) break;
		
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if (dist[u]+1 < dist[v]) {
				dist[v] = dist[u]+1;
				p[v] = u;
				q.push(v);
			}
		}
	}
	
	int c = ff1;
	for (int i = 0; i < diameter/2; i++) c = p[c];
	center.pb(c);
	if (diameter&1) center.pb(p[c]);
	
	printf("center = ");
	for (int i = 0; i < center.size(); i++) printf(" %d", center[i]); puts("");
	
	return 0;
}

/*
11
1 2
1 3
3 4
4 5
6 3
7 3
7 8
4 9
10 7
11 1

9
1 3
2 3
3 5
4 3
6 4
7 4
8 4
9 4

10
1 2
1 9
2 3
2 6
3 4
4 5
6 7
7 8
3 10

10
1 4
2 4
3 4
7 2
3 5
3 8
5 6
4 9
9 10
*/
