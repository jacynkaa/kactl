/**
 * Author: Amtek
 * Date: 2023-10-25
 * License: CC0
 * Source: folklore
 * Description: sparse (N can be up to 1e18) persistent segment tree supporting
 * lazy propagation. Ranges are inclusive
 * Time: O(\log N)
 * Status: tested a bit (not much)
 */

struct LazyPSegmentTree { // default: update +, query max
	typedef int val;
	val idntV = 0; // identity value
	val fV(val l, val r) {
		return max(l, r); // implement combining values
	}
	typedef int lazy;
	lazy idntL = 0;
	lazy fL(lazy prv, lazy nxt) {
		return prv + nxt; // implement combining lazy
	}
	val apl(val x, lazy lz) {
		return x + lz; // implement applying lazy
	}
	struct node {
		int l = 0, r = 0;
		val x;
		lazy lz;
		node(val x, lazy lz) : x(x), lz(lz) {
		}
	};
	int N;
	vector<node> t;
	LazyPSegmentTree(int N) : N(N) {
		t.push_back(
			node(idntV, idntL)); // 0th node is the root of an empty tree
								 // t.reserve() in case of memory issues
	}
// careful to not use V and U somewhere later
#define V t[v]
#define U t[u]
	int cpy(int v) {
		t.push_back(V);
		return sz(t) - 1;
	}
	void aplV(int v, lazy lz) {
		V.lz = fL(V.lz, lz);
		V.x = apl(V.x, lz);
	}
	// creates 4 * lgN +- eps new nodes
	int upd(int v, int l, int r, lazy lz, int a = 0, int b = -1, int u = -1) {
		if (u == -1) {
			u = cpy(v);
			b = N - 1;
		}
		if (l > b || r < a)
			return u;
		if (a >= l && b <= r) {
			aplV(u, lz);
			return u;
		}
		int c = (a + b) / 2;
		U.l = cpy(V.l);
		U.r = cpy(V.r);
		aplV(U.l, U.lz);
		aplV(U.r, U.lz);
		upd(V.l, l, r, lz, a, c, U.l);
		upd(V.r, l, r, lz, c + 1, b, U.r);
		U.lz = idntL;
		U.x = fV(t[U.l].x, t[U.r].x);
		return u;
	}
	// doesn't create new nodes
	val get(int v, int l, int r, int cl = 0, int cr = -1) {
		if (cr == -1)
			cr = N - 1;
		if (!v || l > cr || r < cl)
			return idntV;
		if (cl >= l && cr <= r)
			return V.x;
		int m = (cl + cr) / 2;
		return apl(fV(get(V.l, l, r, cl, m), get(V.r, l, r, m + 1, cr)), V.lz);
	}
};