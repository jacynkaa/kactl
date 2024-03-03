/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source:
 * Description: Blazing Fast Bipartite Matching. Can call on some already matched set for better performance. Extending matching by K is faster than by N.
 * Time: O(Enough)
 * Usage: initialize mt to all -1, mt[i] is the match of vertex i
 * Status: works
 */
#pragma once

int turbo(int v, vector<vi> &g, vi& mt, vi& vis) {
	if (vis[v])
		return 0;
	vis[v] = 1;
	for (auto u : g[v])
		if (mt[u] == -1 || turbo(mt[u], g, mt, vis)) {
			mt[u] = v;
			mt[v] = u;
			return 1;
		}
	return 0;
}

// vertices dont need to be [left][right] in order, just bipartite
int turboMatching(vector<vi> &g, vi &mt) {
	int n = sz(g);
	vi vis(n);
	int res = 0, flow = 1;
	while (flow) {
		flow = 0;
		fill(all(vis), 0);
		rep(i, n)
			if (mt[i] == -1 && turbo(i, g, mt, vis))
				flow ++;
		res += flow;
	}
	return res;
}
