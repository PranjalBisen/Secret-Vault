
// ॐ गं गणपतये नमः
// जय श्री राम
// ॐ नमः शिवाय
#include "secret_hash_utils.h"
#include <bits/stdc++.h>
using namespace std;

// Typedefs for convenience
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef unordered_map<int, int> umii;
typedef unordered_map<ll, ll> umll;
typedef map<int, int> mii;
typedef map<ll, ll> mll;
typedef set<int> si;
typedef set<ll> sll;

// Constants
const ll MOD = 1e9 + 7;
const int M = 998244353;
const int N = 3e5 + 10;
const int N_sieve = 1000000;
const ll INF = LLONG_MAX;
const ld PI = acos(-1.0);
const ld EPS = 1e-9;

// Utility Macros
#define pb push_back
#define F first
#define S second
#define yes cout << "YES\n"
#define no cout << "NO\n"
#define bob cout << "Bob\n"
#define alice cout << "Alice\n"
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define fast_io                                                                \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORR(i, a, b) for (int i = (a); i >= (b); --i)
#define TESTS                                                                  \
  int t;                                                                       \
  cin >> t;                                                                    \
  while (t--)                                                                  \
    solve();
#define mem(x, v) memset(x, v, sizeof(x))

bool lookup_bloom_filter(vector<bool> &vis, string s, int n) {
  /*
  Function to lookup whether the given string's all hashed bits are set
  Returns true if probably present, false if definitely not present
  */
  int h1 = hash_ascii(s, n);
  int h2 = hash_polynomial(s, n);
  int h3 = hash_djb2(s, n);
  int h4 = hash_jenkins(s, n);

  if (vis[h1] && vis[h2] && vis[h3] && vis[h4]) {
    return true;
  }
  return false;
}

void insert_bloom_filter(vector<bool> &vis, string s, int n) {
  /*
  Function to get all hash values of the given string
  and set the corresponding bits, no duplicate rejection
  here because the vault layer handles that now
  */
  int h1 = hash_ascii(s, n);
  int h2 = hash_polynomial(s, n);
  int h3 = hash_djb2(s, n);
  int h4 = hash_jenkins(s, n);

  vis[h1] = true;
  vis[h2] = true;
  vis[h3] = true;
  vis[h4] = true;
}

void test_bloom_filter(vector<bool> &vis, int n) {
  /*
  Overall function to tell all capabilites of the
  bloom filter, including all hashs and insert v lookup
  */
  insert_bloom_filter(vis, "Pranjal", n);
  insert_bloom_filter(vis, "Bisen", n);
  insert_bloom_filter(vis, "PranjalBisen", n);

  lookup_bloom_filter(vis, "Pranjal", n);
  lookup_bloom_filter(vis, "GanpatiBappa", n);
}
// int main() {
//     /*
//     Used array size as 8192 just because it comes to be 1KB
//     */
//     fast_io;
//     vector<bool> vis(8192,false);
//     // test_bloom_filter(vis,8192);
//     return 0;
// }
