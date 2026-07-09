
    //ॐ गं गणपतये नमः
    //जय श्री राम
    //ॐ नमः शिवाय
#include <bits/stdc++.h>
#include "secret_index_bst.h"
#include "secret_binary_storage.h"
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

SecretRecord create_record_helper(string key, string secret){
    /*
    Simple helper function to create the secretrecord struct
    */
    SecretRecord record;
    strcpy(record.name,key.c_str());
    strcpy(record.secret,secret.c_str());
    record.is_deleted=false;
    return record;
}

void insert_secret(string vault_file_name, BSTNode* &root){
    /*
    Simple function to encapsulate all the required
    logical operations to store a secret in .dat and 
    also in bst
    */
   string key, secret;
    cout<<"Enter Your Name Bruvvv"<<endl;
    cin>>key;
    // getline(cin, key);
    cout<<"Its time to know your secret"<<endl;
    cin>>secret;
    // getline(cin, secret);

    SecretRecord secretrecord=create_record_helper(key, secret);
    ll current_write_offset=append_dat_file(vault_file_name,secretrecord);
    BSTNode* new_node=create_new_node(key,current_write_offset);
    insert_new_node_in_bst(new_node,root); 
}

bool vault_exists(string vault_file_name){
    /*
    Function to check if there is an existing
    vault with same name
    */
    fstream file(vault_file_name,ios::binary|ios::in);
    return file.good();
}

BSTNode* rebuild_bst_from_file(string vault_file_name){
    /*
    We already had a bst before we killed the program
    so now we gotta rebuild the tree from the secret vault
    */
    BSTNode* root=nullptr;
    fstream file(vault_file_name,ios::binary|ios::in);
    if(!file){
        cout<<"Error while opening vault for rebuild"<<endl;
        return root;
    }
    SecretRecord record;
    ll offset=0;
    while(read_next_record(file,record)){
        if(!record.is_deleted){
            BSTNode* new_node=create_new_node(string(record.name),offset);
            insert_new_node_in_bst(new_node,root);
        }
        offset+=sizeof(SecretRecord);
    }
    file.close();
    return root;
}

void search_secret(string vault_file_name,BSTNode* &root){
    /*
    Another beautiful funciton to encapsulate all 
    the search logic : bst -> .dat -> output
    */
    cout<<"Tell me what you wanna search for"<<endl;
    string key;
    cin>>key;

    BSTNode* searched_node=search_node_in_bst(key,root);
    if(!searched_node){
        no;
        cout<<"Sorry bruv we don't have your secret"<<endl;
    }
    else{
        yes;
        ll searched_offset=searched_node->offset;
        SecretRecord temp;
        read_from_offset_one_dat_file(vault_file_name,temp,searched_offset);
    }
}

void test_vault_orchestrated_flow(){
    /*
    Our test function for testing the orchestrated 
    flow of binary storage and bst integrated logic
    */
    string vault;
    cout<<"What should your vault's name be?"<<endl;
    cin>>vault;
    create_dat_file(vault);
    string vault_file_name=vault+".dat";
    BSTNode* root=nullptr;
    FOR(i,0,3){
        cout<<"Record :"<<i+1<<endl;
        insert_secret(vault_file_name,root);
    }
    cout<<"Now all records are saved in the vault with their offsets in bst"<<endl;
    cout<<"Its search time babbyyyy"<<endl;
    FOR(i,0,3){
        search_secret(vault_file_name,root);
    }
}

void menu(){
    /*
    A simple infite loop menu function
    */
    string vault;
    cout<<"What should your vault's name be?"<<endl;
    cin>>vault;
    string vault_file_name=vault+".dat";
    BSTNode* root=nullptr;
    if(vault_exists(vault_file_name)){
        cout<<"Vault found! Recovering BST..."<<endl;
        root=rebuild_bst_from_file(vault_file_name);
        cout<<"BST rebuilt successfully"<<endl;
    }
    else{
        create_dat_file(vault);
    }
    while(true){
    cout<<"Welcome to My Secret Vault"<<endl;
    cout<<"1. Insert Secret"<<endl;
    cout<<"2. Search Secret"<<endl;
    cout<<"3. Print all Secrets like a madman"<<endl;
    cout<<"4. I'm a loser, Byeeee"<<endl;

    int choose;
    cin>>choose;

    if(choose==1){
        insert_secret(vault_file_name,root);
    }
    else if(choose==2){
        search_secret(vault_file_name,root);
    }
    else if(choose==3){
        SecretRecord temp;
        read_all_dat_file(vault_file_name,temp);
    }
    else if(choose==4){
        cout<<"Bye loseerrrr"<<endl;
        break;
    }
    else{
        cout<<"Read properly and enter bruvvv"<<endl;
    }
   }
   inorder_traversal_of_bst(root);
}

int main() {
    /*
    Simple flow, first create a secret.dat file,
    ask user to give key and their secret,
    make a record from that and after that make 
    a node from same record and append to BST.
    */
    fast_io;
    menu();
    // test_vault_orchestrated_flow();
    return 0;
}