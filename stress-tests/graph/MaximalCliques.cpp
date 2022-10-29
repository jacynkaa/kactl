#include "../utilities/template.h"

#include "../../content/graph/MaximalCliques.h"

template<class F>
void fastCliques(vector<B>& eds, F f) {
	B R{}, P = ~B(), X{};
	vi deg(sz(eds));
	rep(i,sz(eds)) deg[i] = sz(eds[i]);
	rep(j,sz(eds)) {
		int i = (int)(min_element(all(deg)) - deg.begin());
		R[i] = 1;
		rec(eds, R, P & eds[i], X & eds[i], f);
		R[i] = P[i] = 0; X[i] = 1;
		rep(k,sz(eds)) if (eds[i][k]) deg[k]--;
		deg[i] = 1000000;
	}
}

int main1() {
	fwd(n,1,11) rep(m,200) {
		vector<B> ed(n);
		rep(i,m) {
			int a = rand() % n, b = rand() % n;
			if (a == b) continue;
			ed[a][b] = 1;
			ed[b][a] = 1;
		}
		unordered_set<B> cl;
		int co = 0;
		cliques(ed, [&](B x) {
			co++;
			cl.insert(x);
		});
		assert(sz(cl) == co); // no duplicates
		auto isClique = [&](B c) {
			rep(i,n) if (c[i])
			fwd(j,i+1,n) if (c[j]) {
				if (!ed[i][j]) return false; // not a clique
			}
			rep(i,n) if (!c[i]) {
				bool all = true;
				rep(j,n) if (c[j]) all &= ed[i][j];
				if (all) return false; // not maximal
			}
			return true;
		};
		for(auto &c: cl) {
			assert(isClique(c));
		}

		int realCo = 0;
		fwd(bi,0,(1 << n)) {
			B c{};
			rep(i,n) c[i] = !!(bi & (1 << i));
			if (isClique(c)) realCo++;
		}
		assert(co == realCo);
	}
	cout<<"Tests passed!"<<endl;
	return 0;
}

int main2() {
	fwd(it,0,20) {
		const int n = 128, m = 4000;
		vector<B> ed(n);
		rep(i,m) {
			int a = rand() % n, b = rand() % n;
			if (a == b) continue;
			ed[a][b] = 1;
			ed[b][a] = 1;
		}
		int co = 0, sum = 0;
		cliques(ed, [&](B x) { co++; sum += (int)x.count(); });
		cout << co << ' ' << (double)sum / co << endl;
	}
	return 0;
}

#ifndef target
#define target main1
#endif
int main() { target(); }
