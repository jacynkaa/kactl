#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define all(X) (X).begin(), (X).end()
#define sz(X) (int)(X.size())
#define st first
#define nd second
#define pii pair<int, int>

#ifdef LOC
auto &operator<<(auto &out, pair<auto, auto> a) { return out << "(" << a.st << ", " << a.nd << ")"; }

auto &operator<<(auto &out, auto a) {
   out << "{";
   for (auto b : a)
      out << b << ", ";
   return out << "}";
}

void dump(auto... x) { ((cerr << x << ", "), ...) << '\n'; }

#define debug(x...) cerr << "[" #x "]: ", dump(x)
#else
#define debug(...) 0
#endif

int32_t main() {
   ios_base::sync_with_stdio(0), cin.tie(0);
   // g++ -std=c++17 -DLOC -Wfatal-errors -Wall -O3 sol.cpp -osol
   // add flag -fconcepts to get rid of warnings related to the auto keyword in debug (only applicable to certain g++ versions)
