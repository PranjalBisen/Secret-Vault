
    //ॐ गं गणपतये नमः
    //जय श्री राम
    //ॐ नमः शिवाय
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
const ll MOD = 1e9+7;
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
#define fast_io ios_base::sync_with_stdio(false); cin.tie(0);
#define FOR(i, a, b) for(int i = (a); i < (b); ++i)
#define FORR(i, a, b) for(int i = (a); i >= (b); --i)
#define TESTS int t; cin >> t; while(t--) solve();
#define mem(x, v) memset(x, v, sizeof(x))

string clean_string(string s){
    /*
    makes the string lower char,
    or numbers just (A-Z) -> (a-z)
    Does not change special chars or numbers
    */
   FOR(i,0,s.size()){
    if(isalpha(s[i])) s[i]|=32;
   }
   return s;
}

ll mul_mod(ll a, ll b, ll modulo){
    /*
    Simple modular multiplication helper
    */
    return ((a%modulo)*(b%modulo))%modulo;
}

int hash_ascii(string s, int n){
    /*
    simplest hash function, calculates sum of all 
    ascii and MODS with our bitArray size
    */
    ll sum_of_all_ascii=0;
    s=clean_string(s);
    FOR(i,0,s.size()){
        sum_of_all_ascii+=(s[i]-'a');
        sum_of_all_ascii%=n;
    }
    return sum_of_all_ascii;
}

int hash_polynomial(string s, int n){
    /*
    Polynomial Rolling Hash Function, 
    H(s) = (s[0]*p0 + s[1]*p1 ... + s[n-1]*pn-1)%MOD
    where p0,p1,p2...,pn-1 are p to the power of 0,1,2...,n-1
    */
   ll polynomial_rolling_hash=0;
   ll prime=31;
   ll power=1;
   s=clean_string(s);
   FOR(i,0,s.size()){
    polynomial_rolling_hash=(polynomial_rolling_hash+mul_mod(power,s[i]-'a',MOD))%n;
    polynomial_rolling_hash%=n;
    power*=prime;
   }
   return polynomial_rolling_hash;
}

ll hash_polynomial_raw(string s){
    /*
    Same polynomial rolling hash but returns the full ll value
    without modding by array size, used for password hashing
    where we want the actual hash not a bucket index
    */
   ll polynomial_rolling_hash=0;
   ll prime=31;
   ll power=1;
   s=clean_string(s);
   FOR(i,0,s.size()){
    polynomial_rolling_hash=(polynomial_rolling_hash+mul_mod(power,s[i]-'a',MOD))%MOD;
    power*=prime;
   }
   return polynomial_rolling_hash;
}

int hash_djb2(string s, int n){
    /*
    DJB2 Hashing algorithm, start with 5381, multiply current hash by 33,
    and add the charecters ascii value
    H(s) = hash x 33 + char
    */
   ll djb2_hash_value=5381;
   s=clean_string(s);
   FOR(i,0,s.size()){
    djb2_hash_value=(mul_mod(djb2_hash_value,33,MOD)+s[i]-'a');
    djb2_hash_value%=n;
   }
   return djb2_hash_value;
}

int hash_jenkins(string s, int n){
    /*
    Jenkins one-at-a-time hashing function.
    For each byte c in the data stream:
    Add the byte value to the hash.
    Shift the hash left by 10 bits and add it to itself.
    Shift the hash right by 6 bits and XOR it with itself.

    After all this :
    Shift left by 3 bits, add to itself.
    Shift right by 11 bits, XOR with itself.
    Shift left by 15 bits, add to itself.
    */
   ll jenkins_one_at_a_time_hash=0;
   s=clean_string(s);
   FOR(i,0,s.size()){
    jenkins_one_at_a_time_hash+=(s[i]-'a');
    jenkins_one_at_a_time_hash+=(jenkins_one_at_a_time_hash<<10);
    jenkins_one_at_a_time_hash^=(jenkins_one_at_a_time_hash>>6);
   }
   jenkins_one_at_a_time_hash+=(jenkins_one_at_a_time_hash<<3);
   jenkins_one_at_a_time_hash^=(jenkins_one_at_a_time_hash>>11);
   jenkins_one_at_a_time_hash+=(jenkins_one_at_a_time_hash<<15);
   jenkins_one_at_a_time_hash=(jenkins_one_at_a_time_hash%n+n)%n;

   return jenkins_one_at_a_time_hash;
}
