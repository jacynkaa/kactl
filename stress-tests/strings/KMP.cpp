#include "../utilities/template.h"

#include "../../content/strings/KMP.h"

template<class F>
void gen(string& s, int at, int alpha, F f) {
	if (at == sz(s)) f();
	else {
		rep(i,alpha) {
			s[at] = (char)('a' + i);
			gen(s, at+1, alpha, f);
		}
	}
}

void test(const string& s) {
	vi p = pi(s);
	rep(i,sz(s)) {
		int maxlen = -1;
		fwd(len,0,i+1) {
			rep(j,len) {
				if (s[j] != s[i+1 - len + j]) goto fail;
			}
			maxlen = len;
fail:;
		}
		assert(maxlen == p[i]);
	}
}

int main() {
	// string str; cin >> str; for(auto &x: pi(str)) cout << x; cout << endl;
	// test ~3^12 strings
	rep(n,13) {
		string s(n, 'x');
		gen(s, 0, 3, [&]() {
			test(s);
		});
	}
	// then ~4^10 strings
	rep(n,11) {
		string s(n, 'x');
		gen(s, 0, 4, [&]() {
			test(s);
		});
	}
	cout<<"Tests passed!"<<endl;
}
