#include <bits/stdc++.h>
using namespace std;

#define pb push_back

const int N = (int)1e5+5;
const int INF = (int)1e9+5;
int n, dist[N];
vector<int> adj[N];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n-1; i++) {
		int u, v;
		scanf("%d %d", &u, &v);	
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	// bfs to find the furthest node from 1
	int furthestfrom1 = 1;
	for (int i = 1; i <= n; i++) dist[i] = INF;
	queue<int> q; q.push(1); dist[1] = 0;
	
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (dist[u] > dist[furthestfrom1]) furthestfrom1 = u;
		
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if (dist[u]+1 < dist[v]) {
				q.push(v);
				dist[v] = dist[u]+1;
			}
		}
	}
	
	// bfs from furthestfrom1 node to get a node furthest from furthestfrom1 node
	// diameter of tree is the distance between these two nodes.
	int ans = 0;
	for (int i = 1; i <= n; i++) dist[i] = INF;
	q.push(furthestfrom1);
	dist[furthestfrom1] = 0;
	
	while (!q.empty()) {
		int u = q.front(); q.pop();	
		if (dist[u] > ans) ans = dist[u];
		
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if (dist[u]+1 < dist[v]) {
				q.push(v);
				dist[v] = dist[u]+1;
			}
		}
	}
	
	printf("%d\n", ans);
	
	return 0;	
}

/*
9
1 2
2 3
3 4
4 5
2 6
6 7
7 8
1 9

6
1 2
2 3
2 5
5 6
3 4
*/
