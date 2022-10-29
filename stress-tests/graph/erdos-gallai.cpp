#include "../utilities/template.h"

bool valid(vi deg) {
	int n = sz(deg);
	sort(all(deg));
	reverse(all(deg));
	int sum = 0;
	rep(i,n) sum += deg[i];
	if (sum & 1) return 0;
	rep(k,n) {
		int s = 0, t = 0;
		rep(i,k+1)
			s += deg[i];
		fwd(i,k+1,n)
			t += min(deg[i], k + 1);
		if (s > k * (k+1) + t) return 0;
	}
	return 1;
}

int main() {
	rep(N,7) {
		vector<pii> possibleEd;
		rep(i,N) rep(j,i) possibleEd.emplace_back(i, j);
		set<vi> valids;
		fwd(bi,0,(1 << sz(possibleEd))) {
			vi deg(N);
			rep(i,sz(possibleEd)) if (bi & (1 << i)) {
				int a, b;
				tie(a, b) = possibleEd[i];
				deg[a]++;
				deg[b]++;
			}
			assert(valid(deg));
			valids.insert(deg);
		}

		vi de(N);
		function<void(int)> rec = [&](int at) {
			if (at == N) {
				assert(valid(de) == valids.count(de));
			} else {
				rep(a,N) {
					de[at] = a;
					rec(at + 1);
				}
			}
		};
		rec(0);
	}
	cout << "Tests passed!" << endl;
}
