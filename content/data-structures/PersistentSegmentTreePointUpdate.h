/**
 * Author: Amtek
 * Date: 2023-10-25
 * License: CC0
 * Source: folklore
 * Description: sparse (N can be up to 1e18) persistent segment tree supporting
 * point updates and range queries. Ranges are inclusive
 * Time: O(\log N)
 * Status: tested on https://codeforces.com/contest/813/problem/E
 */

struct pseg {
	typedef int val;
	val idnt = 0; // identity value
	val f(val l, val r) {
		return idnt; // implement this!
	}
	struct node {
		int l = 0, r = 0;
		val x;
		node(val x) : x(x) {
		}
	};
	int N;
	vector<node> t;
	pseg(int N) : N(N) {
		t.push_back(node(idnt)); // 0th node is the root of an empty tree
								 // t.reserve() in case of memory issues
	}
// careful to not use V and U somewhere later
#define V t[v]
#define U t[u]
	int cpy(int v) {
		t.push_back(V);
		return sz(t) - 1;
	}
	// creates lgN +- eps new nodes
	int upd(int v, int p, val x, int a = 0, int b = -1) {
		b = ~b ? b : N - 1;
		int u = cpy(v);
		if (a == b) {
			U.x = x; // change something here if not swaping values
			return u;
		}
		int c = (a + b) / 2;
		if (p <= c)
			U.l = upd(V.l, p, x, a, c);
		else
			U.r = upd(V.r, p, x, c + 1, b);
		U.x = f(t[U.l].x, t[U.r].x);
		return u;
	}
	// doesn't create new nodes
	val get(int v, int l, int r, int a = 0, int b = -1) {
		b = ~b ? b : N - 1;
		if (!v || l > b || r < a)
			return idnt;
		if (a >= l && b <= r)
			return V.x;
		int c = (a + b) / 2;
		return f(get(V.l, l, r, a, c), get(V.r, l, r, c + 1, b));
	}
};