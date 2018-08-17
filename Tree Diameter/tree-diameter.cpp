#include <bits/stdc++.h>
using namespace std;

#define pb push_back

const int N = (int)1e5+5;
int n, height[N];
vector<int> adj[N];

int dfs(int u, int pre) {
	int maksheight = -1;
	int maksheight2 = -1;
	int diameter = 0, maksdiameter = 0;
	
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		if (v == pre) continue;
		
		int diameterv = dfs(v, u);
		if (diameterv > maksdiameter) maksdiameter = diameterv;
		
		if (height[v] >= maksheight) {
			maksheight2 = maksheight;
			maksheight = height[v];
		}
		else if (height[v] > maksheight2) {
			maksheight2 = height[v];	
		}
	}
	
	height[u] = maksheight+1;
	diameter = maksheight;
	if (maksheight2 > -1) diameter += maksheight2 + 2;
	
	maksdiameter = max(maksdiameter, diameter);
	
	return maksdiameter;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n-1; i++) {
		int u, v;
		scanf("%d %d", &u, &v);	
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	printf("%d\n", dfs(1, -1));
	
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
