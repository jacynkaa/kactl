#include <bits/stdc++.h>
using namespace std;

#define fwd(i, a, n) for (int i = (a); i < (n); i++)
#define rep(i, n) fwd(i, 0, n)
#define all(X) begin(X),end(X)
#define sz(X) ssize(X)
#define st first
#define nd second
#define pii pair<int, int>
#define vi vector<int>

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
   // g++ -std=c++20 -DLOC -Wfatal-errors -Wall -O3 sol.cpp -osol
