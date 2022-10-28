// better random number generator
mt19937_64 gen(seed);
uniform_int_distribution<int> distr(a, b);
auto my_rand = bind(distr, gen); // my_rand() zwraca teraz liczbe z przedzialu [a, b]

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("popcnt,avx,tune=native")
//#pragma GCC optimize ("trapv") kills the program on integer overflows
// Undocumented std::bitset features:
// - _Find_first() - returns first bit = 1 or N
// - _Find_next(i) - returns first bit = 1 after i-th bit or N

// Makra Piorasow
#define each(a, x) for (auto &a : (x))
#define x first
#define y second
#define mp make_pair