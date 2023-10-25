/**
 * Author: Amtek
 * Date: 2023-10-25
 * License: CC0
 * Source: folklore
 * Description: sparse (N can be up to 1e18) persistent segment tree supporting
 * range updates and point queries. Ranges are inclusive
 * Time: O(\log N)
 * Status: tested on https://codeforces.com/contest/1887/problem/D
 */

struct PSegmentTree { // default: update add, query val
	typedef int val;
	val idnt = 0; // neutral value
	val f(val a, val b) {
		return a + b; // implement this!
	}
	struct node {
		int l = 0, r = 0;
		val x;
		node(val x) : x(x) {
		}
	};
	int N;
	vector<node> t;
	PSegmentTree(int N) : N(N) {
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
	// creates 4 * lgN +- eps new nodes
	int upd(int v, int l, int r, val x, int a = 0, int b = -1) {
		b = ~b ? b : N - 1;
		if (l > b || r < a)
			return v;
		int u = cpy(v);
		if (a >= l && b <= r) {
			U.x = f(U.x, x);
			return u;
		}
		int c = (a + b) / 2;
		U.l = upd(V.l, l, r, x, a, c);
		U.r = upd(V.r, l, r, x, c + 1, b);
		return u;
	}
	// doesn't create new nodes
	val get(int v, int p, int a = 0, int b = -1) {
		b = ~b ? b : N - 1;
		if (a == b)
			return V.x;
		int c = (a + b) / 2;
		if (p <= c)
			return f(V.x, get(V.l, p, a, c));
		return f(V.x, get(V.r, p, c + 1, b));
	}
};