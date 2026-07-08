
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

// Sieve of Eratosthenes and Smallest Prime Factor (SPF)
vector<ll> sieve(N_sieve, 1);
vector<ll> spf(N_sieve + 1, 1e9);
void sieveoe() {
    for (ll i = 0; i < spf.size(); i++) {
        spf[i] = i;
    }
    sieve[0] = 0;
    sieve[1] = 0;
    for (ll i = 2; i * i <= N_sieve; i++) {
        if (sieve[i]) {
            spf[i] = min(spf[i], i);
            for (ll j = i * i; j <= N_sieve; j += i) {
                sieve[j] = 0;
                spf[j] = min(spf[j], i);
            }
        }
    }
}

// Factorial and Modular Factorial
ll factorial(ll n) {
    ll ans = 1;
    for (ll i = 1; i <= n; i++) {
        ans *= i;
    }
    return ans;
}

ll mul_mod(ll a, ll b, ll modulo) {
    return ((a % modulo) * (b % modulo)) % modulo;
}

ll factorial_with_mod(ll n, ll modulo) {
    ll ans = 1;
    for (ll i = 1; i <= n; i++) {
        ans = mul_mod(ans, i, modulo);
    }
    return ans % modulo;
}

// GCD, LCM, and Modular Inverse
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll lcm(ll a, ll b) {
    return (a * b) / gcd(a, b);
}

ll mod_inverse(ll a, ll mod = MOD) {
    ll res = 1, b = mod - 2;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// Power of 2 Check
bool powerof2(ll x) {
    return !(x & (x - 1));
}

// MSB and One's Complement
ll msb(ll n) {
    ll ans = 0;
    n = (n >> 1);
    while (n) {
        n = (n >> 1);
        ans++;
    }
    return ans;
}

int onesComplement(int n) {
    int number_of_bits = floor(log2(n)) + 1;
    return ((1 << number_of_bits) - 1) ^ n;
}

// nCr Function (Combinatorial)
int nCr(int n, int r) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;
    return nCr(n - 1, r - 1) + nCr(n - 1, r);
}

// String Utility Functions
string to_upper(string s) {
    transform(all(s), s.begin(), ::toupper);
    return s;
}

string to_lower(string s) {
    transform(all(s), s.begin(), ::tolower);
    return s;
}

bool is_palindrome(const string &s) {
    return equal(s.begin(), s.begin() + s.size()/2, s.rbegin());
}

// Comparator Function for Sorting Pairs by Sum
static bool compsum(pii a, pii b) {
    return (a.first + a.second < b.first + b.second);
}



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

bool lookup_bloom_filter(vector<bool>&vis, string s, int n){
    /*
    Function to lookup whether the given string's all hashed bits are set
    */
   int h1=hash_ascii(s,n);
   int h2=hash_polynomial(s,n);
   int h3=hash_djb2(s,n);
   int h4=hash_jenkins(s,n);

   if(vis[h1]&&vis[h2]&&vis[h3]&&vis[h4]){
    cout<<"hash_ascii = "<<h1<<endl;
    cout<<"hash_polynomial = "<<h2<<endl;
    cout<<"hash_djb2 = "<<h3<<endl;
    cout<<"hash_jenkins = "<<h4<<endl; 
    cout<<"Probably Present"<<endl;
    return true;
   }
   cout<<"Definitely Not Present"<<endl;
   return false;
}

void insert_bloom_filter(vector<bool>&vis, string s, int n){
    /*
    Function to get all hash values of the given string
    and set the corresponding bits
    */
    if(lookup_bloom_filter(vis,s,n)){
        no;
        cout<<"Duplicacy detected by Bloom Filter"<<endl;
        return;
    }
   int h1=hash_ascii(s,n);
   int h2=hash_polynomial(s,n);
   int h3=hash_djb2(s,n);
   int h4=hash_jenkins(s,n);

   vis[h1]=true;
   vis[h2]=true;
   vis[h3]=true;
   vis[h4]=true;

   yes;
   cout<<"hash_ascii = "<<h1<<endl;
   cout<<"hash_polynomial = "<<h2<<endl;
   cout<<"hash_djb2 = "<<h3<<endl;
   cout<<"hash_jenkins = "<<h4<<endl; 
   cout<<"Successfully inserted"<<endl;
}

void test_bloom_filter(vector<bool>&vis, int n){
    /*
    Overall function to tell all capabilites of the 
    bloom filter, including all hashs and insert v lookup
    */
   insert_bloom_filter(vis,"Pranjal",n);
   insert_bloom_filter(vis,"Bisen",n);
   insert_bloom_filter(vis,"PranjalBisen",n);

   lookup_bloom_filter(vis,"Pranjal",n);
   lookup_bloom_filter(vis,"GanpatiBappa",n);

   insert_bloom_filter(vis,"Pranjal",n);

}
int main() {
    /*
    Used array size as 8192 just because it comes to be 1KB
    */
    fast_io;
    vector<bool> vis(8192,false);
    // test_bloom_filter(vis,8192);
    return 0;
}
