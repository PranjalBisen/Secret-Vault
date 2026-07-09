
    //ॐ गं गणपतये नमः
    //जय श्री राम
    //ॐ नमः शिवाय
#include <bits/stdc++.h>
#include "secret_hash_utils.h"
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

struct VaultMetadata{
    /*
    Stores vault level information like password hash
    Lives inside .meta file, separate from .dat records
    */
    ll password_hash;
};

ll hash_password(string password){
    /*
    Uses our own polynomial rolling hash to hash the password
    No SHA256, no OpenSSL, no bcrypt, just our beautiful hash
    */
    return hash_polynomial_raw(password);
}

void create_metadata(string vault_name,string password){
    /*
    Creates the .meta file and stores the hashed password
    Called only when creating a brand new vault
    */
    string meta_file_name=vault_name+".meta";
    fstream file(meta_file_name,ios::binary|ios::out);
    if(!file){
        cout<<"Error while creating metadata file"<<endl;
        return;
    }
    VaultMetadata metadata;
    metadata.password_hash=hash_password(password);
    file.write((char*)&metadata,sizeof(metadata));
    file.close();
    cout<<"Vault password set successfully"<<endl;
}

VaultMetadata read_metadata(string vault_name){
    /*
    Reads the .meta file and returns the VaultMetadata struct
    */
    string meta_file_name=vault_name+".meta";
    VaultMetadata metadata;
    metadata.password_hash=-1;
    fstream file(meta_file_name,ios::binary|ios::in);
    if(!file){
        cout<<"Error while reading metadata file"<<endl;
        return metadata;
    }
    file.read((char*)&metadata,sizeof(metadata));
    file.close();
    return metadata;
}

bool verify_password(string vault_name,string password){
    /*
    Hashes the entered password and compares with stored hash
    Simple comparison, if hashes match you're in
    */
    VaultMetadata metadata=read_metadata(vault_name);
    if(metadata.password_hash==-1){
        cout<<"Could not read vault metadata"<<endl;
        return false;
    }
    ll entered_hash=hash_password(password);
    return entered_hash==metadata.password_hash;
}
