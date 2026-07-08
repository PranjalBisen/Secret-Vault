
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

struct SecretRecord{
    /*
    Struct SecretRecord which contains user name, user secret 
    and a is_deleted flag.
    Will be used as a node and storage format later.
    */
    char name[32];
    char secret[256];
    bool is_deleted;
};

void print_secret_record(SecretRecord secretRecord){
    /*
    Helper Function to print the complete struct
    */
   cout<<"Name : "<<secretRecord.name<<" Secret : "<<secretRecord.secret<<endl;
}

void print_current_write_offset(fstream& file){
    cout<<"Current write offset is : "<<file.tellp()<<endl;
}

void print_current_read_offset(fstream& file){
    cout<<"Current read offset is : "<<file.tellg()<<endl;
}

void create_dat_file(string s){
    /*
    Simple function to create a data file 
    */
    fstream created_file(s+".dat", ios::binary|ios::out);
    print_current_write_offset(created_file);
    if(!created_file){
        no;
        cout<<"Error while creating file"<<endl;
        return ;
    }
    cout<<"File : "<<s<<".dat Successfully Created"<<endl;
    print_current_write_offset(created_file);
    created_file.close();
}

void append_dat_file(string file_name, SecretRecord secretRecord){
    /*
    Here we have written code to append value at the end of file
    */
   fstream file(file_name, ios::binary|ios::out|ios::app);
   if(!file){
        no;
        cout<<"Error while creating file"<<endl;
        return ;
    }
   print_current_write_offset(file);
    file.write((char*)&secretRecord,sizeof(secretRecord));
    print_current_write_offset(file);
    cout<<"Data Appended Successfully"<<endl;
    cout<<"Size of Struct: "<<sizeof(secretRecord)<<endl;
    file.close();
}

void read_all_dat_file(string file_name, SecretRecord secretRecord){
    /*
    Function to read the complete file contents
    */
   fstream file(file_name,ios::binary|ios::in);
   print_current_read_offset(file);
   if(!file){
        no;
        cout<<"Error while creating file"<<endl;
        return ;
    }
    while(file.read((char*)&secretRecord, sizeof(secretRecord))){
        if(!secretRecord.is_deleted){
            print_secret_record(secretRecord);
            print_current_read_offset(file);
        }
    }
    print_current_read_offset(file);
    cout<<endl;
    cout<<"Complete File Read Successfully"<<endl;
    file.close();
}

void read_from_record_number_one_dat_file(string file_name, SecretRecord secretRecord, int index){
    /*
    Function to read exactly one Struct from a file
    according to the given record number
    */
   fstream file(file_name,ios::binary|ios::in);
   print_current_read_offset(file);
   if(!file){
        no;
        cout<<"Error while creating file"<<endl;
        return ;
    }
    file.seekg(index*sizeof(secretRecord));
    print_current_read_offset(file);
    if(file.read((char*)&secretRecord,sizeof(secretRecord))){
        if(!secretRecord.is_deleted){
            print_secret_record(secretRecord);
        }
        else{
            cout<<"This is Soft Deleted"<<endl;
            print_secret_record(secretRecord);
        }
    }
    print_current_read_offset(file);
    cout<<"Successfully read one struct record"<<endl;
    file.close();
}

void read_from_offset_one_dat_file(string file_name, SecretRecord secretRecord, int offset){
    /*
    Function to read exactly one Struct from a file
    at a given offset
    */
   fstream file(file_name,ios::binary|ios::in);
   print_current_read_offset(file);
   if(!file){
        no;
        cout<<"Error while creating file"<<endl;
        return ;
    }
    file.seekg(offset);
    print_current_read_offset(file);
    if(file.read((char*)&secretRecord,sizeof(secretRecord))){
        if(!secretRecord.is_deleted){
            print_secret_record(secretRecord);
        }
        else{
            cout<<"This is Soft Deleted"<<endl;
            print_secret_record(secretRecord);
        }
    }
    print_current_read_offset(file);
    cout<<"Successfully read one struct record"<<endl;
    file.close();
}

void test_file_handling(){
    /*
    Simple test function to test create, append, and various 
    read capabilites in .dat files.
    */
    SecretRecord s1={"Pranjal","It is currently way past my bedtime lol",false};
    SecretRecord s2={"Pranjal Bisen","I don't have to get up early tomorrow anyways",false};
    SecretRecord s3={"GanpatiBappa","Ganpati Bapppaaaa Morryyyyaaaaaaa",false};
    SecretRecord s4={"Naav Visarlo","Idk what to write here now",true};
    cout<<"Size of Struct : "<<sizeof(s1)<<endl;
    create_dat_file("Secret");
    append_dat_file("Secret.dat",s1);
    append_dat_file("Secret.dat",s2);
    append_dat_file("Secret.dat",s3);
    append_dat_file("Secret.dat",s4);
    read_all_dat_file("Secret.dat",s1);
    read_from_record_number_one_dat_file("Secret.dat",s1,2);
    read_from_offset_one_dat_file("Secret.dat",s1,100);
    read_from_offset_one_dat_file("Secret.dat",s1,289);
    read_from_record_number_one_dat_file("Secret.dat",s1,3);

}
/*
tellp() -> Current write offset.
tellg() -> Current read offset.
seekp() -> Move the write offset.
seekg() -> Move the read offset.
*/
int main() {
    fast_io;
    // test_file_handling();
    return 0;
}