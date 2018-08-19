/*
	Centroid Decomposition
	http://codeforces.com/problemset/problem/321/C
*/

#include <bits/stdc++.h>
using namespace std;

#define pb push_back

const int N = (int)2e5+5;
vector<int> adj[N];
int n, level[N], subsize[N];
bool iscentroid[N];

void dfs(int u, int pre) {
	subsize[u] = 1;
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (v == pre || iscentroid[v]) continue;
		dfs(v, u);
		subsize[u] += subsize[v];
	}
}

int findCentroid(int u, int pre, int total) {
	bool flag = 1;	// u is centroid
	int heaviest = 0;
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (v == pre || iscentroid[v]) continue;
		
		if (subsize[v] > total/2) flag = 0;
		if (subsize[v] > subsize[heaviest]) heaviest = v;	
	}
	if (flag) return u;
	return findCentroid(heaviest, u, total);
}

int getCentroid(int u) {
	dfs(u, -1);
	return findCentroid(u, -1, subsize[u]);
}

void decompose(int u, int lvl) {
	int centroid = getCentroid(u);
	iscentroid[centroid] = 1;
	level[centroid] = lvl;
	for (int i = 0; i < adj[centroid].size(); i++) {
		int v = adj[centroid][i];
		if (!iscentroid[v]) decompose(v, lvl+1);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n-1; i++) {
		int u, v;
		scanf("%d %d", &u, &v);	
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	for (int i = 1; i <= n; i++) iscentroid[i] = 0;
	decompose(1, 0);
	
	for (int i = 1; i <= n; i++) {
		printf("%c%c", level[i]+'A', (i==n)?'\n':' ');	
	}
	
	return 0;	
}
