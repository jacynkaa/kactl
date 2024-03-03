#include "../utilities/template.h"

#include "../../content/graph/MinimumVertexCover.h"
#include "../../content/graph/hopcroftKarp.h"

vi coverHK(vector<vi>& g, int n, int m) {
	vi match(m, -1);
	int res = hopcroftKarp(g, match);
	vector<bool> lfound(n, true), seen(m);
	for(auto &it: match) if (it != -1) lfound[it] = false;
	vi q, cover;
	rep(i,n) if (lfound[i]) q.push_back(i);
	while (!q.empty()) {
		int i = q.back(); q.pop_back();
		lfound[i] = 1;
		for(auto &e: g[i]) if (!seen[e] && match[e] != -1) {
			seen[e] = true;
			q.push_back(match[e]);
		}
	}
	rep(i,n) if (!lfound[i]) cover.push_back(i);
	rep(i,m) if (seen[i]) cover.push_back(n+i);
	assert(sz(cover) == res);
	return cover;
}

int main() {
	fwd(it,0,300000) {
		int N = rand() % 100, M = rand() % 100;
		int prop = rand();
		vector<vi> gr1(N);
		vector<vi> gr2(N + M);
		vi left(N), right(M);
		rep(i,N) rep(j,M) if (rand() < prop) {
			gr1[i].push_back(j);
			gr2[i].push_back(j + N);
			gr2[j + N].push_back(i);
		}
		auto verify = [&](vi& cover) {
			for(auto &x: cover) {
				if (x < N) left[x] = 1;
				else right[x - N] = 1;
			}
			rep(i,N) if (!left[i]) for(auto &j:gr1[i]) {
				assert(right[j]);
				/* if (!right[j]) {
					cout << N << ' ' << M << endl;
					rep(i,N) for(auto &j: gr[i]) cout << i << " - " << j << endl;
					cout << "yields " << sz(cover) << endl;
					for(auto &x: cover) cout << x << endl;
					abort();
				} */
			}
		};
		vi cover1 = cover(gr2, N, M);
		vi cover2 = coverHK(gr1, N, M);
		assert(sz(cover1) == sz(cover2));
		verify(cover1);
		verify(cover2);
		// cout << '.' << endl;
	}
	cout<<"Tests passed!"<<endl;
}
