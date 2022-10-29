#include "../utilities/template.h"

#include "../../content/numerical/LinearRecurrence.h"

template<class F>
void gen(vector<ll>& v, int at, F f) {
	if (at == sz(v)) f();
	else {
		rep(i,mod) {
			v[at] = i;
			gen(v, at+1, f);
		}
	}
}

int main() {
	fwd(n,1,5) {
		vector<ll> start(n);
		vector<ll> coef(n);
		int size = 10*n + 3;
		vector<ll> full(size);
		gen(start,0,[&]() {
			gen(coef,0,[&]() {
				for(auto &x:full) x = 0;
				rep(i,n) full[i] = start[i];
				fwd(i,n,size) rep(j,n) full[i] = (full[i] + coef[j] * full[i-1 - j]) % mod;
	// rep(i,size) cerr << full[i] << ' '; cerr << endl;
	// rep(i,n) cerr << coef[i] << ' '; cerr << endl;
	// LinearRec lr(start, coef);
	// rep(i,size) { cerr << lr.Get(i) << ' '; } cerr << endl;
				rep(i,size) {
					auto v = linearRec(start, coef, i);
	// cerr << v << ' ';
					assert(v == full[i]);
				}
	// cerr << endl;
	// cerr << endl;
			});
		});
	}
	cout<<"Tests passed!"<<endl;
}
