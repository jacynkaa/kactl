/**
 * Author: Amtek
 * Date: 2023-10-24
 * License: CC0
 * Source: N/A
 * Description: Min cost K-flow. Supports fast 1st phase distance computation
 * Time: O(INIT + F * nlogn) INIT <= V * E and depends on first dist computation
 * Status: tested on https://codeforces.com/gym/102759/problem/F and kattis:maxflowmincost
 */

struct MCMF {
	ll INF = 9e18;
	struct edge {
		int v; ll cap, w, f;
	};
	vector<vi> g;
	vector<edge> es;
	vector<ll> dst;
	vi pre, vis;
	MCMF(int N) : g(N), dst(N), pre(N), vis(N) {}
	list<int> q; priority_queue<pair<ll, int>> pq;
	void push(int v, int dij) {
		if (dij) pq.push({-dst[v], v});
		else if (!vis[v]) {
			if (sz(q) && dst[v] < dst[q.front()]) q.push_front(v);
			else q.push_back(v);
			vis[v] = 1;
		}
	}
	void spfa(int s, int dij) { // dij 0/1 = spfa/dijsktra
		fill(all(pre), -1); fill(all(vis), 0); fill(all(dst), INF);
		dst[s] = 0; push(s, dij);
		while (sz(q) + sz(pq)) {
			int v;
			if (dij) {
				v = pq.top().nd; pq.pop();
				if (vis[v]++) continue;
			} else {
				v = q.front(); q.pop_front();
				vis[v] = 0;
			}
			for (auto eid : g[v]) {
				edge &e = es[eid];
				if (e.cap != e.f) {
					int u = e.v;
					ll d = dst[v] + e.w;
					if (d < dst[u]) {
						dst[u] = d; pre[u] = eid ^ 1;
						push(u, dij);
					}
				}
			}
		}
	}
	void add(int u, int v, ll cap = 1, ll cost = 0) {
		g[u].push_back(sz(es));
		es.push_back({v, cap, cost, 0});
		g[v].push_back(sz(es));
		es.push_back({u, 0, -cost, 0});
	}
	pair<ll, ll> calc(int s, int t, ll k = -1) {
		spfa(s, 0); // disregard if weights are non-negative
		// compute dist faster here if graph is special (DAG etc)
		ll totf = 0, totc = 0, fc = dst[t];
		while (true) {
			rep (v, sz(g)) for (auto e : g[v])
				es[e].w += dst[v] - dst[es[e].v];
			spfa(s, 1);
			if (~pre[t]) {
				fc += dst[t];
				ll f = ~k ? k - totf : INF;
				for (int e = pre[t]; ~e; e = pre[es[e].v])
					f = min(f, es[e ^ 1].cap - es[e ^ 1].f);
				for (int e = pre[t]; ~e; e = pre[es[e].v])
					es[e ^ 1].f += f, es[e].f -= f;
				totf += f, totc += f * fc;
				if (totf == k) break;
			} else break;
		}
		return {totf, totc};
	}
};